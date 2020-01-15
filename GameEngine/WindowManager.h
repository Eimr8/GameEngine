#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#define NOMINMAX //Don't define minmax so it doesn't break std::min
#include <Windows.h>
#include <string>

typedef struct{
	int wWidth;
	int wHeight;
	DWORD wStyle;
	DWORD wExStyle;
} WNDVAR;

class WindowManager{

public:
	WindowManager(HINSTANCE);
	~WindowManager();

	bool CreateWnd(std::string, WNDVAR);

	//void setGfx(Graphics*);
	//void setInputMng(InputManager*);
	WNDVAR getWNDVAR();
	HWND getWHandler();
	HINSTANCE getHInstance();

private:
	static LRESULT CALLBACK WindowProcSetup(HWND, UINT, WPARAM, LPARAM);
	virtual LRESULT WindowProc(UINT, WPARAM, LPARAM);

private:
	HINSTANCE hInst;
	HWND wHandler;

	WNDVAR wndVar;
	std::string wName;
	std::string wClassName;

	//Graphics* gfx;
	//InputManager* inputMng;
};

#endif