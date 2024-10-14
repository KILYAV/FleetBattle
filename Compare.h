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
		using Direct_t = Point (Point::*)() const;
		UINT LengthRaw(
			const Compare_t compare_f,
			const Point start,
			const Direct_t direct_f
		) const;
	};
}