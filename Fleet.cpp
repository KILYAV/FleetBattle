//#include <iostream>
#include "Fleet.h"

using namespace fleet;

Fleet::Fleet() :
	BaseBoard{ Cell::sea }
{
	ranks.resize(GetSizeUINT());
}
std::optional<std::pair<UINT, Diff>> Fleet::Status() const {
	auto max{ GetLevelUINT() };
	for (UINT index = 0, size = ranks.size(); index < size; ++index) {
		if (ranks[index] == max) {
			--max;
		}
		else {
			return { { max, ranks[index] > max ? Diff::up : Diff::down}};
		}
	}
	return {};
}
std::optional<Cell> Fleet::Manual(const Point point) {
	auto check{ Fleet::CheckLevel(point) };
	if (check) {
		auto& [index, diff] { check.value() };
		if (Diff::up == diff) {
			if (index.first + index.second >= GetLevelUINT())
				return {};
		}
		if (index.first) {
			ranks[index.first - 1] -= static_cast<int>(diff);
		}
		if (index.second) {
			ranks[index.second - 1] -= static_cast<int>(diff);
		}
		ranks[index.first + index.second] += static_cast<int>(diff);
		if (Diff::up == diff) {
			SetCell(point, Cell::ship);
			return { Cell::ship };
		}
		else {
			SetCell(point, Cell::sea);
			return { Cell::sea };
		}
	}
	return {};
}
void Fleet::Order() {
	Fill(Cell::sea);
}
void Fleet::BuildShip() {
	UINT count = GetCountCells(Cell::sea);
	UINT rand = RandUINT(count);
	Point point{ GepPointCellNumber(rand, Cell::sea) };
	CheckDiagonally(point);
}
std::optional<Fleet::variant> Fleet::CheckLevel(const Point point) const {
	if (false == CheckDiagonally(point)) {
		return {};
	}
	auto index{ CheckLines(point) };
	if (Cell::sea == GetCell(point)) {
		return { std::pair{ index, Diff::up } };
	}
	else if (Cell::ship == GetCell(point)) {
		return { std::pair{ index, Diff::down } };
	}
	else
		return {};
}
bool Fleet::CheckCross(const Point point) const {
	auto max{ GetMax() };
	if (point.X())
		if (Cell::ship == GetCell(point.Left()))
			return false;
	if (point.X() < max)
		if (Cell::ship == GetCell(point.Right()))
			return false;
	if (point.Y())
		if (Cell::ship == GetCell(point.Up()))
			return false;
	if (point.Y() < max)
		if (Cell::ship == GetCell(point.Down()))
			return false;
	return true;
}
bool Fleet::CheckDiagonally(const Point point) const {
	auto max{ GetMax() };
	if (point.Y() && point.X())
		if (Cell::ship == GetCell(point.Up().Left()))
			return false;
	if (point.Y() && (point.X() < max))
		if (Cell::ship == GetCell(point.Up().Right()))
			return false;
	if ((point.Y() < max) && point.X())
		if (Cell::ship == GetCell(point.Down().Left()))
			return false;
	if ((point.Y() < max) && (point.X() < max))
		if (Cell::ship == GetCell(point.Down().Right()))
			return false;
	return true;
}
std::pair<UINT, UINT> Fleet::CheckLines(const Point point) const {
	return { CheckUp(point) + CheckLeft(point),
		CheckDown(point) + CheckRight(point) };
}
UINT Fleet::CheckUp(const Point point) const {
	if (point.Y()) {
		if (Cell::ship == GetCell(point.Up())) {
			return CheckUp(point.Up()) + 1;
		}
	}
	return 0;
}
UINT Fleet::CheckDown(const Point point) const {
	if (point.Y() < GetMax()) {
		if (Cell::ship == GetCell(point.Down())) {
			return CheckDown(point.Down()) + 1;
		}
	}
	return 0;
}
UINT Fleet::CheckLeft(const Point point) const {
	if (point.X()) {
		if (Cell::ship == GetCell(point.Left())) {
			return CheckLeft(point.Left()) + 1;
		}
	}
	return 0;
}
UINT Fleet::CheckRight(const Point point) const {
	if (point.X() < GetMax()) {
		if (Cell::ship == GetCell(point.Right())) {
			return CheckRight(point.Right()) + 1;
		}
	}
	return 0;
}
