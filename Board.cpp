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
Cell BaseBoard::GetCell(const Point point) const {
	return board[point.Y() * GetSizeUINT() + point.X()];
}
Point BaseBoard::GetRandPoint(const Cell type) const {
	UINT count{ 0 };
	for (const auto& cell : board) {
		if (cell == type)
			++count;
	}

	UINT rand = GetRandUINT(count - 1);

	UINT number{ 0 };
	for (UINT ind = 0, size = board.size(); ind < size; ++ind) {
		if (type == board[ind]) {
			if (rand == number) {
				return Point{
					ind % GetSizeUINT(),
					ind / GetSizeUINT()
				};
			}
			++number;
		}
	}
}
