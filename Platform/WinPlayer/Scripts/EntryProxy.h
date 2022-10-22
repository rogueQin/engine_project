#include "RuntimePrefix.h"
#include "WinPlayerMainWindow.h"


class  EntryProxy
{
public:
	EntryProxy();
	~EntryProxy();

	void ProcessMessage(MSG& msg);
	
	void MessageLoop();
	
	void StartEngine(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);
	
private:
	//Editor::BaseWindow* gMainWindow;
	WinPlayerMainWindow* gMainWindow;


};

