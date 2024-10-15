#pragma once
#include "Manual.h"

namespace random {
	using namespace domain;

	class Random :
		virtual Data,
		protected manual::Manual
	{
	protected:
		Random() = default;
		void Order();

	private:
		void GetShip(
			const Level level
		);

		std::pair<Point, Direct_t> GetPointDirect(
			const Level level
		) const;
		UINT GetOffset(
			const UINT line,
			const Level level
		) const;
		std::tuple<Point, UINT, UINT, UINT, UINT> GetPointRaw(
			const Level level
		) const;
		std::tuple<UINT, UINT, UINT, UINT> GetRaw(
			const Point center
		) const;
		Point GetCenter() const;

		virtual void ReRanks() = 0;
		virtual const std::vector<UINT>& GetRanks() const = 0;
	};
}
