#pragma once
#include "Compare.h"

#include <optional>

namespace random{
	class Random;
}

namespace manual {
	using namespace domain;
	
	class Manual :
		virtual Data,
		protected compare::Compare
	{
	protected:
		Manual() = default;
		std::optional<Cell> LevelUp(const Point point);

		using EndPoints =
			std::optional<std::tuple<Point, Point, Point, Point>>;
		EndPoints LevelDown(
			const Point point
		);

		virtual std::vector<UINT>& Ranks() = 0;
	private:
		std::optional<std::tuple<UINT, UINT, bool>> CheckUp(
			const Point point
		) const;
		std::optional<Point> GetEndPoint(
			const Point start,
			const Direct direct
		) const;
	};
}