#pragma once
#include "Board.h"

#include <string>
#include <optional>

namespace fleet {
	using namespace domain;

	class Fleet :
		virtual Data,
		protected board::Board
	{
	protected:
		Fleet();

		std::optional<std::pair<UINT, bool>> Status() const;
		std::optional<Cell> LevelUp(const Point point);
		bool LevelDown(const Point point);

		std::optional<std::wstring> Cancel() const;
		void Random();

	private:
		template<class Board_tmp>
		bool CompareCell(
			const Point point,
			const Cell cell
		) const;
		bool CompareSea(
			const Point point,
			const Cell cell
		) const;

		template<class Board_tmp, class Combination>
		bool CheckCorner(
			const Point point,
			const Cell cell
		) const;
		template<class Board_tmp, class Combination>
		bool CheckFace(
			const Point point,
			const Cell cell
		) const;
		template<class Board_tmp, class Combination>
		bool CheckSquare(
			const Point point,
			const Cell cell
		) const;

		using Compare = bool (Fleet::*)(const Point, const Cell) const;
		using Direct = Point(Point::*)() const;
		UINT CheckRaw(
			const Compare compare,
			const Cell cell,
			const Point prev,
			const Direct direct
		) const;

		std::optional<std::tuple<UINT, UINT, bool>> CheckUp(
			const Point point
		) const;

		Point GetCenter() const;
		std::tuple<UINT, UINT, UINT, UINT> GetRaw(const Point center) const;
		std::tuple<Point, UINT, UINT, UINT, UINT> GetPointRaw(
			const Level level
		) const;
		UINT GetOffset(
			const UINT line,
			const Level level
		) const;
		std::pair<Point, Direct> GetPointDirect(const Level level) const;
		void GetShip(const Level level);

		std::vector<UINT> ranks;
	};
}
