#include "FleetBattle.h"

#include <string>

using namespace domain;
using namespace fleet_battle;

Enemy::Enemy(const HWND hWnd) :
	Draw{ hWnd, IDC::FRAMEENEMY }
{
	Draw::Fill(Cell::sky);
	EnableWindow(Enemy::GetHWND(), false);
};
void Enemy::LButtonDown(const LPARAM lParam) {
	auto point{ GetPoint(lParam) };
}
Allies::Allies(const HWND hWnd) :
	Draw{ hWnd, IDC::FRAMEALLIES }
{
	Draw::Fill(Cell::sea);
};
void Allies::LButtonDown(const LPARAM lParam) {
	auto point{ GetPoint(lParam) };
	if (auto check{ Fleet::Manual(point) }; check) {
		if (Cell::ship == check.value()) {
			Draw::SetCell(point, Cell::ship);
		}
		else {
			Draw::SetCell(point, Cell::sea);
		}
	}
}
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
	Enemy::Random();
	EnableWindow(Allies::GetHWND(), false);
	EnableWindow(Enemy::GetHWND(), true);
}
void FleetBattle::Random() {
	Allies::Random();
	Allies::Draw::Fill(Allies::Board::Release());
}