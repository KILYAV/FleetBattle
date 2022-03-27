#pragma once
#include "framework.h"
#include "Resource.h"
// Content 
#include "CBase.h"
#include "CList.h"

class CFrame : public CList, virtual protected CBase {
public:
	enum EScale
	{
		eScale20 = 20,
		eScale40 = 40,
		eScale80 = 80
	};

	struct EWndProc
	{
		WNDPROC sMain;
		WNDPROC sEnemy;
		WNDPROC sAllies;
	};

public:
	using PHWND = HWND*;

private:
	static WNDCLASSEXW wcex;

	UINT mScale;
	UINT mSizeFrame;

	HWND aHWnd[eFrameTotal];
	HDC  aHDC[eFrameTotal - 1];

private:
	static bool TestContent(const PHWND, const HWND);

	void CreateMainFrame(const WNDPROC);
	void CreateEnemyFrame(const WNDPROC);
	void CreateAlliesFrame(const WNDPROC);

protected:
	CFrame(const HINSTANCE, const EWndProc, const PVOID);

	PHDC  const GetHDC() { return aHDC; };
	PHWND const GetHWnd() { return aHWnd; };
	UINT  const GetScale() { return mScale; };

public:
	CFrame() = delete;
};
