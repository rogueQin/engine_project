#include "BaseWindow.h"


namespace Editor {
	HINSTANCE BaseWindow::mAppInstance = nullptr;
	BaseWindow* BaseWindow::sRootWindow = nullptr;
	Gdiplus::GdiplusStartupInput BaseWindow::sGdiplusStartupInput = NULL;
	ULONG_PTR BaseWindow::sGdiplusToken = NULL;

	BaseWindow::BaseWindow() : mbVisiable(false)
	{
	}

	BaseWindow::~BaseWindow() 
	{
	}

	HWND BaseWindow::GetHwnd()
	{
		return mhWnd;
	}

	HDC BaseWindow::GetDC() 
	{
		return mHDC;
	}

	void BaseWindow::PaintWindow() 
	{
		if (mbDirty) {
			OnPaint();
			mbDirty = false;
		}
		if (mNext != nullptr) {
			Next<BaseWindow>()->PaintWindow();
		}
	}

	void BaseWindow::Show(bool bShow) 
	{
		mbVisiable = bShow;
		ShowWindow(mhWnd, mbVisiable ? SW_SHOW : SW_HIDE);
		UpdateWindow(mhWnd);
		OnShow(mbVisiable);
	}

	void BaseWindow::OnShow(bool bShow)
	{
	}

	void BaseWindow::DrawContent(Gdiplus::Graphics& painter) 
	{
	}

	void BaseWindow::OnPaint() 
	{
		Gdiplus::Graphics painter(mHDC);
		painter.Clear(mBKGColor);
		DrawContent(painter);
		OnEndPaint();
	}

	void BaseWindow::OnEndPaint() 
	{
	}

	void BaseWindow::OnSize(WPARAM wParam, LPARAM lParam, void* reserved) 
	{
	}

	void BaseWindow::OnMove(WPARAM wParam, LPARAM lParam, void* reserved) 
	{
	}

	void BaseWindow::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, void* reserved) 
	{
	}

	void BaseWindow::InitGlobalGUISettings(HINSTANCE instance)
	{
		mAppInstance = instance;
		Gdiplus::GdiplusStartup(&sGdiplusToken, &sGdiplusStartupInput, NULL);
		CoInitialize(NULL);
	}

	ATOM BaseWindow::RegisterWindowClass(UINT style, LPCTSTR pWndClassName, WNDPROC wndProc)
	{
		WNDCLASSEXW wcex;
		memset(&wcex, 0, sizeof(wcex));
		wcex.cbSize = sizeof(wcex);
		wcex.style = style;
		wcex.lpfnWndProc = wndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = mAppInstance;
		wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
		wcex.hIconSm = NULL;
		wcex.hCursor = LoadCursor(0, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wcex.lpszMenuName = 0;
		wcex.lpszClassName = pWndClassName;
		ATOM atom = RegisterClassExW(&wcex);
		if (!atom)
		{
			return 0;
		}
		return atom;
	}

	HWND BaseWindow::CreateWindowWithStyle(WindowStyle style, int x, int y, int width, int height, LPCTSTR windowClass, HWND parent)
	{
		DWORD windowStyle = WS_OVERLAPPED;
		DWORD windowExStyle = WS_OVERLAPPED;
		switch (style)
		{
		case WindowStyleNormalWindow:
			windowExStyle = windowExStyle | WS_OVERLAPPED;
			windowStyle = windowStyle | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
			break;
		case WindowStyleDlgWindow:
			windowExStyle = windowExStyle | WS_EX_TOPMOST;
			windowStyle = windowStyle | WS_POPUP | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
			break;
		case WindowStyleContainerWindow:
			windowExStyle = windowExStyle | WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE | WS_EX_TOPMOST;
			windowStyle = windowStyle | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_THICKFRAME;
			break;
		case WindowStyleAuxWindow:
			windowExStyle = windowExStyle | WS_EX_TOOLWINDOW;
			windowStyle = windowStyle | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
			break;
		}
		
		HWND mhWnd = CreateWindowEx(
			windowExStyle,
			windowClass,
			L"Window",
			windowStyle,
			x,
			y,
			width,
			height,
			parent,
			0,
			mAppInstance,
			0);

		return mhWnd;
	}

	void BaseWindow::SetRootWindow(BaseWindow*window)
	{
		sRootWindow = window;
	}
}

