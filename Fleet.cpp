#include "Fleet.h"

using namespace fleet;

struct OR {
	static bool Operator(bool lft, bool rht) {
		return lft || rht;
	}
};
struct AND {
	static bool Operator(bool lft, bool rht) {
		return lft && rht;
	}
};

std::vector<UINT>& Fleet::Ranks() {
	return ranks;
}

Fleet::Fleet(
	const HWND hWnd,
	const IDC IDC_FRAME
) :
	frame::Frame{ hWnd, IDC_FRAME }
{
	if (IDC::FRAMEALLIES == IDC_FRAME) {
		Frame::Fill(Cell::sea);
	}
	else {
		Frame::Fill(Cell::sky);
		EnableWindow(GetHWND(), false);
	}
	ranks.resize(GetLevelUINT());
}
std::optional<std::pair<UINT, bool>> Fleet::Status() const {
	auto max{ GetLevelUINT() };
	for (UINT index = 0, size = ranks.size(); index < size; ++index) {
		if (ranks[index] == max) {
			--max;
		}
		else {
			return { { max, ranks[index] > max } };
		}
	}
	return {};
}
std::optional<std::wstring> Fleet::Cancel() const {
	if (auto check = Status(); check.has_value()) {
		auto [level, diff] {check.value()};
		std::wstring messing{ L"Too " };
		if (diff)
			messing += L"many ";
		else
			messing += L"few ";
		return
			messing + std::to_wstring(level) + L"-level ships";
	}
	else
		return {};
}
void Enemy::LButtonDown(const LPARAM lParam) {
	auto point = GetPoint(lParam);
	if (Cell::sky != Sky::GetCell(point)) {
		return;
	}
	else if (Cell::sea == Sea::GetCell(point)) {
		Sky::SetCell(point, Cell::missle);
		Frame::SetCell(point, Cell::missle);
		ShotBack();
		return;
	}
	else {
		if (auto points = LevelDown(point); points)
			DeadBlast(points.value());
		HitBlast(point);
		return;
	}
}
void Allies::LButtonDown(const LPARAM lParam) {
	auto point{ GetPoint(lParam) };
	if (auto check{ LevelUp(point) }; check) {
		Frame::SetCell(point, check.value());
	}
}
void Allies::EnemyShot() {
	auto point = Sky::GetRandPoint(Cell::sky);
	if (Cell::sea == Sea::GetCell(point)) {
		Sky::SetCell(point, Cell::missle);
		Sea::SetCell(point, Cell::missle);
		Frame::SetCell(point, Cell::missle);
		return;
	}
}
void Allies::Fill() const {
	UINT size{ GetSizeUINT() };
	for (UINT x = 0; x < size; ++x) {
		for (UINT y = 0; y < size; ++y) {
			Frame::SetCell(Point{ x, y }, Sea::GetCell(Point{ x,y }));
		}
	}
}
