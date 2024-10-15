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
bool Compare::WrapperCell(
	const Point point
) const {
	auto optional = CompareCell(point);
	return
		optional ? optional.value() : false;
}
bool Compare::CompareCorner(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.Up().Left()),
		CompareCell(point.Up().Right()),
		CompareCell(point.Down().Left()),
		CompareCell(point.Down().Right())
	};
	return
		OR(optional, std::size(optional));
}
bool Compare::CompareFace(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.Up()),
		CompareCell(point.Down()),
		CompareCell(point.Left()),
		CompareCell(point.Right()),
	};
	return
		OR(optional, std::size(optional));
}
bool Compare::CompareHor(
	const Point point
) const {
	std::optional<bool> optional[]{
		CompareCell(point.Left()),
		CompareCell(point),
		CompareCell(point.Right())
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
		CompareCell(point.Up()),
		CompareCell(point),
		CompareCell(point.Down())
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
}
UINT Compare::GetLengthRaw(
	const Compare_t compare_f,
	const Direct_t direct_f,
	Point point
) const {
	UINT max = GetMaxUINT();
	UINT count{ 0 };
	(&point->*direct_f)();
	if (point.IsNotNan(max))
		while ((this->*compare_f)(point)) {
			++count;
			(&point->*direct_f)();
			if (point.IsNan(max))
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
	if (point.IsNotNan(max)) {
		while (Cell::blast == Sky::GetCell(point)) {
			(&point->*direct_f)();
			if (point.IsNan(max)) {
				return Point{};
			}
		}
		return point;
	}
	return {};
}