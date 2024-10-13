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
void Fleet::SetCell(
	const Point point,
	const Cell cell
) {
	Sky::SetCell(point, cell);
	Sea::SetCell(point, cell);
	Frame::SetCell(point, cell);
}
void Fleet::HitBlast(
	const Point point
) {
	UINT max = GetMaxUINT();
	if (false == point.Up().Left().IsNan(max)) {
		SetCell(point.Up().Left(), Cell::missle);
	}
	if (false == point.Up().Right().IsNan(max)) {
		SetCell(point.Up().Right(), Cell::missle);
	}
	if (false == point.Down().Left().IsNan(max)) {
		SetCell(point.Down().Left(), Cell::missle);
	}
	if (false == point.Down().Right().IsNan(max)) {
		SetCell(point.Down().Right(), Cell::missle);
	}
	Frame::SetCell(point, Cell::blast);
}
void Fleet::DeadBlast(
	const std::tuple<Point, Point, Point, Point> points
) {
	enum Direct {
		up,
		down,
		left,
		right
	};
	UINT max = GetMaxUINT();
	if (false == std::get<up>(points).IsNan(max)) {
		SetCell(std::get<up>(points), Cell::missle);
	}
	if (false == std::get<down>(points).IsNan(max)) {
		SetCell(std::get<down>(points), Cell::missle);
	}
	if (false == std::get<left>(points).IsNan(max)) {
		SetCell(std::get<left>(points), Cell::missle);
	}
	if (false == std::get<right>(points).IsNan(max)) {
		SetCell(std::get<right>(points), Cell::missle);
	}
}
void Enemy::LButtonDown(const LPARAM lParam) {
	auto point = GetPoint(lParam);
	if (Cell::sky != Sky::GetCell(point)) {
		return;
	}
	else if (Cell::sea == Sea::GetCell(point)) {
		SetCell(point, Cell::missle);
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
void Allies::EnemyShot(
	std::optional<Point> point
) {
	enum Direct {
		up,
		down,
		left,
		right
	};
	if (point) {
		;
	}
	else {
		auto random = Sky::GetRandPoint(Cell::sky);
		if (Cell::sea == Sea::GetCell(random)) {
			SetCell(random, Cell::missle);
			return;
		}
		else if (Cell::ship == Sea::GetCell(random)) {
			SetCell(random, Cell::blast);
			if (auto points = LevelDown(random); points)
				DeadBlast(points.value());
			HitBlast(random);
			return EnemyShot(random);
		}
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
