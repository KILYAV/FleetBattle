#pragma once
#include "Compare.h"

#include <array>
#include <optional>

namespace random{
	class Random;
}

namespace manual {
	using namespace domain;
	constexpr UINT ends_points_size = 4;
	
	class Manual :
		virtual Data,
		protected compare::Compare
	{
	protected:
		Manual() = default;
		std::optional<Cell> LevelUp(const Point point);

		static const uint64_t target_size = 4;
		using Points_t = std::array<Point, target_size>;
		struct Target_t {
			Points_t points;
			UINT count;
		};
		Target_t LevelDown(
			const Point point
		);

		virtual void SetRanks(
			const UINT first,
			const UINT second,
			const bool level
		) = 0;

		using Compare_t = bool (Manual::*)(const Point) const;
		using Direct_t = Point & (Point::*)();

		UINT GetLengthRaw(
			const Compare_t compare_f,
			const Direct_t direct_f,
			Point point
		) const;
		std::optional<Point> GetPointRaw(
			const Direct_t direct_f,
			Point point
		) const;
	private:
		std::optional<std::tuple<UINT, UINT, bool>> CheckUp(
			const Point point
		) const;

		bool WrapperCell(
			const Point point
		) const;
	};
}