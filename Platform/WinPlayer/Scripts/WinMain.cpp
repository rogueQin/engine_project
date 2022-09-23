
#include <windows.h>
#include <gl/GL.h>
#include "Config.h"

extern "C" void StartEngine(HINSTANCE, HINSTANCE, LPSTR, int);
typedef struct
{
	int mLeft;
	int mBotoom;
	int mWidth;
	int mHeight;
}Rect;


HWND ghMainWnd = 0;
HDC hdc = 0;
Rect mRect;


bool InitWindowsApp(HINSTANCE instanceHandle, int show);
int Run();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OnSize(WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	if (!InitWindowsApp(hInstance, nCmdShow))
		return 0;

	return Run();

	//StartEngine(hInstance, hPrevInstance, pCmdLine, nCmdShow);
	//return 0;
}

bool InitWindowsApp(HINSTANCE instanceHandle, int show)
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instanceHandle;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"ApplicationMain";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, L"RegisterClass Failed", 0, 0);
		return false;
	}

	ghMainWnd = CreateWindow(
		L"ApplicationMain",
		L"Win32Basic",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		Config::Screen_width,
		Config::Screen_height,
		0,
		0,
		instanceHandle,
		0);

	if (ghMainWnd == 0)
	{
		MessageBox(0, L"CreateWindow Failed", 0, 0);
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.cColorBits = 32;
	pfd.cDepthBits = 8;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;

	hdc = GetDC(ghMainWnd);

	int format = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, format, &pfd);

	HGLRC hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	ShowWindow(ghMainWnd, show);
	UpdateWindow(ghMainWnd);

	return true;
}

int Run()
{
	MSG msg = { 0 };
	
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			if (mRect.mWidth > mRect.mHeight)
			{
				int dis = mRect.mWidth - mRect.mHeight;
				glViewport(0, -dis / 2, mRect.mWidth, mRect.mWidth);
			}
			else 
			{
				int dis = mRect.mHeight - mRect.mWidth;
				glViewport(-dis / 2, 0, mRect.mHeight, mRect.mHeight);
			}

			glClear(GL_COLOR_BUFFER_BIT);

			glBegin(GL_TRIANGLES);

			glColor4f(1,0,0,1);
			glVertex2f(0, 0);
			glVertex2f(-0.5, -0.5);
			glVertex2f(0, 0.5);

			glColor4f(0, 1, 0, 1);
			glVertex2f(0, 0);
			glVertex2f(0.5, -0.5);
			glVertex2f(0, 0.5);

			glColor4f(0, 0, 1, 1);
			glVertex2f(0, 0);
			glVertex2f(-0.5, -0.5);
			glVertex2f(0.5, -0.5);

			glEnd();

			SwapBuffers(hdc);
		}
	}
	
	return (int)msg.wParam;
}

void OnSize(WPARAM wParam, LPARAM lParam) 
{
	mRect.mWidth = LOWORD(lParam);
	mRect.mHeight = HIWORD(lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		//MessageBox(0, L"Hello Applicaiton Main!", L"Hello", MB_OK);7
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(ghMainWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		OnSize(wParam, lParam);
		return 0;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
