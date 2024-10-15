#include "Shot.h"

using namespace shot;

Shot::Shot(
	const HWND hWnd,
	const IDC IDC_FRAME
) :
	Frame{ hWnd, IDC_FRAME }
{};
void Shot::SetCell(
	const Point point,
	const Cell cell
) {
	Sky::SetCell(point, cell);
	Sea::SetCell(point, cell);
	Frame::SetCell(point, cell);
}
void Shot::Blast(
	const Point point
) {
	SetCell(point, Cell::blast);
}
void Shot::Missle(
	const Point point
) {
	SetCell(point, Cell::missle);
}
void Shot::MissleCorner(
	const Point point
) {
	UINT max = GetMaxUINT();
	if (Point next{ point.Up().Left() }; next.IsNotNan(max))
		Missle(next);
	if (Point next{ point.Up().Right() }; next.IsNotNan(max))
		Missle(next);
	if (Point next{ point.Down().Left() }; next.IsNotNan(max))
		Missle(next);
	if (Point next{ point.Down().Right() }; next.IsNotNan(max))
		Missle(next);
}
void Shot::MissleFace(
	const std::tuple<Point, Point, Point, Point> points
) {
	UINT max = GetMaxUINT();
	if (std::get<up>(points).IsNotNan(max)) {
		Missle(std::get<up>(points));
	}
	if (std::get<down>(points).IsNotNan(max)) {
		Missle(std::get<down>(points));
	}
	if (std::get<left>(points).IsNotNan(max)) {
		Missle(std::get<left>(points));
	}
	if (std::get<right>(points).IsNotNan(max)) {
		Missle(std::get<right>(points));
	}
}