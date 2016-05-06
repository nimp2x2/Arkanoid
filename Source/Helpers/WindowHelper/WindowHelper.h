#ifndef WINDOW_H
#define WINDOW_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>
#include <Helpers\Logger\Logger.h>
#include <memory>

class WindowHelper
{
public:
	HWND CreateWnd(const wchar_t * WindowName, int Width, int Height);
	WindowHelper(const wchar_t * WindowClassName, LRESULT (CALLBACK * WindowClassMessageProc)(HWND, UINT, WPARAM, LPARAM));
	WindowHelper(const WindowHelper & Right) = delete;
	WindowHelper(WindowHelper && Right);
	WindowHelper& operator=(const WindowHelper & Right) = delete;
	WindowHelper& operator=(WindowHelper && Right);
	~WindowHelper();
private:
	bool bWindowClassRegistered;
	std::wstring WindowClassName;
	LRESULT (CALLBACK * WindowClassMessageProc)(HWND, UINT, WPARAM, LPARAM);
};

#endif