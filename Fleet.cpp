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
std::optional<std::pair<UINT, bool>> Fleet::IsComplete() const {
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
std::optional<std::wstring> Fleet::IsCancel() const {
	if (auto check = IsComplete(); check.has_value()) {
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
bool Fleet::IsLoss() const {
	UINT total{ 0 };
	for (auto count : ranks) {
		total += count;
	}
	return
		false == static_cast<bool>(total);
}
bool Fleet::Damage()
{
	if (target.count) {
		if (SeriesHit())
			Damage();
	}
	else {
		if (RandomHit())
			Damage();
	}
}
std::optional<bool> Fleet::RandomHit(Point random) {
	if (random.IsNan())
		random = Sky::GetRandPoint(Cell::sky);

	if (Cell::sea == Sea::GetCell(random)) {
		MissedCell(random);
		return {};
	}
	else {
		Sleep(300);
		MisledCorner(random);
		BlastCell(random);
		auto target { LevelDown(random) };
		if (target.count) {
			if (IsTarget(target)) {
				Fleet::target = target;
			}
			else {
				MisledFace(target);
				Fleet::target.count = 0;
			}
		}
		return true;
	}
}
bool Fleet::SeriesHit() {
	UINT index = GetRandUINT(target.count - 1);
	Point point{ target.points[index] };
	target.points[index] = target.points[target.count - 1];
	--target.count;

	return RandomHit(point);
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
		MissedCell(point);
		ReturnedFire();
		return;
	}
	else {
		BlastCell(point);
		MisledCorner(point);
		auto target { LevelDown(point) };
		if (target.count) {
			if (IsNotTarget(target))
				MisledFace(target);
		}
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