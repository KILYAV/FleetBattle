#include "FleetBattle.h"

#include <string>

using namespace domain;
using namespace fleet_battle;

FleetBattle::FleetBattle(const HINSTANCE hInstance) :
	Data{ hInstance },
	Main{},
	Enemy{ Main::GetHWND() },
	Allies{ Main::GetHWND() }
{
	Enemy::Frame::Fill();
	Allies::Frame::Fill();
	EnableWindow(Enemy::GetHWND(), false);
};
void FleetBattle::Battle() {
	if (auto wstring_opt = Allies::IsCancel(); wstring_opt) {
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
	Allies::Frame::Fill();
}
bool FleetBattle::ReturnedFire() {
	Allies::Damage();
}
