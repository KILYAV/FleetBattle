#pragma once
#include "Data.h"

#include <vector>

namespace board {
	using namespace domain;

	class Board :
		virtual Data
	{
	protected:
		explicit Board(
			const Cell cell
		);

		void Fill(
			const Cell cell
		);
		void SetCell(
			const Point point,
			const Cell cell
		);
		Cell GetCell(
			const Point point
		) const;
		Point GetRandPoint(
			const Cell cell
		) const;
		const std::vector<Cell>& Release() const {
			return board;
		};

	private:
		using Vector = std::vector<Cell>;

		Vector board;
	};

	class Sea :
		virtual Data,
		protected Board
	{
	protected:
		explicit Sea() :
			Board(Cell::sea) {};
	};

	class Sky :
		virtual Data,
		protected Board {
	protected:
		explicit Sky() :
			Board(Cell::sky) {};
	};
}