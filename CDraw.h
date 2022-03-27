#pragma once
#include "framework.h"
#include "Resource.h"
// Content
#include "CFrame.h"

class CDraw : public CFrame {
private:
	enum EColor
	{
		eBlace = 0x000000,
		eRed = 0x0000FF,
		eBlue = 0xFF0000,
		eWhite = 0xFFFFFF
	};
	struct SCell
	{
		const HBRUSH pBrush;
		const HPEN pPen;
	};

private:
	static const SCell aCell[eCellTotal];

private:
	template<typename T0, typename T1>
	constexpr void SELECTSCELL(T0 hDC, T1 eCell)
	{
		SelectObject(hDC, aCell[eCell].pBrush);
		SelectObject(hDC, aCell[eCell].pPen);
	}
	template<typename T0, typename T1, typename T2, typename T3, typename T4>
	constexpr void DRAWCELL(T0 aBoard, T1 hDC, T2 size, T3 scale, T4 eCell)
	{
		SELECTSCELL(hDC, eCell);
		for (UINT x = 0; x < size; x++)
			for (UINT y = 0; y < size; y++)
				if (aBoard[x][y] == eCell)
					Rectangle(hDC, x * scale, y * scale,
						(x + 1) * scale, (y + 1) * scale);
	}

protected:
	void DrawFull(const UINT);
	void DrawCell(const SPoint&, const UINT, const UINT);
	void DrawDiagonal(const SPoint&, const UINT);

protected:
	CDraw(const HINSTANCE, const EWndProc, const PVOID);

public:
	CDraw() = delete;
};
