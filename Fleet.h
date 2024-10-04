#pragma once
#include "Board.h"

#include <optional>

namespace fleet {
	using namespace domain;

	class Fleet : virtual Data, protected board::BaseBoard {
	protected:
		Fleet();

		std::optional<std::pair<UINT, Diff>> Status() const;
		std::optional<Cell> Manual(const Point point);
		void Order();
	private:
		using variant = std::pair<std::pair<UINT, UINT>, Diff>;
		std::optional<variant> CheckLevel(const Point point) const;

		bool CheckDiagonally(const Point point) const;
		std::pair<UINT, UINT> CheckLines(const Point point) const;

		UINT CheckUp(const Point point) const;
		UINT CheckDown(const Point point) const;
		UINT CheckRight(const Point point) const;
		UINT CheckLeft(const Point point) const;

		UINT GetMax() const { return GetSizeUINT() - 1; };

		void BuildShip();

		class Rank :
			std::vector<UINT>
		{
		private:
			using vector = std::vector<UINT>;
		public:
			using vector::at;
			using vector::size;

			Rank(UINT size) :
				vector{ size }
			{};
			void ReStart();
		};

		Rank ranks;
	};
}
