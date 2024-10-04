#include "FleetBattle.h"

#include <string>

using namespace fleet_battle;

Enemy::Enemy(const HWND hWnd) :
	Draw{ hWnd, IDC::FRAMEENEMY }
{
	Draw::Fill(Cell::sky);
};
void Enemy::LButtonDown(const LPARAM lParam) {

}
Allies::Allies(const HWND hWnd) :
	Draw{ hWnd, IDC::FRAMEALLIES }
{
	Draw::Fill(Cell::sea);
};
void Allies::LButtonDown(const LPARAM lParam) {
	using namespace domain;
	auto point{ GetPoint(lParam) };
	if (auto check{ Fleet::Manual(point) }; check) {
		if (Cell::ship == check.value()) {
			Draw::SetCell(point, Cell::ship);
			Board::Sea::SetCell(point, Cell::ship);
		}
		else {
			Draw::SetCell(point, Cell::sea);
			Board::Sea::SetCell(point, Cell::sea);
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
	if (auto check{ Allies::Status() }; check.has_value()) {
		auto [level, diff] {check.value()};
		std::wstring messing{ L"Too " };
		if (Diff::down == diff)
			messing += L"many ";
		else
			messing += L"few ";
		messing += std::to_wstring(level) + L"-level ships";
		MessageBox(Main::GetHWND(), messing.data(), L"Start fleet battle", MB_OK);
	}
}
void FleetBattle::Random() {
	//Allies::Order();
}