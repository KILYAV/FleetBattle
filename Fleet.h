#pragma once
#include "Shot.h"

#include <string>
#include <optional>

namespace fleet {
	using namespace domain;

	class Fleet :
		virtual Data,
		protected shot::Shot
	{
	protected:
		Fleet(const HWND hWnd, const IDC IDC_FRAME);

		std::optional<std::pair<UINT, bool>> Status() const;
		std::optional<std::wstring> IsCancel() const;

		void Damage();
	private:
		bool SeriosHit();
		bool RandomHit(Point point = Point{});

		void SetRanks (
			const UINT first,
			const UINT second,
			const bool level
		) override;
		const std::vector<UINT>& GetRanks() const override {
			return ranks;
		}
		void ReRanks() override;

		std::vector<UINT> ranks;
		Target_t target;
	};

	class Enemy :
		virtual Data,
		protected Fleet
	{
	protected:
		Enemy(const HWND hWnd) :
			Fleet{ hWnd, IDC::FRAMEENEMY }
		{};

		void LButtonDown(const LPARAM lParam) override;

		virtual void ReturnedFire() = 0;
	private:
		Cell GetCell(
			const Point point
		) const override;
	};
	class Allies :
		virtual Data,
		protected Fleet
	{
	protected:
		Allies(const HWND hWnd) :
			Fleet{ hWnd, IDC::FRAMEALLIES }
		{};

		void LButtonDown(const LPARAM lParam) override;
	private:
		Cell GetCell(
			const Point point
		) const override;
	};

}
