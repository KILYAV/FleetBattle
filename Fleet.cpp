#include "Fleet.h"

using namespace fleet;

Fleet::Fleet(
	const HWND hWnd,
	const IDC IDC_FRAME
) :
	shot::Shot{ hWnd, IDC_FRAME }
{
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
void Fleet::Damage()
{
	if (target)
		;
	else
		RandomHit();
}
bool Fleet::RandomHit() {
	auto random = Sky::GetRandPoint(Cell::sky);
	if (Cell::sea == Sea::GetCell(random)) {
		Missed(random);
		return false;
	}
	else {
		MisledCorner(random);
		Blast(random);
		if (auto points = LevelDown(random); points) {
			MisledFace(points.value());
			return true;
		}
		else {
			;
		}
	}
}
void Fleet::SetRanks(
	const UINT first,
	const UINT second,
	const bool level
) {
	if (first) {
		ranks[first - 1] += level ? -1 : +1;
	}
	if (second) {
		ranks[second - 1] += level ? -1 : +1;
	}
	ranks[first + second] += level ? +1 : -1;
}
void Fleet::ReRanks() {
	for (UINT index = 0, size = GetLevelUINT(), count = size;
		index < size; ++index) {
		ranks[index] = count--;
	}
}
void Enemy::LButtonDown(
	const LPARAM lParam
) {
	auto point = GetPoint(lParam);
	if (Cell::sky != Sky::GetCell(point)) {
		return;
	}
	else if (Cell::sea == Sea::GetCell(point)) {
		Missed(point);
		ReturnedFire();
		return;
	}
	else {
		Blast(point);
		MisledCorner(point);
		if (auto points = LevelDown(point); points)
			MisledFace(points.value());
		return;
	}
}
Cell Enemy::GetCell(
	const Point point
) const {
	return Sky::GetCell(point);
}
void Allies::LButtonDown(const LPARAM lParam) {
	auto point{ GetPoint(lParam) };
	if (auto check{ LevelUp(point) }; check) {
		Frame::SetCell(point, check.value());
	}
}
Cell Allies::GetCell(
	const Point point
) const {
	return Sea::GetCell(point);
}
/*
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
			Missle(random);
			return;
		}
		else if (Cell::ship == Sea::GetCell(random)) {
			Missle(random);
			MissleCorner(random);
			if (auto points = LevelDown(random); points) {
				MissleFace(points.value());
				return EnemyShot();
			}
			return EnemyShot(random);
		}
	}
}
*/
