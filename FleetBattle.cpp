#include "FleetBattle.h"

#include <string>

using namespace domain;
using namespace fleet_battle;

FleetBattle::FleetBattle(const HINSTANCE hInstance) :
	Data{ hInstance },
	Main{},
	Enemy{ Main::GetHWND() },
	Allies{ Main::GetHWND() }
{};
void FleetBattle::Battle() {
	if (auto wstring_opt = Allies::Cancel(); wstring_opt) {
		MessageBox(
			Main::GetHWND(),
			wstring_opt.value().data(),
			L"Start fleet battle",
			MB_OK
		);
		return;
	}
	Enemy::Order();
	EnableWindow(Allies::GetHWND(), false);
	EnableWindow(Enemy::GetHWND(), true);
}
void FleetBattle::Random() {
	Allies::Order();
	Allies::Fill();
}
void FleetBattle::ShotBack() {
	Allies::EnemyShot();
}