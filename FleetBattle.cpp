#include "FleetBattle.h"

#include <string>

using namespace fleet_battle;

Enemy::Enemy(const HWND hWnd) :
	PlayFrame{ hWnd, IDC::FRAMEENEMY }
{
	PlayFrame::Fill(Cell::sky);
};
void Enemy::LButtonDown(const LPARAM lParam) {

}
Allies::Allies(const HWND hWnd) :
	PlayFrame{ hWnd, IDC::FRAMEALLIES }
{
	PlayFrame::Fill(Cell::sea);
};
void Allies::LButtonDown(const LPARAM lParam) {
	using namespace domain;
	auto point{ GetPoint(lParam) };
	if (auto check{ Fleet::ChangLevel(point) }; check) {
		if (Diff::up == check.value()) {
			PlayFrame::SetCell(point, Cell::ship);
			Board::Sea::SetCell(point, Cell::ship);
		}
		else {
			PlayFrame::SetCell(point, Cell::sea);
			Board::Sea::SetCell(point, Cell::sea);
		}
	}
}
FleetBattle::FleetBattle(const HINSTANCE hInstance) :
	Data{ hInstance },
	MainFrame{},
	Enemy{ MainFrame::GetHWND() },
	Allies{ MainFrame::GetHWND() }
{};
void FleetBattle::Battle() const {
	if (auto check{ Allies::CheckFleet() }; check.has_value()) {
		auto [level, diff] {check.value()};
		std::wstring messeng{ L"Too " };
		if (Diff::down == diff)
			messeng += L"many ";
		else
			messeng += L"few ";
		messeng += std::to_wstring(level) + L"-level ships";
		MessageBox(MainFrame::GetHWND(), messeng.data(), L"Start fleet battle", MB_OK);
	}
}
/*
void FleetBattle::StartRound() {
	;
}
*/