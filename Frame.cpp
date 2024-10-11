#include "Frame.h"

using namespace frame;

Frame::Frame(
	const WNDPROC WndProc,
	const HWND hWnd,
	const IDC IDC_FRAME
) {
	static WNDCLASSEXW wcex{
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
	VariantInstance(std::pair{ GetHWND(), this});
}
Frame* Frame::VariantInstance(
	std::variant<const HWND,
	std::pair<const HWND, Frame*>> variant
) {
	static std::map<const HWND, Frame*> inst;

	if (variant.index()) {
		auto [hWnd, ptr] { std::get<std::pair<const HWND, Frame*>>(variant) };
		inst.emplace(hWnd, ptr);
		return ptr;
	}
	else {
		auto hWnd{ std::get<const HWND>(variant) };
		if (auto iter = inst.find(hWnd); iter != inst.end())
			return iter->second;
	}
}
const Point Frame::GetPoint(
	const LPARAM lParam
) const {
	return Point{ (static_cast<UINT>(lParam) & 0xffff) / GetScaleUINT(),
		((static_cast<UINT>(lParam) >> 16) & 0xffff) / GetScaleUINT() };
}
Main::Main() :
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
LRESULT CALLBACK Main::CallBackMain(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BATTLE_BATTLE:
			GetInstance<Main>(hWnd).Battle();
			break;
		case ID_RANDOM_RANDOM:
			GetInstance<Main>(hWnd).Random();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		};
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
Draw::Draw(
	const HWND hWnd,
	const IDC IDC_FRAME
) :
	Frame{ CallBackDraw, hWnd, IDC_FRAME},
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
void Draw::SetCell(
	const Point point, const Cell cell) const {
	if (Draw::type != cell) {
		SelectCell(cell);
		Draw::type = cell;
	}
	auto scale{ GetScaleUINT() };
	Rectangle(
		hDC,
		point.X() * scale,
		point.Y() * scale,
		(point.X() + 1) * scale,
		(point.Y() + 1) * scale
	);
}
void Draw::Fill(const Cell cell) const {
	if (Draw::type != cell) {
		SelectCell(cell);
		Draw::type = cell;
	}
	auto size{ GetSizeUINT() };
	auto scale{ GetScaleUINT() };
	for (UINT x = 0; x < size; ++x) {
		for (UINT y = 0; y < size; ++y) {
			Rectangle(
				hDC,
				x * scale,
				y * scale,
				(x + 1) * scale,
				(y + 1) * scale
			);
		}
	}
}
void Draw::SelectCell(const Cell cell) const {
	enum class Color {
		Blace = 0x000000,
		Red   = 0x0000FF,
		Blue  = 0xFF0000,
		White = 0xFFFFFF
	};
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
LRESULT CALLBACK Draw::CallBackDraw(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		GetInstance<Draw>(hWnd).LButtonDown(lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}