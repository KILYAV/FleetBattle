#pragma once

#include "Random.h"
#include "Frame.h"

#include <array>

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

		void BlastCell(
			const Point point
		);
		void MissedCell(
			const Point point
		);
		void MisledCorner(
			const Point point
		);
		void MisledFace(
			const Target_t& target
		);
		bool IsTarget(
			const Target_t& target
		) const;
		bool IsNotTarget(
			const Target_t& target
		) const {
			return false == IsTarget(target);
		}

	private:
		void SetCell(
			const Point point,
			const Cell
		);
	};
}