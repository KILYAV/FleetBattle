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
void Shot::BlastCell(
	const Point point
) {
	SetCell(point, Cell::blast);
}
void Shot::MissedCell(
	const Point point
) {
	SetCell(point, Cell::missle);
}
void Shot::MisledCorner(
	const Point point
) {
	UINT max = GetMaxUINT();
	if (Point next{ point.North().West() }; next.IsNotNan(max))
		MissedCell(next);
	if (Point next{ point.North().East() }; next.IsNotNan(max))
		MissedCell(next);
	if (Point next{ point.South().West() }; next.IsNotNan(max))
		MissedCell(next);
	if (Point next{ point.South().East() }; next.IsNotNan(max))
		MissedCell(next);
}
void Shot::MisledFace(
	const Target_t& target
) {
	for (UINT index = 0, size = target.count; index < size; ++index) {
		MissedCell(target.points[index]);
	}
}
bool Shot::IsTarget(
	const Target_t& target
) const {
	bool result = Cell::ship == Sea::GetCell(target.points[0]);
	for (UINT index = 1, size = target.count; index < size; ++index) {
		result = result || Cell::ship == Sea::GetCell(target.points[index]);
	}
	return result;
}