#include "WinPlayerMainWindow.h"
#include "../Configs/Config.h"

WinPlayerMainWindow::WinPlayerMainWindow() 
{
}

WinPlayerMainWindow::~WinPlayerMainWindow() 
{
}

void WinPlayerMainWindow::Init() 
{
	SetRootWindow(this);
	UINT style = CS_VREDRAW | CS_HREDRAW | CS_DROPSHADOW | CS_DBLCLKS;
	LPCTSTR pWndClassName = L"WinPlayerMainWindow";
	RegisterWindowClass(style, pWndClassName, WindowEventProc);

	DWORD windowStyle = WS_OVERLAPPED | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	mhWnd = CreateWindowWithStyle(Editor::WindowStyleNormalWindow, CW_USEDEFAULT, CW_USEDEFAULT, Config::Screen_width, Config::Screen_height, pWndClassName, NULL);

	mHDC = GetWindowDC(mhWnd);
	mBKGColor = Gdiplus::Color(0, 150, 200);
}

