#pragma once
#include "Random.h"
#include "Frame.h"

#include <string>
#include <optional>

namespace fleet {
	using namespace domain;

	class Fleet :
		virtual Data,
		protected random::Random,
		protected frame::Frame
	{
	protected:
		Fleet(const HWND hWnd, const IDC IDC_FRAME);

		std::optional<std::pair<UINT, bool>> Status() const;
		std::optional<std::wstring> Cancel() const;

	private:
		std::vector<UINT>& Ranks() override;

		std::vector<UINT> ranks;
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
		virtual void ShotBack() = 0;
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
		void EnemyShot();
		void Fill() const;
	};

}
