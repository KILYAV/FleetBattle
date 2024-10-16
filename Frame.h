#pragma once
#include "Data.h"
#include "Resource.h"

#include <map>
#include <variant>

namespace frame {
	using namespace domain;

	class BaseFrame :
		virtual Data
	{
	protected:
		enum class IDC {
			FRAMEMAIN = IDS_APP_TITLE,
			FRAMEENEMY = IDC_FRAMEENEMY,
			FRAMEALLIES = IDC_FRAMEALLIES
		};
		explicit BaseFrame(
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
		static BaseFrame* VariantInstance(
			std::variant<const HWND, std::pair<const HWND, BaseFrame*>> variant
		);
	};
	template<class Type>
	Type& BaseFrame::GetInstance(const HWND hWnd) {
		return *static_cast<Type*>(VariantInstance(hWnd));
	}

	class Main :
		virtual Data,
		public BaseFrame
	{
	protected:
		explicit Main();

		virtual void Random() = 0;
		virtual void Battle() = 0;

	private:
		static LRESULT CALLBACK CallBackMain(HWND, UINT, WPARAM, LPARAM);
	};

	class Frame :
		virtual Data,
		public BaseFrame
	{
	public:
		virtual void LButtonDown(const LPARAM lParam) = 0;

	protected:
		explicit Frame(
			const HWND hWnd,
			const IDC IDC_FRAME
		);

		void SetCell(
			const Point point,
			const Cell cell
		) const;
		void Fill() const;

		virtual Cell GetCell(
			const Point point
		) const = 0;
	private:
		HDC hDC;
		mutable Cell cell = Cell::sea;

		void SelectCell(const Cell cell) const;

		static LRESULT CALLBACK CallBackDraw(HWND, UINT, WPARAM, LPARAM);
	};
}
