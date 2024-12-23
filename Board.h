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
		Cell GetCell(
			const Point point
		) const;
		Point GetRandPoint(
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
		explicit Sea() :
			BaseBoard(Cell::sea) {};
	};

	class Sky :
		virtual Data,
		protected BaseBoard
	{
	protected:
		explicit Sky() :
			BaseBoard(Cell::sky) {};
	};

	class Board :
		virtual Data,
		protected Sea,
		protected Sky
	{
	protected:
		explicit Board() = default;
	};
}