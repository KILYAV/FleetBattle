#pragma once
#include "Data.h"

#include <vector>

namespace board {
	using namespace domain;

	class BaseBoard :
		virtual Data
	{
	protected:
		explicit BaseBoard(
			const Cell cell
		);

		void Fill(
			const Cell cell
		);
		void SetCell(
			const Point point,
			const Cell cell
		);
		const Cell GetCell(
			const Point point
		) const;
		const UINT CountCells(
			const Cell
		) const;
		const Point GepPointCellNumber(
			const UINT number,
			const Cell cell
		) const;

	private:
		using Vector = std::vector<Cell>;

		Vector board;
	};

	class Sea :
		virtual Data,
		protected BaseBoard
	{
	protected:
		explicit Sea(Frame&& frame) :
			BaseBoard(std::move(frame), Cell::sea) {};
	};

	class Sky :
		virtual Data,
		protected BaseBoard {
	protected:
		explicit Sky(Frame&& frame) :
			BaseBoard(std::move(frame), Cell::sky) {};
	};

	class Board :
		virtual Data,
		protected Sea,
		protected Sky {
	protected:
		explicit Board(Frame&& sea, Frame&& sky) :
			Sea{ std::move(sea) },
			Sky{ std::move(sky) }
		{}
	};
}