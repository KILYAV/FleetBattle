#include "Board.h"

using namespace domain;
using namespace board;

BaseBoard::BaseBoard(
	const Cell cell
) :
	board{ Vector{ GetSizeUINT() * GetSizeUINT(), cell }}
{}
void BaseBoard::Fill(const Cell cell) {
	for (auto& cell_ : board) {
		cell_ = cell;
	}
}
void BaseBoard::SetCell(const Point point, const Cell cell) {
	board[point.Y() * GetSizeUINT() + point.X()] = cell;
}
const Cell BaseBoard::GetCell(const Point point) const {
	return board[point.Y() * GetSizeUINT() + point.X()];
}
const UINT BaseBoard::GetCountCells(const Cell cell) const {
	UINT count{ 0 };
	for (auto& cell_ : board) {
		if (cell_ == cell)
			++count;
	}
	return count;
}

const Point BaseBoard::GepPoint(
	const UINT number, const Cell cell) const
{
	UINT count{ 0 };
	for (UINT ind = 0, size = board.size(); ind < size; ++ind) {
		if (cell == board[ind]) {
			if (number == count) {
				return Point{
					ind - ind / GetSizeUINT() * GetSizeUINT(),
					ind / GetSizeUINT()
				};
			}
			++count;
		}
	}
}
