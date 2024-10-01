//#include <iostream>
#include "Fleet.h"

using namespace fleet;

std::optional<Check::variant> Check::CheckLevel(const Point point) const {
	if (false == CellsDiagonally(point)) {
		return {};
	}
	auto index{ CheckCellsVerHor(point) };
	if (Cell::sea == Sea::GetCell(point)) {
		return { std::pair{ index, Diff::up } };
	}
	else if (Cell::ship == Sea::GetCell(point)) {
		return { std::pair{ index, Diff::down } };
	}
}
bool Check::CellsDiagonally(const Point point) const {
	auto max{ GetMax() };
	if (point.x && point.y)
		if (Cell::ship == Sea::GetCell(Point{ point.x - 1, point.y - 1 }))
			return false;
	if (point.x && point.y < max)
		if (Cell::ship == Sea::GetCell(Point{ point.x - 1, point.y + 1 }))
			return false;
	if (point.x < max && point.y)
		if (Cell::ship == Sea::GetCell(Point{ point.x + 1, point.y - 1 }))
			return false;
	if (point.x < max && point.y < max)
		if (Cell::ship == Sea::GetCell(Point{ point.x + 1, point.y + 1 }))
			return false;
	return true;
}
std::pair<UINT, UINT> Check::CheckCellsVerHor(const Point point) const {
	return { Above(point) + Left(point),
		Below(point) + Right(point) };
}
UINT Check::Above(const Point point) const {
	if (point.y) {
		if (Cell::ship == Sea::GetCell(Point{ point.x, point.y - 1 })) {
			return Above(Point{ point.x, point.y - 1 }) + 1;
		}
	}
	return 0;
}
UINT Check::Below(const Point point) const {
	if (point.y < GetMax()) {
		if (Cell::ship == Sea::GetCell(Point{ point.x, point.y + 1 })) {
			return Below(Point{ point.x, point.y + 1 }) + 1;
		}
	}
	return 0;
}
UINT Check::Left(const Point point) const {
	if (point.x) {
		if (Cell::ship == Sea::GetCell(Point{ point.x - 1, point.y })) {
			return Left(Point{ point.x - 1, point.y }) + 1;
		}
	}
	return 0;
}
UINT Check::Right(const Point point) const {
	if (point.x < GetMax()) {
		if (Cell::ship == Sea::GetCell(Point{ point.x + 1, point.y })) {
			return Right(Point{ point.x + 1, point.y }) + 1;
		}
	}
	return 0;
}
Fleet::Fleet() {
	rank.resize(GetLevelUINT());
}
std::optional<Diff> Fleet::ChangLevel(const Point point) {
	auto check{ Check::CheckLevel(point) };
	if (check) {
		auto& [index, diff]{ check.value() };
		if (Diff::up == diff) {
			if (index.first + index.second >= GetLevelUINT())
				return {};
		}
		if (index.first) {
			rank[index.first - 1] -= static_cast<int>(diff);
		}
		if (index.second) {
			rank[index.second - 1] -= static_cast<int>(diff);
		}
		rank[index.first + index.second] += static_cast<int>(diff);
		return { diff };
	}
	return {};
}
std::optional<std::pair<UINT, Diff>> Fleet::CheckFleet() const {
	auto max{ GetLevelUINT() };
	for (auto count : rank) {
		if (count == max) {
			--max;				
		}
		else {
			return { { max, count > max ? Diff::up : Diff::down } };
		}
	}
	return {};
}
