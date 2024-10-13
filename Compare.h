#pragma once
#include "Board.h"

namespace compare {
	using namespace domain;

	class Compare :
		virtual Data,
		protected board::Board
	{
	protected:
		template<class Board_tmp>
		bool CompareCell(
			const Point point
		) const;
		template<class Board_tmp, class Direct_ptr>
		bool CompareTrip(
			const Point point
		) const;

		template<class Board_tmp>
		bool CompareCorner(
			const Point point
		) const;
		template<class Board_tmp>
		bool CompareFace(
			const Point point
		) const;
		template<class Board_tmp>
		bool CompareSquare(
			const Point point
		) const;

		using CompFunc = bool (Compare::*)(const Point) const;
		using Direct = Point (Point::*)() const;
		UINT LengthRaw(
			const CompFunc comp_func,
			const Point start,
			const Direct direct
		) const;
	};

	template<class Board_tmp>
	bool Compare::CompareCell(
		const Point point
	) const {
		if (false == point.IsNan(GetMaxUINT())) {
			if (Cell::ship == Board_tmp::GetCell(point)) {
				return true;
			}
		}
		return false;
	}
	template<class Board_tmp, class Direct_ptr>
	bool Compare::CompareTrip(
		const Point point
	) const {
		bool result{
			CompareCell<Board_tmp>(Direct_ptr::First(point)) ||
			CompareCell<Board_tmp>(Direct_ptr::Second(point)) ||
			CompareCell<Board_tmp>(Direct_ptr::Third(point))
		};
		return
			false == result;
	}

	template<class Board_tmp>
	bool Compare::CompareCorner(
		const Point point
	) const {
		const bool comp[]{
			CompareCell<Board_tmp>(point.Up().Left()),
			CompareCell<Board_tmp>(point.Up().Right()),
			CompareCell<Board_tmp>(point.Down().Left()),
			CompareCell<Board_tmp>(point.Down().Right())
		};
		bool result = comp[0];
		for (UINT index = 1, size = std::size(comp); index < size; ++index) {
			result |= comp[index];
		}
		return result;
	}
	template<class Board_tmp>
	bool Compare::CompareFace(
		const Point point
	) const {
		const bool comp[]{
			CompareCell<Board_tmp>(point.Up()),
			CompareCell<Board_tmp>(point.Down()),
			CompareCell<Board_tmp>(point.Left()),
			CompareCell<Board_tmp>(point.Right()),
		};
		bool result = comp[0];
		for (UINT index = 1, size = std::size(comp); index < size; ++index) {
			result |= comp[index];
		}
		return result;
	}
	template<class Board_tmp>
	bool Compare::CompareSquare(
		const Point point
	) const {
		return
			CompareCorner<Board_tmp>(point) ||
			CompareFace<Board_tmp>(point);
	}

	struct HOR {
		static Point First(const Point point) {
			return point.Left();
		}
		static Point Second(const Point point) {
			return point;
		}
		static Point Third(const Point point) {
			return point.Right();
		}
	};
	struct VER {
		static Point First(const Point point) {
			return point.Up();
		}
		static Point Second(const Point point) {
			return point;
		}
		static Point Third(const Point point) {
			return point.Down();
		}
	};
}