#pragma once
#include "Data.h"

#include <vector>

namespace board {
	using namespace domain;

	class BaseBoard : virtual Data {
	public:
		void Fill(const Cell cell);
		void SetCell(const Point point, const Cell cell);
		const Cell GetCell(const Point point) const;
		const UINT CountCells(const Cell) const;

	protected:
		explicit BaseBoard(const Cell cell);

	private:
		std::vector<Cell> board;
	};

	class Sea : virtual Data, protected BaseBoard {
	protected:
		explicit Sea() : BaseBoard(Cell::sea) {};
	};

	class Sky : virtual Data, protected BaseBoard {
	protected:
		explicit Sky() : BaseBoard(Cell::sky) {};
	};

	class Board : virtual Data, protected Sea, protected Sky {
	protected:
		explicit Board() = default;
	};
}