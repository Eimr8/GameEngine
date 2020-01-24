#ifndef _WINDOWMANAGER_H_
#define _WINDOWMANAGER_H_

#define NOMINMAX //Don't define minmax so it doesn't break std::min

//Helper macros
#define EXCEPT(hr) WindowManager::Exception(__FILE__, __LINE__, hr)
#define LAST_EXCEPT() WindowManager::Exception(__FILE__, __LINE__, GetLastError())

#include "BaseException.h"
#include <Windows.h>
#include <string>

typedef struct{
	int wWidth;
	int wHeight;
	DWORD wStyle;
	DWORD wExStyle;
} WNDVAR;

class WindowManager
{

public:
	class Exception : public BaseException
	{
	public:
		Exception(const char*, int, HRESULT) noexcept;
		const char* what() const noexcept override;
		virtual const char* getType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT) noexcept;
		HRESULT getErrorCode() const noexcept;
		std::string getErrorString() const noexcept;

	private:
		HRESULT hr;
	};

public:
	WindowManager(HINSTANCE);
	~WindowManager();

	bool CreateWnd(std::string, WNDVAR);

	//void setGfx(Graphics*);
	//void setInputMng(InputManager*);
	WNDVAR getWNDVAR() const noexcept;
	HWND getWHandler() const noexcept;
	HINSTANCE getHInstance() const noexcept;

private:
	static LRESULT CALLBACK WindowProcSetup(HWND, UINT, WPARAM, LPARAM);
	virtual LRESULT WindowProc(UINT, WPARAM, LPARAM);

private:
	HINSTANCE hInst;
	HWND wHandler;

	WNDVAR wndVar;
	std::string wName;
	std::string wClassName;
};

#endif