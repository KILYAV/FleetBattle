#include "Random.h"

using namespace random;

void Random::Order() {
	Sea::Fill(Cell::sea);
	auto& ranks{ Ranks() };

	for (UINT index = 0, size = GetLevelUINT(), count = size;
		index < size; ++index) {
		ranks[index] = count--;
	}

	for (UINT level = ranks.size(); level > 0; --level) {
		for (UINT number = 0, count = ranks[level - 1]; number < count; ++number) {
			GetShip(static_cast<Level>(level));
		}
	}
}
void Random::GetShip(const Level level) {
	auto [point, direct] = GetPointDirect(level);
	for (UINT index = 0, size = static_cast<UINT>(level);
		index < size; ++index) {
		Sea::SetCell(point, Cell::ship);
		point = (&point->*direct)();
	}
}
std::pair<Point, Random::Direct> Random::GetPointDirect(
	const Level level
) const {
	auto [center, up, left, ver, hor] {GetPointRaw(level)};

	UINT deltaX = center.X();
	UINT deltaY = center.Y();
	Direct direct = nullptr;
	if (hor < static_cast<UINT>(level)) {
		deltaY = up + GetOffset(ver, level);
		direct = &Point::Down;
	}
	else if (ver < static_cast<UINT>(level)) {
		deltaX = left + GetOffset(hor, level);
		direct = &Point::Right;
	}
	else {
		if (GetRandBool()) {
			deltaY = up + GetOffset(ver, level);
			direct = &Point::Down;
		}
		else {
			deltaX = left + GetOffset(hor, level);
			direct = &Point::Right;
		}
	}

	return {
		Point{ deltaX, deltaY },
		direct
	};
}
UINT Random::GetOffset(
	const UINT line,
	const Level level
) const {
	UINT delta = line - static_cast<UINT>(level);
	delta = GetRandUINT(delta + 1);
	return delta;
}
enum Direct {
	up,
	left,
	ver,
	hor
};
std::tuple<Point, UINT, UINT, UINT, UINT> Random::GetPointRaw(
	const Level level
) const {
	Point center;
	std::tuple<UINT, UINT, UINT, UINT> tuple;
	do {
		center = GetCenter();
		tuple = GetRaw(center);
	} while (
		(static_cast<UINT>(level) > std::get<ver>(tuple)) &&
		(static_cast<UINT>(level) > std::get<hor>(tuple))
		);
	return {
		center,
		std::get<up>(tuple),
		std::get<left>(tuple),
		std::get<ver>(tuple),
		std::get<hor>(tuple)
	};
}
std::tuple<UINT, UINT, UINT, UINT> Random::GetRaw(
	const Point point
) const {
	using namespace compare;
	UINT up = LengthRaw(
		&Random::CompareTrip<Sea, HOR>, point, &Point::Up);
	UINT left = LengthRaw(
		&Random::CompareTrip<Sea, VER>, point, &Point::Left);
	UINT ver = LengthRaw(
		&Random::CompareTrip<Sea, HOR>, point, &Point::Down);
	UINT hor = LengthRaw(
		&Random::CompareTrip<Sea, VER>, point, &Point::Right);

	ver = ver + up - 1;
	hor = hor + left - 1;
	up = point.Y() - (up - 1);
	left = point.X() - (left - 1);

	return { up, left, ver, hor };
}
Point Random::GetCenter() const {
	Point point;
	do {
		point = Sea::GetRandPoint(Cell::sea);
	} while (CompareSquare<Sea>(point));
	return point;
}