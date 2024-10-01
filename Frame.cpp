
#include "Frame.h"

using namespace frame;

Frame::Frame(const WNDPROC WndProc, const HWND hWnd, const IDC IDC_FRAME) {
	static WNDCLASSEXW wcex {
		sizeof(WNDCLASSEX),					// cbSize
		0,									// style
		NULL,								// lpfnWndProc
		0,									// cbClsExtra
		0,									// cbWndExtra
		NULL,								// hInstance
		NULL,								// hIcon
		LoadCursor(nullptr, IDC_ARROW),		// hCursor
		(HBRUSH)(COLOR_WINDOW + 1),			// hbrBackground
		MAKEINTRESOURCEW(IDC_FLEETBATTLE),	// lpszMenuName
		NULL,								// lpszClassName
		NULL								// hIconSm
	};
	constexpr size_t MAX_LOADSTRING = 100;

	auto hInstance{ GetHInstance() };
	WCHAR szWindowClass[MAX_LOADSTRING];
	LoadStringW(hInstance, static_cast<UINT>(IDC_FRAME), szWindowClass, MAX_LOADSTRING);

	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.lpszClassName = szWindowClass;
	RegisterClassExW(&wcex);

	if (hWnd) {
		Frame::hWnd = CreateWindowW(szWindowClass, nullptr, WS_CHILD /* | WS_DISABLED */,
			CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWnd, nullptr, hInstance, nullptr);
	}
	else {
		WCHAR szTitle[MAX_LOADSTRING];
		LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		Frame::hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU
			| WS_MINIMIZEBOX, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
			nullptr, hInstance, nullptr);
	}
	VariantInstance(std::pair{ GetHWND(), this });
}
const Point Frame::GetPoint(const LPARAM lParam) const {
	return Point{ (static_cast<UINT>(lParam) & 0xffff) / GetScaleUINT(),
		((static_cast<UINT>(lParam) >> 16) & 0xffff) / GetScaleUINT()};
}
Frame& Frame::GetInstance(const HWND hWnd) {
	return VariantInstance(hWnd);
}
Frame& Frame::VariantInstance(
	std::variant<const HWND, std::pair<const HWND, Frame*>> variant) {
	static std::map<const HWND, Frame*> inst;

	if (variant.index()) {
		auto [hWnd, ptr]{ std::get<std::pair<const HWND, Frame*>>(variant) };
		inst.emplace(hWnd, ptr);
		return *ptr;
	}
	else {
		auto hWnd{ std::get<const HWND>(variant) };
		if (auto iter = inst.find(hWnd); iter != inst.end())
			return *iter->second;
	}
}
MainFrame::MainFrame() :
	Frame{ CallBackMain, NULL, IDC::FRAMEMAIN }
{
	RECT RWindows, RClient;
	GetWindowRect(GetHWND(), &RWindows);
	GetClientRect(GetHWND(), &RClient);

	UINT sizeFrame{ GetSizeUINT() * GetScaleUINT() };
	MoveWindow(GetHWND(), RWindows.left, RWindows.top,
		RWindows.right - RWindows.left - RClient.right + sizeFrame * 2,
		RWindows.bottom - RWindows.top - RClient.bottom + sizeFrame, false);
	ShowWindow(GetHWND(), SW_SHOW);
	UpdateWindow(GetHWND());
}
LRESULT CALLBACK MainFrame::CallBackMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BATTLE_START:
			GetInstance(hWnd).Battle();
			break;
			/*
		case ID_RANDOM:
			GetInstance(hWnd).CreateFleet();
			break;
			*/
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
PlayFrame::PlayFrame(const HWND hWnd, const IDC IDC_FRAME) :
	Frame{ CallBackPlay, hWnd, IDC_FRAME},
	hDC{ GetDC(GetHWND()) }
{
	UINT sizeFrame{ GetSizeUINT() * GetScaleUINT() };
	if (IDC::FRAMEALLIES == IDC_FRAME)
		MoveWindow(GetHWND(), 0, 0, sizeFrame, sizeFrame, false);
	else if (IDC::FRAMEENEMY == IDC_FRAME)
		MoveWindow(GetHWND(), sizeFrame, 0, sizeFrame, sizeFrame, false);
	ShowWindow(GetHWND(), SW_SHOW);
	UpdateWindow(GetHWND());

	SelectCell(Cell::sea);
}
void PlayFrame::SetCell(const Point point, const Cell cell) const {
	if (PlayFrame::cell != cell) {
		SelectCell(cell);
		PlayFrame::cell = cell;
	}
	auto scale{ GetScaleUINT() };
	Rectangle(hDC, point.x * scale, point.y * scale, (point.x + 1) * scale, (point.y + 1) * scale);
}
void PlayFrame::Fill(const Cell cell) const {
	if (PlayFrame::cell != cell) {
		SelectCell(cell);
		PlayFrame::cell = cell;
	}
	auto size{ GetSizeUINT() };
	auto scale{ GetScaleUINT() };
	for (UINT x = 0; x < size; ++x) {
		for (UINT y = 0; y < size; ++y) {
			Rectangle(hDC, x * scale, y * scale, (x + 1) * scale, (y + 1) * scale);
		}
	}
}
void PlayFrame::SelectCell(const Cell cell) const {
	struct Cell {
		HBRUSH brush;
		HPEN pen;
		Cell(const Color brush, const Color pen) :
			brush{ CreateSolidBrush(static_cast<UINT>(brush)) },
			pen{ CreatePen(PS_SOLID, 1, static_cast<UINT>(pen)) }
		{}
	};
	static const Cell sea{ Color::Blue, Color::White };
	static const Cell sky{ Color::White, Color::Blue };
	static const Cell ship{ Color::Blace, Color::Blace };

	switch (static_cast<UINT>(cell)) {
	case(static_cast<UINT>(domain::Cell::sea)):
		SelectObject(hDC, sea.brush);
		SelectObject(hDC, sea.pen);
		break;
	case(static_cast<UINT>(domain::Cell::sky)):
		SelectObject(hDC, sky.brush);
		SelectObject(hDC, sky.pen);
		break;
	default:
		SelectObject(hDC, ship.brush);
		SelectObject(hDC, ship.pen);
	}
}
LRESULT CALLBACK PlayFrame::CallBackPlay(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		GetInstance(hWnd).LButtonDown(lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}