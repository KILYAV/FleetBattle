//#include <iostream>
#include "Fleet.h"

using namespace fleet;

Fleet::Fleet() :
	BaseBoard{ Cell::sea },
	ranks{ GetLevelUINT() }
{}
std::optional<std::pair<UINT, Diff>> Fleet::Status() const {
	auto max{ GetLevelUINT() };
	for (UINT index = 0, size = ranks.size(); index < size; ++index) {
		if (ranks.at(index) == max) {
			--max;
		}
		else {
			return { { max, ranks.at(index) > max ? Diff::up : Diff::down } };
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
			ranks.at(index.first - 1) -= static_cast<int>(diff);
		}
		if (index.second) {
			ranks.at(index.second - 1) -= static_cast<int>(diff);
		}
		ranks.at(index.first + index.second) += static_cast<int>(diff);
		if (Diff::up == diff)
			return { Cell::ship };
		else
			return { Cell::sea };
	}
	return {};
}
void Fleet::Order() {
	Fill(Cell::sea);

}
void Fleet::BuildShip() {
	UINT count = GetCountCells(Cell::sea);
	UINT number = RandUINT(count);
	Point point{ };
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
bool Fleet::CheckDiagonally(const Point point) const {
	auto max{ GetMax() };
	if (point.X() && point.Y())
		if (Cell::ship == GetCell(point.Up().Left()))
			return false;
	if (point.X() && point.Y() < max)
		if (Cell::ship == GetCell(point.Up().Right()))
			return false;
	if (point.X() < max && point.Y())
		if (Cell::ship == GetCell(point.Down().Left()))
			return false;
	if (point.X() < max && point.Y() < max)
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
void Fleet::Rank::ReStart() {
	for (UINT index = 0, size = this->size(); index < size; ++index) {
		this->at(index) = size - index;
	}
}