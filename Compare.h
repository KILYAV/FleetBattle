#pragma once
#include "Board.h"

#include <optional>

namespace compare {
	using namespace domain;

	class Compare :
		virtual Data,
		protected board::Board
	{
	protected:
		std::optional<bool> CompareCell(
			const Point point
		) const;
		bool WrapperCell(
			const Point point
		) const;
		bool CompareHor(
			const Point point
		) const;
		bool CompareVer(
			const Point point
		) const;
		bool CompareCorner(
			const Point point
		) const;
		bool CompareFace(
			const Point point
		) const;
		bool CompareSquare(
			const Point point
		) const;

		using Compare_t = bool (Compare::*)(const Point) const;
		using Direct_t = Point& (Point::*)();
		UINT GetLengthRaw(
			const Compare_t compare_f,
			const Direct_t direct_f,
			Point point
		) const;
		std::optional<Point> GetPointRaw(
			const Direct_t direct_f,
			Point point
		) const;
	};
}