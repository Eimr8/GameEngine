#include "WindowManager.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	WNDVAR wndvar = { 1024, 576, WS_OVERLAPPEDWINDOW, NULL };
	WindowManager* wndMng = new WindowManager(hInstance);
	wndMng->CreateWnd("Window", wndvar);

	//App loop
	MSG msg;
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;

	//return 0;
}
