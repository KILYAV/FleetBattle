#include "Board.h"

using namespace domain;
using namespace board;

BaseBoard::BaseBoard(const Cell cell) :
	board{ std::vector<Cell>{ GetSizeUINT() * GetSizeUINT(), cell }}
{}
void BaseBoard::Fill(const Cell cell) {
	for (auto& cell_ : board) {
		cell_ = cell;
	}
}
void BaseBoard::SetCell(const Point point, const Cell cell) {
	board[point.y * GetSizeUINT() + point.x] = cell;
}
const Cell BaseBoard::GetCell(const Point point) const {
	return board[point.y * GetSizeUINT() + point.x];
}
const UINT BaseBoard::CountCells(const Cell cell) const {
	UINT count{ 0 };
	for (auto& cell_ : board) {
		if (cell_ == cell)
			++count;
	}
	return count;
}