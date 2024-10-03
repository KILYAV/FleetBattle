#pragma once
#include "Data.h"
#include "Resource.h"

#include <map>
#include <variant>

namespace frame {
	using namespace domain;

	class Frame : virtual Data {
	protected:
		enum class IDC {
			FRAMEMAIN = IDS_APP_TITLE,
			FRAMEENEMY = IDC_FRAMEENEMY,
			FRAMEALLIES = IDC_FRAMEALLIES
		};
		explicit Frame(
			const WNDPROC WndProc,
			const HWND hWnd,
			const IDC IDC_FRAME
		);
		const HWND GetHWND() const { return hWnd; };
		const Point GetPoint(const LPARAM lParam) const;
		template<class Type>
		static Type& GetInstance(const HWND hWnd);
	private:
		HWND hWnd;
		static Frame& VariantInstance(
			std::variant<const HWND, std::pair<const HWND, Frame*>> variant);
	};
	template<class Type>
	Type& Frame::GetInstance(const HWND hWnd) {
		return *static_cast<Type*>(VariantInstance(hWnd));
	}

	class Main : virtual Data, protected Frame {
	protected:
		explicit Main();

		virtual void Start() = 0;
		virtual void Battle() = 0;

	private:
		static LRESULT CALLBACK CallBackMain(HWND, UINT, WPARAM, LPARAM);
	};
	class Draw : virtual Data, protected Frame {
	public:
		virtual void LButtonDown(const LPARAM lParam) = 0;

	protected:
		explicit Draw(const HWND hWnd, const IDC IDC_FRAME);

		//HDC GetHDC() const { return hDC; };
		void SetCell(const Point point, const Cell cell) const;
		void Fill(const Cell cell) const;
	private:
		HDC hDC;
		mutable Cell cell = Cell::sea;

		void SelectCell(const Cell cell) const;

		static LRESULT CALLBACK CallBackDraw(HWND, UINT, WPARAM, LPARAM);
	};
}
