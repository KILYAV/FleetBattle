#include "Manual.h"

using namespace manual;

std::optional<Cell> Manual::LevelUp(
	const Point point
) {
	auto check{ CheckUp(point) };
	if (check) {
		auto& [first, second, level] { check.value() };
		if (level) {
			if (first + second >= GetLevelUINT())
				return {};
		}
		SetRanks(first, second, level);
		if (level) {
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
Manual::Target_t Manual::LevelDown(const Point point) {
	auto [first, second, level] { CheckUp(point).value() };
	SetRanks(first, second, level);
	
	UINT count{ 0 };
	std::array<Point, ends_points_size> result;
	if (auto optional{ GetPointRaw(&Point::North, point) }; optional)
		result[count++] = optional.value();
	if (auto optional{ GetPointRaw(&Point::South, point) }; optional)
		result[count++] = optional.value();
	if (auto optional{ GetPointRaw(&Point::West, point) }; optional)
		result[count++] = optional.value();
	if (auto optional{ GetPointRaw(&Point::East, point) }; optional)
		result[count++] = optional.value();

	return { result, count };
}
UINT Manual::GetLengthRaw(
	const Compare_t compare_f,
	const Direct_t direct_f,
	Point point
) const {
	UINT max = GetMaxUINT();
	UINT count{ 0 };
	(&point->*direct_f)();
	for (; point.IsNotNan(max); ++count) {
		if ((this->*compare_f)(point))
			(&point->*direct_f)();
		else
			return count;
	}
	return count;
}
std::optional<Point> Manual::GetPointRaw(
	const Direct_t direct_f,
	Point point
) const {
	UINT max = GetMaxUINT();
	(&point->*direct_f)();
	while (point.IsNotNan(max)) {
		switch (Sky::GetCell(point)) {
		case(Cell::blast):
			(&point->*direct_f)();
			break;
		case(Cell::sky):
			return point;
		default:
			return {};
		}
	}
	return {};
}
std::optional<std::tuple<UINT, UINT, bool>> Manual::CheckUp(
	const Point point
) const {
	if (CompareCorner(point)) {
		return {};
	}
	UINT first{
		GetLengthRaw(&Manual::WrapperCell, &Point::North, point) +
		GetLengthRaw(&Manual::WrapperCell, &Point::West, point)
	};
	UINT second{
		GetLengthRaw(&Manual::WrapperCell, &Point::South, point) +
		GetLengthRaw(&Manual::WrapperCell, &Point::East, point)
	};
	if (Cell::ship == Sea::GetCell(point)) {
		return { { first, second, false } };
	}
	else
		return { { first, second, true } };
}
bool Manual::WrapperCell(
	const Point point
) const {
	auto optional = CompareCell(point);
	return
		optional ? optional.value() : false;
}