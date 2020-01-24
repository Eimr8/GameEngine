#include "WindowManager.h"
#include "resource.h"
#include <sstream>

WindowManager::WindowManager(HINSTANCE hInstance)
{
	hInst = hInstance;
	wHandler = nullptr;
	wndVar = { 0 };
	//inputMng = NULL;
}

WindowManager::~WindowManager()
{
	LPCSTR wclassname = (LPCSTR)wClassName.c_str();
	UnregisterClass(wClassName.c_str(), hInst);
}

bool WindowManager::CreateWnd(std::string wname, WNDVAR wndVar) 
{
	//Define and register window class
	LPCSTR wClassName = (LPCSTR)"WindowClass";
	LPCSTR wName = (LPCSTR)wname.c_str();

	WNDCLASSEX wClass = { 0 };
	wClass.cbSize = sizeof(wClass);
	wClass.style = CS_OWNDC;
	wClass.lpfnWndProc = &WindowProcSetup;
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	wClass.hInstance = hInst;
	wClass.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
	wClass.hCursor = NULL;
	wClass.hbrBackground = NULL;
	wClass.lpszMenuName = NULL;
	wClass.lpszClassName = wClassName;
	wClass.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);

	if (!RegisterClassEx(&wClass))
	{
		throw LAST_EXCEPT();
		return false;
	}

	//Create Window
	RECT rect = { 0, 0, wndVar.wWidth, wndVar.wHeight };
	AdjustWindowRectEx(&rect, wndVar.wStyle, false, wndVar.wExStyle);

	wHandler = CreateWindowEx(
		wndVar.wExStyle,
		wClassName,
		wName,
		wndVar.wStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right,
		rect.bottom,
		NULL,
		NULL,
		hInst,
		this
	);

	if (wHandler == NULL) 
	{
		throw LAST_EXCEPT();
		return false;
	}

	this->wndVar = wndVar;
	this->wName = wname;
	this->wClassName = wClassName;

	//Show WindowManager
	ShowWindow(wHandler, SW_SHOW);

	return true;
}

