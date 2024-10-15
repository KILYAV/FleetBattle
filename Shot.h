#pragma once

#include "Random.h"
#include "Frame.h"

namespace shot {
	using namespace domain;
	class Shot :
		virtual Data,
		protected frame::Frame,
		protected random::Random
	{
	protected:
		Shot(
			const HWND hWnd,
			const IDC IDC_FRAME
		);

		void HitCell(
			const Point point,
			const Cell cell
		);
		void HitCorner(
			const Point point
		);
		void HitFace(
			const std::tuple<Point, Point, Point, Point>
		);
	private:

	};
}