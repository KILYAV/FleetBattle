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

		void Blast(
			const Point point
		);
		void Missle(
			const Point point
		);
		void MissleCorner(
			const Point point
		);
		void MissleFace(
			const std::tuple<Point, Point, Point, Point>
		);
	private:
		void SetCell(
			const Point point,
			const Cell
		);
	};
}