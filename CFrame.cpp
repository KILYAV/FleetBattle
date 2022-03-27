#include "CFrame.h"
#define MAX_LOADSTRING 0x100 - 1

WNDCLASSEXW CFrame::wcex = { sizeof(WNDCLASSEX), 0, nullptr, 0, 0 };

CFrame::CFrame(HINSTANCE hInstance, EWndProc pWndProc, PVOID pcGame) :
    CList(TestContent, aHWnd, pcGame), CBase(),
    mSizeFrame(GetSizeBoard()* eScale20), mScale(eScale20)
{
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FLEETBATTLE));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FLEETBATTLE);
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

    CreateMainFrame(pWndProc.sMain);
    CreateEnemyFrame(pWndProc.sEnemy);
    CreateAlliesFrame(pWndProc.sAllies);
};

void CFrame::CreateMainFrame(const WNDPROC pWndProc)
{
    WCHAR szTitle[MAX_LOADSTRING];
    LoadStringW(wcex.hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    WCHAR szWindowClass[MAX_LOADSTRING];
    LoadStringW(wcex.hInstance, IDS_MAINFRAME, szWindowClass, MAX_LOADSTRING);
    wcex.lpfnWndProc = pWndProc;
    wcex.lpszClassName = szWindowClass;

    RegisterClassExW(&wcex);
    aHWnd[eMain] = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, wcex.hInstance, nullptr);

    RECT RWindows, RClient;
    GetWindowRect(aHWnd[eMain], &RWindows);
    GetClientRect(aHWnd[eMain], &RClient);

    MoveWindow(aHWnd[eMain], RWindows.left, RWindows.top,
        RWindows.right - RWindows.left - RClient.right + mSizeFrame * 2,
        RWindows.bottom - RWindows.top - RClient.bottom + mSizeFrame, false);
    ShowWindow(aHWnd[eMain], SW_SHOW);
    UpdateWindow(aHWnd[eMain]);
};
void CFrame::CreateEnemyFrame(const WNDPROC pWndProc)
{
    WCHAR szWindowClass[MAX_LOADSTRING];
    LoadStringW(wcex.hInstance, IDS_ENEMYFRAME, szWindowClass, MAX_LOADSTRING);
    wcex.lpszClassName = szWindowClass;
    wcex.lpfnWndProc = pWndProc;
    RegisterClassExW(&wcex);

    aHWnd[eEnemy] = CreateWindowW(szWindowClass, nullptr, WS_CHILD | WS_DISABLED,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, aHWnd[eMain], nullptr, wcex.hInstance, nullptr);

    MoveWindow(aHWnd[eEnemy], mSizeFrame, 0, mSizeFrame, mSizeFrame, false);
    ShowWindow(aHWnd[eEnemy], SW_SHOW);
    UpdateWindow(aHWnd[eEnemy]);

    aHDC[eEnemy] = GetDC(aHWnd[eEnemy]);
};
void CFrame::CreateAlliesFrame(const WNDPROC pWndProc)
{
    WCHAR szWindowClass[MAX_LOADSTRING];
    LoadStringW(wcex.hInstance, IDS_ALLIESFRAME, szWindowClass, MAX_LOADSTRING);
    wcex.lpszClassName = szWindowClass;
    wcex.lpfnWndProc = pWndProc;
    RegisterClassExW(&wcex);

    aHWnd[eAllies] = CreateWindowW(szWindowClass, nullptr, WS_CHILD,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, aHWnd[eMain], nullptr, wcex.hInstance, nullptr);

    MoveWindow(aHWnd[eAllies], 0, 0, mSizeFrame, mSizeFrame, false);
    ShowWindow(aHWnd[eAllies], SW_SHOW);
    UpdateWindow(aHWnd[eAllies]);

    aHDC[eAllies] = GetDC(aHWnd[eAllies]);
};

bool CFrame::TestContent(const PHWND aHWnd, const HWND hWnd)
{
    return (aHWnd[eMain] == hWnd ||
        aHWnd[eEnemy] == hWnd ||
        aHWnd[eAllies] == hWnd);
};
