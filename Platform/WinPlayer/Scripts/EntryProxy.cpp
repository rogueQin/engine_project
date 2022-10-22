#include "EntryProxy.h"


EntryProxy::EntryProxy() {}
EntryProxy::~EntryProxy() {}

void EntryProxy::ProcessMessage(MSG& msg)
{
	//if (!TranslateAccelerator(msg.hwnd, gMainWindow.mAccel, &msg)){}

	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

void EntryProxy::MessageLoop()
{
	MSG msg = { 0 };
	std::vector<MSG> msg_seq;
	bool isQuit = false;


	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
		{
			ProcessMessage(msg);
		}
		else
		{
			msg_seq.push_back(msg);
		}

		if (msg_seq.size() >= 100)
		{
			for (int i = 0; i < msg_seq.size(); i++)
			{
				ProcessMessage(msg_seq[i]);
			}
			msg_seq.clear();
		}

		if (msg.message == WM_QUIT)
		{
			msg_seq.clear();
			break;
		}
	}
}

void EntryProxy::StartEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WinPlayerMainWindow::InitGlobalGUISettings(hInstance);
	gMainWindow = new WinPlayerMainWindow();
	gMainWindow->Init();
	gMainWindow->Show(true);
	//gMainWindow->SetWindowSize();
}

