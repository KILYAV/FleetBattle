#pragma once
#include "Fleet.h"
#include "Frame.h"

//#include <string>

namespace fleet_battle {
	using namespace domain;

	class Enemy :
		virtual domain::Data,
		protected frame::Draw,
		protected fleet::Fleet
	{
	protected:
		Enemy(const HWND hWnd);
		void LButtonDown(const LPARAM lParam) override;
	};

	class Allies :
		virtual domain::Data,
		protected frame::Draw,
		protected fleet::Fleet
	{
	protected:
		Allies(const HWND hWnd);
		void LButtonDown(const LPARAM lParam) override;
	public:
		void Fill() const;
	};

	class FleetBattle :
		virtual domain::Data,
		frame::Main,
		Enemy,
		Allies
	{
	public:
		FleetBattle(const HINSTANCE hInstance);
	private:
		void Battle() override;
		void Random() override;
	};
}
