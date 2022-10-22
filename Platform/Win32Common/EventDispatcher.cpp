#include "EventDispatcher.h"
namespace Editor {
	EventDispatcher::EventDispatcher() 
	{
	}

	EventDispatcher::~EventDispatcher() 
	{
	}

	void EventDispatcher::OnMouseMove(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnMouseWheel(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnLeftButtonDown(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnLeftButtonUp(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnLeftButtonDoubleClick(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnRightButtonDown(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnRightButtonUp(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnRightButtonDoubleClick(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnKeyDown(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnKeyUp(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnSize(WPARAM wParam, LPARAM lParam, void*reserved) {}
	void EventDispatcher::OnMove(WPARAM wParam, LPARAM lParam, void* reserved) {}
	void EventDispatcher::OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, void* reserved) {}

	LRESULT EventDispatcher::WindowEventProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		EventDispatcher* self = (EventDispatcher*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (nullptr == self)
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		switch (msg)
		{
		case WM_MOUSEMOVE:
		{
			POINT pos;
			GetCursorPos(&pos);
			RECT rect;
			GetWindowRect(hWnd, &rect);
			self->OnMouseMove(wParam, MAKELPARAM(pos.x - rect.left, pos.y - rect.bottom));
			return 0;
		}
		case WM_LBUTTONDOWN: 
		{
			POINT pos;
			GetCursorPos(&pos);
			RECT rect;
			GetWindowRect(hWnd, &rect);
			self->OnLeftButtonDown(wParam, MAKELPARAM(pos.x - rect.left, pos.y - rect.bottom));
			return 0;
		}
		case WM_LBUTTONUP:
		{
			POINT pos;
			GetCursorPos(&pos);
			RECT rect;
			GetWindowRect(hWnd, &rect);
			self->OnLeftButtonUp(wParam, MAKELPARAM(pos.x - rect.left, pos.y - rect.bottom));
			return 0;
		}
		case WM_LBUTTONDBLCLK:
		{
			self->OnLeftButtonUp(wParam, lParam);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			self->OnRightButtonDown(wParam, lParam);
			return 0;
		}
		case WM_RBUTTONUP:
		{
			self->OnRightButtonUp(wParam, lParam);
			return 0;
		}
		case WM_RBUTTONDBLCLK:
		{
			self->OnRightButtonDoubleClick(wParam, lParam);
			return 0;
		}
		case WM_KEYDOWN:
		{
			self->OnKeyDown(wParam, lParam);
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE:
		{
			self->OnSize(wParam, lParam);
			return 0;
		}
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
}
