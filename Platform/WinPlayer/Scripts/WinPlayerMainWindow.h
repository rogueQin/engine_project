#include "MainWindow.h"

class  WinPlayerMainWindow : public Editor::MainWindow
{
protected:
	virtual void OnKeyDown(WPARAM wParam, LPARAM lParam, void*reserved);

public:
	WinPlayerMainWindow();
	~WinPlayerMainWindow();

	void Init();


};

