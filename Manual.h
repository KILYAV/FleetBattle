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

		using OptionalPoints =
			std::optional<std::tuple<Point, Point, Point, Point>>;
		OptionalPoints LevelDown(
			const Point point
		);

		virtual void SetRanks(
			const UINT first,
			const UINT second,
			const bool level
		) = 0;
	private:
		std::optional<std::tuple<UINT, UINT, bool>> CheckUp(
			const Point point
		) const;
		std::optional<Point> GetEndPointRaw(
			const Direct_t direct,
			Point point
		) const;
	};
}