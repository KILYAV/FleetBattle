#pragma once
#include "Board.h"
#include "Resource.h"

#include <map>
#include <variant>

namespace frame {
	using namespace domain;

	class Frame : virtual Data {
	public:
		virtual void Battle() const = 0;
		virtual void LButtonDown(const LPARAM lParam) = 0;
	protected:
		enum class IDC {
			FRAMEMAIN = IDS_APP_TITLE,
			FRAMEENEMY = IDC_FRAMEENEMY,
			FRAMEALLIES = IDC_FRAMEALLIES
		};

		explicit Frame(const WNDPROC WndProc, const HWND hWnd, const IDC IDC_FRAME);

		const HWND GetHWND() const { return hWnd; };
		const Point GetPoint(const LPARAM lParam) const;
		static Frame& GetInstance(const HWND hWnd);
	private:
		HWND hWnd;
		static Frame& VariantInstance(
			std::variant<const HWND, std::pair<const HWND, Frame*>> variant);
	};

	class MainFrame : virtual Data, protected Frame {
	protected:
		explicit MainFrame();
	private:
		void LButtonDown(const LPARAM lParam) override {};
		static LRESULT CALLBACK CallBackMain(HWND, UINT, WPARAM, LPARAM);
	};

	class PlayFrame : virtual Data, protected Frame {
	protected:
		explicit PlayFrame(const HWND hWnd, const IDC IDC_FRAME);

		HDC GetHDC() const { return hDC; };
		void SetCell(const Point point, const Cell cell) const;
		void Fill(const Cell cell) const;
	private:
		HDC hDC;
		mutable Cell cell = Cell::sea;

		void SelectCell(const Cell cell) const;

		static LRESULT CALLBACK CallBackPlay(HWND, UINT, WPARAM, LPARAM);
	};
}
