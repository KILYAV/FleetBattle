#pragma once
#include "Fleet.h"
#include "Frame.h"

//#include <string>

namespace fleet_battle {
	using namespace domain;

	class FleetBattle :
		virtual domain::Data,
		frame::Main,
		protected fleet::Enemy,
		fleet::Allies
	{
	public:
		FleetBattle(const HINSTANCE hInstance);
	private:
		void Battle() override;
		void Random() override;
		void ReturnedFire() override;
	};
}