LRESULT CALLBACK WindowManager::WindowProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	WindowManager* windowManager = NULL;

	if(msg == WM_NCCREATE)
	{
		CREATESTRUCT* cS = (CREATESTRUCT*)lParam;
		windowManager = (WindowManager*)cS->lpCreateParams;
		windowManager->wHandler = hWnd;

		SetLastError(1);
		if (SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)windowManager))
		{
			if(GetLastError() != 1) return FALSE;
		}
	}
	else
	{
		windowManager = (WindowManager*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	if(windowManager)
	{
		return windowManager->WindowProc(msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WindowManager::WindowProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg)
	{
	case WM_CLOSE:
		DestroyWindow(wHandler);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_ACTIVATE:
		return 0;

	case WM_EXITSIZEMOVE:
		/*RECT clientRect;
		GetClientRect(wHandler, &clientRect);
		gfx->d3dParameters.BackBufferWidth = clientRect.right;
		gfx->d3dParameters.BackBufferHeight = clientRect.bottom;

		HRESULT tmp;
		if (gfx->d3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			gfx->onLostDevice();
			if (FAILED((tmp = gfx->d3dDevice->Reset(&gfx->d3dParameters))))
				DXTRACE_ERR("Graphic device reset failed\n", tmp);
			gfx->onResetDevice();
		}*/
		return 0;

	case WM_KILLFOCUS:
		//Reset key states in case of losing focus
		//If not done may miss keyup messages and cause unexpected behavior
		//inputMng->clearKeyStates();
		//break;

		// ***************** Keyboard Messages **********************
	case WM_KEYDOWN:
		//SYSKEYDOWN needs to be handled to track some keys like ALT (VK_MENU)
	case WM_SYSKEYDOWN:
		/*if (!(lParam & 0x40000000) || inputMng->autorepeat()) {
			inputMng->onKeyDown((unsigned char)wParam);
		}
		break;*/

	case WM_KEYUP:
	case WM_SYSKEYUP:
		//inputMng->onKeyUp((unsigned char)wParam);
		break;

	case WM_CHAR:
		/*inputMng->onChar((char)wParam);
		break;*/
		// **********************************************************

		// ***************** Mouse Messages *************************

	case WM_MOUSEMOVE:
		/*const POINTS pt = MAKEPOINTS(lParam);

		//In client region, log move and log enter + capture mouse
		if (pt.x >= 0 && pt.x < wndVar.wWidth && pt.y >= 0 && pt.y < wndVar.wHeight) {
			inputMng->onMouseMove(pt.x, pt.y);
			if (!inputMng->isInWindowManager()) {
				SetCapture(wHandler);
				inputMng->onMouseEnter();
			}
		}
		//Not in client, log move and maintain capture if button down
		else {
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				inputMng->onMouseMove(pt.x, pt.y);
			}
			//Button up, release capture and log event for leaving
			else {
				ReleaseCapture();
				inputMng->onMouseLeave();
			}
		}
		break;*/

	case WM_LBUTTONDOWN:
	{
		/*const POINTS pt = MAKEPOINTS(lParam);
		inputMng->onLeftPressed(pt.x, pt.y);
		break;*/
	}

	case WM_LBUTTONUP:
	{
		/*const POINTS pt = MAKEPOINTS(lParam);
		inputMng->onLeftReleased(pt.x, pt.y);
		// release mouse if outside of WindowManager
		if (pt.x < 0 || pt.x >= wndVar.wWidth || pt.y < 0 || pt.y >= wndVar.wHeight) {
			ReleaseCapture();
			inputMng->onMouseLeave();
		}
		break;*/
	}

	case WM_RBUTTONDOWN:
	{
		/*const POINTS pt = MAKEPOINTS(lParam);
		inputMng->onRightPressed(pt.x, pt.y);
		break;*/
	}

	case WM_RBUTTONUP:
	{
		/*const POINTS pt = MAKEPOINTS(lParam);
		inputMng->onRightReleased(pt.x, pt.y);
		// release mouse if outside of WindowManager
		if (pt.x < 0 || pt.x >= wndVar.wWidth || pt.y < 0 || pt.y >= wndVar.wHeight) {
			ReleaseCapture();
			inputMng->onMouseLeave();
		}
		break;*/
	}

	case WM_MOUSEWHEEL:
	{
		/*const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		inputMng->onWheelDelta(pt.x, pt.y, delta);
		break;*/
	}

	// **********************************************************
	}

	return DefWindowProc(wHandler, msg, wParam, lParam);
}

WNDVAR WindowManager::getWNDVAR() const noexcept
{
	return wndVar;
}

HWND WindowManager::getWHandler() const noexcept
{
	return wHandler;
}

HINSTANCE WindowManager::getHInstance() const noexcept
{
	return hInst;
}


/* Exception Class */

WindowManager::Exception::Exception(const char* file, int line, HRESULT hr) noexcept
	:
	BaseException(file, line),
	hr(hr)
{

}

const char* WindowManager::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << "\n"
		<< "Description: " << getErrorString()
		<< "Error code: " << getErrorCode() << "\n"
		<< getFormattedString();

	buffer = oss.str();
	return buffer.c_str();
}

const char* WindowManager::Exception::getType() const noexcept
{
	return "WindowManager Exception";
}

std::string WindowManager::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* buffer = nullptr;
	DWORD msgLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&buffer,
		0,
		nullptr
	);

	if (msgLength == 0)
	{
		return "Unidentified error code";
	}

	std::string errString = buffer;
	LocalFree(buffer);
	return errString;
}

HRESULT WindowManager::Exception::getErrorCode() const noexcept
{
	return hr;
}

std::string WindowManager::Exception::getErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
