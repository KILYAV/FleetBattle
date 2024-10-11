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
	if (Cell::sky != Sky::GetCell(point)) {
		return;
	}
	else if (Cell::sea == Sea::GetCell(point)) {
		Sky::SetCell(point, Cell::sea);
		Draw::SetCell(point, Cell::sea);
		return;
	}
	else {
		LevelUp(point);
		Blast(point);
		return;
	}
}
Allies::Allies(const HWND hWnd) :
	Draw{ hWnd, IDC::FRAMEALLIES }
{
	Draw::Fill(Cell::sea);
};
void Allies::LButtonDown(const LPARAM lParam) {
	auto point{ GetPoint(lParam) };
	if (auto check{ LevelUp(point) }; check) {
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
	Allies::Fill();
}
void Allies::Fill() const {
	UINT size{ GetSizeUINT() };
	for (UINT x = 0; x < size; ++x) {
		for (UINT y = 0; y < size; ++y) {
			Draw::SetCell(Point{ x, y }, Sea::GetCell(Point{ x,y }));
		}
	}
}
void Enemy::Blast(const Point point) {
	UINT max = GetMax();
	if (false == point.Up().Left().IsNan(max)) {
		Draw::SetCell(point.Up().Left(), Cell::sea);
	}
	if (false == point.Up().Right().IsNan(max)) {
		Draw::SetCell(point.Up().Right(), Cell::sea);
	}
	if (false == point.Down().Left().IsNan(max)) {
		Draw::SetCell(point.Down().Left(), Cell::sea);
	}
	if (false == point.Down().Right().IsNan(max)) {
		Draw::SetCell(point.Down().Right(), Cell::sea);
	}
	Draw::SetCell(point, Cell::ship);
}