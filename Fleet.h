#pragma once
#include "Board.h"

#include <optional>

namespace fleet {
	using namespace domain;

	class Check : virtual Data, virtual board::Board {
	protected:
		Check() = default;

		using variant = std::pair<std::pair<UINT, UINT>, Diff>;
		std::optional<variant> CheckLevel(const Point point) const;
	private:
		bool CellsDiagonally(const Point point) const;
		std::pair<UINT, UINT> CheckCellsVerHor(const Point point) const;

		UINT Above(const Point point) const;
		UINT Below(const Point point) const;
		UINT Right(const Point point) const;
		UINT Left(const Point point) const;

		UINT GetMax() const { return GetSizeUINT() - 1; };
	};
	class Fleet : virtual Data, virtual board::Board, Check {
	protected:
		Fleet();

		std::optional<Diff> ChangLevel(const Point point);
		std::optional<std::pair<UINT, Diff>> CheckFleet() const;
	private:
		std::vector<UINT> rank;
	};
}
