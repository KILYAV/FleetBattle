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
Manual::OptionalPoints Manual::LevelDown(const Point point) {
	auto [first, second, level] { CheckUp(point).value() };
	SetRanks(first, second, level);

	std::optional<Point> up = GetEndPointRaw(&Point::Up, point);
	std::optional<Point> down = GetEndPointRaw(&Point::Down, point);
	std::optional<Point> left = GetEndPointRaw(&Point::Left, point);
	std::optional<Point> right = GetEndPointRaw(&Point::Right, point);

	if (up && down && left && right)
		return std::tuple{ up.value(), down.value(), left.value(), right.value() };

	return {};
}
std::optional<std::tuple<UINT, UINT, bool>> Manual::CheckUp(
	const Point point
) const {
	if (CompareCorner(point)) {
		return {};
	}
	UINT first{
		GetLengthRaw(&Manual::WrapperCell, &Point::Up, point) +
		GetLengthRaw(&Manual::WrapperCell, &Point::Left, point)
	};
	UINT second{
		GetLengthRaw(&Manual::WrapperCell, &Point::Down, point) +
		GetLengthRaw(&Manual::WrapperCell, &Point::Right, point)
	};
	if (Cell::ship == Sea::GetCell(point)) {
		return { { first, second, false } };
	}
	else
		return { { first, second, true } };
}
std::optional<Point> Manual::GetEndPointRaw(
	const Direct_t direct,
	Point point
) const {
	auto optional{ GetPointRaw(direct, point) };
	if (optional) {
		point = optional.value();
		if (Cell::sky == Sky::GetCell(point)) {
			if (Cell::sea == Sea::GetCell(point)) {
				return optional;
			}
			else {
				return Point{};
			}
		}
	}
	return Point{};
}