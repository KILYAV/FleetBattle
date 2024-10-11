//#include <iostream>
#include "Fleet.h"

using namespace fleet;

enum Direct {
	up,
	left,
	ver,
	hor
};

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

Fleet::Fleet()
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
std::optional<Cell> Fleet::LevelUp(
	const Point point
) {
	auto check{ CheckUp(point) };
	if (check) {
		auto& [first, second, level] { check.value() };
		if (level) {
			if (first + second >= GetLevelUINT())
				return {};
		}
		if (first) {
			ranks[first - 1]  += level ? -1 : +1;
		}
		if (second) {
			ranks[second - 1] += level ? -1 : +1;
		}
		ranks[first + second] += level ? +1 : -1;
		if (level) {
			Sea::SetCell(point, Cell::ship);
			return { Cell::ship };
		}
		else {
			Sea::SetCell(point, Cell::sea);
			return { Cell::sea };
		}
	}
	return {};
}
bool Fleet::LevelDown(const Point point) {
	auto [first, second, level] { CheckUp(point).value() };
	if (first) {
		--ranks[first - 1];
	}
	if (second) {
		--ranks[second - 1];
	}
	++ranks[first + second];

	Sea::SetCell(point, Cell::sea);
	Sky::SetCell(point, Cell::ship);

	if (false == CheckFace<Sky, OR>(point, Cell::ship))
		if (false == CheckFace<Sea, OR>(point, Cell::ship))
			return true;

	return false;
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
void Fleet::Random() {
	Sea::Fill(Cell::sea);
	for (UINT index = 0, size = GetLevelUINT(), count = size;
		index < size; ++index) {
		ranks[index] = count--;
	}

	for (UINT level = ranks.size(); level > 0; --level) {
		for (UINT number = 0, count = ranks[level - 1]; number < count; ++number) {
			GetShip(static_cast<Level>(level));
		}
	}
}
template<class Board_tmp>
bool Fleet::CompareCell(
	const Point point,
	const Cell cell
) const {
	if (false == point.IsNan(GetMaxUINT())) {
		if (cell == Board_tmp::GetCell(point)) {
			return true;
		}
	}
	return false;
}
bool Fleet::CompareSea(
	const Point point,
	const Cell cell
) const {
	if (CheckSquare<Sea, OR>(point, Cell::ship))
		return false;
	else {
		return CompareCell<Sea>(point, Cell::sea);
	}
}
template<class Board_tmp, class Combination>
bool Fleet::CheckCorner(
	const Point point,
	const Cell cell
) const {
	const bool comp[]{
		CompareCell<Board_tmp>(point.Up().Left(),    cell),
		CompareCell<Board_tmp>(point.Up().Right(),   cell),
		CompareCell<Board_tmp>(point.Down().Left(),  cell),
		CompareCell<Board_tmp>(point.Down().Right(), cell)
	};
	bool result = comp[0];
	for (UINT index = 1, size = std::size(comp); index < size; ++index) {
		result = Combination::Operator(result, comp[index]);
	}
	return result;
}
template<class Board_tmp, class Combination>
bool Fleet::CheckFace(
	const Point point,
	const Cell cell
) const {
	const bool comp[]{
		CompareCell<Board_tmp>(point.Up(),    cell),
		CompareCell<Board_tmp>(point.Down(),  cell),
		CompareCell<Board_tmp>(point.Left(),  cell),
		CompareCell<Board_tmp>(point.Right(), cell),
	};
	bool result = comp[0];
	for (UINT index = 1, size = std::size(comp); index < size; ++index) {
		result = Combination::Operator(result, comp[index]);
	}
	return result;
}
template<class Board_tmp, class Combination>
bool Fleet::CheckSquare(
	const Point point,
	const Cell cell
) const {
	return 
		Combination::Operator(
			CheckCorner<Board_tmp, Combination>(point, cell),
			CheckFace<Board_tmp, Combination>(point, cell)
		);
}
UINT Fleet::CheckRaw(
	const Compare compare,
	const Cell cell,
	const Point prev,
	const Direct direct
) const {
	Point point = (&prev->*direct)();
	if (false == point.IsNan(GetMaxUINT()))
		if ((this->*compare)(point, cell))
			return CheckRaw(compare, cell, point, direct) + 1;
	return 0;
}
std::optional<std::tuple<UINT, UINT, bool>> Fleet::CheckUp(
	const Point point
) const {
	if (CheckCorner<Sea, OR>(point, Cell::ship)) {
		return {};
	}
	UINT first{
		CheckRaw(&Fleet::CompareCell<Sea>, Cell::ship, point, &Point::Up) +
		CheckRaw(&Fleet::CompareCell<Sea>, Cell::ship, point, &Point::Left)
	};
	UINT second{
		CheckRaw(&Fleet::CompareCell<Sea>, Cell::ship, point, &Point::Down) +
		CheckRaw(&Fleet::CompareCell<Sea>, Cell::ship, point, &Point::Right)
	};
	if (Cell::sea == Sea::GetCell(point)) {
		return { { first, second, true } };
	}
	else if (Cell::ship == Sea::GetCell(point)) {
		return { { first, second, false } };
	}
	else
		return {};
}
Point Fleet::GetCenter() const {
	Point point;
	do {
		point = Sea::GetRandPoint(Cell::sea);
	} while (CheckSquare<Sea, OR>(point, Cell::ship));
	return point;
}
std::tuple<UINT, UINT, UINT, UINT> Fleet::GetRaw(
	const Point point
) const {
	UINT up   = CheckRaw(&Fleet::CompareSea, Cell::ship, point, &Point::Up);
	UINT left = CheckRaw(&Fleet::CompareSea, Cell::ship, point, &Point::Left);
	UINT ver  = CheckRaw(&Fleet::CompareSea, Cell::ship, point, &Point::Down);
	UINT hor  = CheckRaw(&Fleet::CompareSea, Cell::ship, point, &Point::Right);

	ver  = ver + up + 1;
	hor  = hor + left + 1;
	up   = point.Y() - up;
	left = point.X() - left;

	return { up, left, ver, hor };
}
std::tuple<Point, UINT, UINT, UINT, UINT> Fleet::GetPointRaw(
	const Level level
) const {
	Point center;
	std::tuple<UINT, UINT, UINT, UINT> tuple;
	do {
		center = GetCenter();
		tuple = GetRaw(center);
	} while (
		(static_cast<UINT>(level) > std::get<ver>(tuple)) &&
		(static_cast<UINT>(level) > std::get<hor>(tuple))
		);
	return {
		center,
		std::get<up>(tuple),
		std::get<left>(tuple),
		std::get<ver>(tuple),
		std::get<hor>(tuple)
	};
}
UINT Fleet::GetOffset(const UINT line, const Level level) const {
	UINT delta = line - static_cast<UINT>(level);
	delta = GetRandUINT(delta + 1);
	return delta;
}
std::pair<Point, Fleet::Direct> Fleet::GetPointDirect(
	const Level level
) const {
	auto [center, up, left, ver, hor] {GetPointRaw(level)};

	UINT deltaX = center.X();
	UINT deltaY = center.Y();
	Direct direct = nullptr;
	if (hor < static_cast<UINT>(level)) {
		deltaY = up + GetOffset(ver, level);
		direct = &Point::Down;
	}
	else if (ver < static_cast<UINT>(level)) {
		deltaX = left + GetOffset(hor, level);
		direct = &Point::Right;
	}
	else {
		if (GetRandBool()) {
			deltaY = up + GetOffset(ver, level);
			direct = &Point::Down;
		}
		else {
			deltaX = left + GetOffset(hor, level);
			direct = &Point::Right;
		}
	}

	return {
		Point{ deltaX, deltaY },
		direct
	};
}
void Fleet::GetShip(const Level level) {
	auto [point, direct] = GetPointDirect(level);
	for (UINT index = 0, size = static_cast<UINT>(level);
		index < size; ++index) {
		Sea::SetCell(point, Cell::ship);
		point = (&point->*direct)();
	}
}
