#pragma once
#include "EventDispatcher.h"

namespace Editor {

	enum WindowStyle {
		WindowStyleNormalWindow = 1,
		WindowStyleDlgWindow,
		WindowStyleContainerWindow,
		WindowStyleAuxWindow,
		WindowStyleCount
	};

	class BaseWindow : public EventDispatcher
	{
	protected:
		HDC mHDC;
		BaseWindow* mParent;
		std::unordered_set<BaseWindow*> mChildren;
		Gdiplus::Color mBKGColor;
		Gdiplus::Rect mRect, mMainRect, mMaxRect;
		char mName[64];
		char mType[64];
		bool mbDirty;
		bool mbVisiable;

	protected:
		virtual void DrawContent(Gdiplus::Graphics& painter);
		virtual void OnPaint();
		virtual void OnEndPaint();
		virtual void OnSize(WPARAM wParam, LPARAM lParam, void* reserved = nullptr);
		virtual void OnMove(WPARAM wParam, LPARAM lParam, void* reserved = nullptr);
		virtual void OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, void* reserved = nullptr);

	public:
		BaseWindow();
		~BaseWindow();
		HWND GetHwnd();
		HDC GetDC();
		virtual void PaintWindow();
		virtual void Show(bool bShow);
		virtual void OnShow(bool bShow);

	public:
		static HINSTANCE mAppInstance;
		static BaseWindow* sRootWindow;
		static Gdiplus::GdiplusStartupInput sGdiplusStartupInput;
		static ULONG_PTR sGdiplusToken;

		static void InitGlobalGUISettings(HINSTANCE instance);
		static ATOM RegisterWindowClass(UINT style, LPCTSTR pWndClassName, WNDPROC wndProc);
		static HWND CreateWindowWithStyle(WindowStyle style, int x, int y, int width, int height, LPCTSTR windowClass, HWND parent);
		static void SetRootWindow(BaseWindow*window);
	};

}
