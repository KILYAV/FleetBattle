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
		auto& ranks{ Ranks() };
		if (first) {
			ranks[first - 1] += level ? -1 : +1;
		}
		if (second) {
			ranks[second - 1] += level ? -1 : +1;
		}
		ranks[first + second] += level ? +1 : -1;
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
Manual::EndPoints Manual::LevelDown(const Point point) {
	auto [first, second, level] { CheckUp(point).value() };
	auto& ranks{ Ranks() };
	if (first) {
		--ranks[first - 1];
	}
	if (second) {
		--ranks[second - 1];
	}
	++ranks[first + second];

	Sea::SetCell(point, Cell::sea);
	Sky::SetCell(point, Cell::ship);

	Point up = GetEndPoint(point, &Point::Up);
	Point down = GetEndPoint(point, &Point::Down);
	Point left = GetEndPoint(point, &Point::Left);
	Point right = GetEndPoint(point, &Point::Right);

	if (((false == up.IsNan()) && (false == down.IsNan())) ||
		((false == left.IsNan()) && (false == right.IsNan())))
		return { { up, down, left, right } };

	return {};
}
std::optional<std::tuple<UINT, UINT, bool>> Manual::CheckUp(
	const Point point
) const {
	if (CompareCorner<Sea>(point)) {
		return {};
	}
	UINT first{
		LengthRaw(&Manual::CompareCell<Sea>, point, &Point::Up) +
		LengthRaw(&Manual::CompareCell<Sea>, point, &Point::Left)
	};
	UINT second{
		LengthRaw(&Manual::CompareCell<Sea>, point, &Point::Down) +
		LengthRaw(&Manual::CompareCell<Sea>, point, &Point::Right)
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
Point Manual::GetEndPoint(
	const Point start,
	const Direct direct
) const {
	UINT max = GetMaxUINT();
	Point point = (&start->*direct)();
	if (false == point.IsNan(max)) {
		while (Cell::ship == Sky::GetCell(point)) {
			point = (&point->*direct)();
			if (false == point.IsNan(max)) {
				return Point{};
			}
		}
		if (Cell::ship == Sea::GetCell(point)) {
			return Point{};
		}
		else {
			return point;
		}

	}
	return Point{};
}