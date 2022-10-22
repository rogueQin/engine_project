#pragma once
#include "RuntimePrefix.h"
#include "Utils/LinkedList.h"

namespace Editor {
	class EventDispatcher : public Engine::LinkedList
	{
	public:
		EventDispatcher();
		~EventDispatcher();
	protected:
		HWND mhWnd;

	protected:
		virtual void OnMouseMove(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnMouseWheel(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnLeftButtonDown(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnLeftButtonUp(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnLeftButtonDoubleClick(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnRightButtonDown(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnRightButtonUp(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnRightButtonDoubleClick(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnKeyDown(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnKeyUp(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);

		virtual void OnSize(WPARAM wParam, LPARAM lParam, void*reserved = nullptr);
		virtual void OnMove(WPARAM wParam, LPARAM lParam, void* reserved = nullptr);
		virtual void OnGetMinMaxInfo(WPARAM wParam, LPARAM lParam, void* reserved = nullptr);

	public:
		static LRESULT CALLBACK WindowEventProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}


