#pragma once
#include "Fleet.h"
#include "Frame.h"

//#include <string>

namespace fleet_battle {
	using namespace frame;

	class Enemy : virtual domain::Data, virtual board::Board,
		Draw, fleet::Fleet {
	protected:
		Enemy(const HWND hWnd);
		void LButtonDown(const LPARAM lParam) override;
	};

	class Allies : virtual domain::Data, virtual board::Board,
		Draw, protected fleet::Fleet {
	protected:
		Allies(const HWND hWnd);
		void LButtonDown(const LPARAM lParam) override;
	};

	class FleetBattle : virtual domain::Data, virtual board::Board,
		Main, Enemy, Allies {
	public:
		FleetBattle(const HINSTANCE hInstance);
	private:
		void Battle() override;
		void Random() override;
	};
}
