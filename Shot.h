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
		void Missed(
			const Point point
		);
		void MisledCorner(
			const Point point
		);
		void MisledFace(
			const std::tuple<Point, Point, Point, Point>
		);
	private:
		void SetCell(
			const Point point,
			const Cell
		);
	};
}