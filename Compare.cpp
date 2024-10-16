#include "Compare.h"

using namespace compare;

bool OR(const std::optional<bool>* optional, const UINT size) {
	bool result = optional[0] ? optional[0].value() : false;
	for (UINT index = 1; index < size; ++index) {
		result = result || (optional[index] ? optional[index].value() : false);
	}
	return result;
}
std::optional<bool> Compare::CompareCell(
	const Point point
) const {
	if (point.IsNotNan(GetMaxUINT())) {
		if (Cell::ship == Sea::GetCell(point)) {
			return true;
		}
		else
			return false;
	}
	return {};
}
bool Compare::CompareCorner(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.North().West()),
		CompareCell(point.North().East()),
		CompareCell(point.South().West()),
		CompareCell(point.South().East())
	};
	return
		OR(optional, std::size(optional));
}
bool Compare::CompareFace(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.North()),
		CompareCell(point.South()),
		CompareCell(point.West()),
		CompareCell(point.East()),
	};
	return
		OR(optional, std::size(optional));
}
bool Compare::CompareHor(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.West()),
		CompareCell(point),
		CompareCell(point.East())
	};

	bool result{
		(optional[0] ? optional[0].value() : false) ||
		(optional[1] ? optional[1].value() : false) ||
		(optional[2] ? optional[2].value() : false)
	};
	return
		false == result;
}
bool Compare::CompareVer(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.North()),
		CompareCell(point),
		CompareCell(point.South())
	};

	bool result{
		(optional[0] ? optional[0].value() : false) ||
		(optional[1] ? optional[1].value() : false) ||
		(optional[2] ? optional[2].value() : false)
	};
	return
		false == result;
}
bool Compare::CompareSquare(
	const Point point
) const {
	return
		CompareCorner(point) || CompareFace(point);
<<<<<<< HEAD
=======
}
UINT Compare::GetLengthRaw(
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
std::optional<Point> Compare::GetPointRaw(
	const Direct_t direct_f,
	Point point
) const {
	UINT max = GetMaxUINT();
	(&point->*direct_f)();
	while (point.IsNotNan(max)) {
		if (Cell::blast == Sky::GetCell(point))
			(&point->*direct_f)();
		else
			return point;
	}
	return {};
>>>>>>> refs/remotes/origin/master
}