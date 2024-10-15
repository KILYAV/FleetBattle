#include "Shot.h"

using namespace shot;

enum Direct {
	up,
	down,
	left,
	right
};

Shot::Shot(
	const HWND hWnd,
	const IDC IDC_FRAME
) :
	Frame{ hWnd, IDC_FRAME }
{};
void Shot::HitCell(
	const Point point,
	const Cell cell
) {
	Sky::SetCell(point, cell);
	Sea::SetCell(point, cell);
	Frame::SetCell(point, cell);
}
void Shot::HitCorner(
	const Point point
) {
	UINT max = GetMaxUINT();
	if (false == point.Up().Left().IsNan(max)) {
		HitCell(point.Up().Left(), Cell::missle);
	}
	if (false == point.Up().Right().IsNan(max)) {
		HitCell(point.Up().Right(), Cell::missle);
	}
	if (false == point.Down().Left().IsNan(max)) {
		HitCell(point.Down().Left(), Cell::missle);
	}
	if (false == point.Down().Right().IsNan(max)) {
		HitCell(point.Down().Right(), Cell::missle);
	}
	Frame::SetCell(point, Cell::blast);
}
void Shot::HitFace(
	const std::tuple<Point, Point, Point, Point> points
) {
	UINT max = GetMaxUINT();
	if (false == std::get<up>(points).IsNan(max)) {
		HitCell(std::get<up>(points), Cell::missle);
	}
	if (false == std::get<down>(points).IsNan(max)) {
		HitCell(std::get<down>(points), Cell::missle);
	}
	if (false == std::get<left>(points).IsNan(max)) {
		HitCell(std::get<left>(points), Cell::missle);
	}
	if (false == std::get<right>(points).IsNan(max)) {
		HitCell(std::get<right>(points), Cell::missle);
	}
}