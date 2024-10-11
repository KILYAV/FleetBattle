//#include <iostream>
#include "Fleet.h"

using namespace fleet;

Fleet::Fleet()
{
	ranks.resize(GetLevelUINT());
}
std::optional<std::pair<UINT, bool>> Fleet::Status() const {
	auto max{ GetLevelUINT() };
	for (UINT index = 0, size = ranks.size(); index < size; ++index) {
		if (ranks[index] == max) {
			--max;
		}
		else {
			return { { max, ranks[index] > max } };
		}
	}
	return {};
}
std::optional<Cell> Fleet::LevelUp(
	const Point point
) {
	auto check{ Fleet::CheckUp(point) };
	if (check) {
		auto& [first, second, levelUp] { check.value() };
		if (levelUp) {
			if (first + second >= GetLevelUINT())
				return {};
		}
		if (first) {
			ranks[first - 1]  += levelUp ? -1 : +1;
		}
		if (second) {
			ranks[second - 1] += levelUp ? -1 : +1;
		}
		ranks[first + second] += levelUp ? +1 : -1;
		if (levelUp) {
			Sea::SetCell(point, Cell::ship);
			return { Cell::ship };
		}
		else {
			Sea::SetCell(point, Cell::sea);
			return { Cell::sea };
		}
	}
	return {};
}
std::optional<std::wstring> Fleet::Cancel() const {
	if (auto check = Status(); check.has_value()) {
		auto [level, diff] {check.value()};
		std::wstring messing{ L"Too " };
		if (diff)
			messing += L"many ";
		else
			messing += L"few ";
		return
			messing + std::to_wstring(level) + L"-level ships";
	}
	else
		return {};
}
void Fleet::Random() {
	Sea::Fill(Cell::sea);
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
bool Fleet::CompareCell(
	const Point point,
	const Cell cell
) const {
	if (false == point.IsNan(GetMax())) {
		if (cell == Sea::GetCell(point)) {
			return true;
		}
	}
	return false;
}
bool Fleet::CompareShip(
	const Point point
) const {
	return
		CompareCell(point, Cell::ship);
}
bool Fleet::CompareSea(
	const Point point
) const {
	if (CheckSquare(point))
		return false;
	else {
		return CompareCell(point, Cell::sea);
	}
}
bool Fleet::CheckCorner(
	const Point point
) const {
	const bool comp[]{
		CompareShip(point.Up().Left()),
		CompareShip(point.Up().Right()),
		CompareShip(point.Down().Left()),
		CompareShip(point.Down().Right())
	};
	bool result = comp[0];
	for (UINT index = 1, size = std::size(comp); index < size; ++index) {
		result |= comp[index];
	}
	return result;
}
bool Fleet::CheckSquare(
	const Point point
) const {
	const bool comp[]{
		CompareShip(point.Up()),
		CompareShip(point.Down()),
		CompareShip(point.Left()),
		CompareShip(point.Right()),
	};
	bool result = CheckCorner(point);
	for (UINT index = 0, size = std::size(comp); index < size; ++index) {
		result |= comp[index];
	}
	return result;
}
UINT Fleet::CheckRaw(
	Compare compare,
	const Point prev,
	Direct direct
) const {
	Point next = (&prev->*direct)();
	if (false == next.IsNan(GetMax()))
		if ((this->*compare)(next))
			return CheckRaw(compare, next, direct) + 1;
	return 0;
}
std::optional<std::tuple<UINT, UINT, bool>> Fleet::CheckUp(
	const Point point
) const {
	if (CheckCorner(point)) {
		return {};
	}
	UINT first{
		CheckRaw(&Fleet::CompareShip, point, &Point::Up) +
		CheckRaw(&Fleet::CompareShip, point, &Point::Left)
	};
	UINT second{
		CheckRaw(&Fleet::CompareShip, point, &Point::Down) +
		CheckRaw(&Fleet::CompareShip, point, &Point::Right)
	};
	if (Cell::sea == Sea::GetCell(point)) {
		return { { first, second, true } };
	}
	else if (Cell::ship == Sea::GetCell(point)) {
		return { { first, second, false } };
	}
	else
		return {};
}
enum Direct {
	up,
	left,
	ver,
	hor
};
Point Fleet::GetCenter() const {
	Point point;
	do {
		point = Sea::GetRandPoint(Cell::sea);
	} while (CheckSquare(point));
	return point;
}
std::tuple<UINT, UINT, UINT, UINT> Fleet::GetRaw(
	const Point point
) const {
	UINT up   = CheckRaw(&Fleet::CompareSea, point, &Point::Up);
	UINT left = CheckRaw(&Fleet::CompareSea, point, &Point::Left);
	UINT ver  = CheckRaw(&Fleet::CompareSea, point, &Point::Down);
	UINT hor  = CheckRaw(&Fleet::CompareSea, point, &Point::Right);

	ver  = ver + up + 1;
	hor  = hor + left + 1;
	up   = point.Y() - up;
	left = point.X() - left;

	return { up, left, ver, hor };
}
std::tuple<Point, UINT, UINT, UINT, UINT> Fleet::GetPointRaw(
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
UINT Fleet::GetOffset(const UINT line, const Level level) const {
	UINT delta = line - static_cast<UINT>(level);
	delta = GetRandUINT(delta + 1);
	return delta;
}
std::pair<Point, Fleet::Direct> Fleet::GetPointDirect(
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
void Fleet::GetShip(const Level level) {
	auto [point, direct] = GetPointDirect(level);
	for (UINT index = 0, size = static_cast<UINT>(level);
		index < size; ++index) {
		Sea::SetCell(point, Cell::ship);
		point = (&point->*direct)();
	}
}
