#include "WindowHelper.h"

WindowHelper::WindowHelper(const wchar_t * _WindowClassName, LRESULT(CALLBACK * _WindowClassMessageProc)(HWND, UINT, WPARAM, LPARAM))
	:WindowClassName(_WindowClassName), WindowClassMessageProc{ _WindowClassMessageProc }, bWindowClassRegistered{ false }
{
	assert(_WindowClassName);
	assert(_WindowClassMessageProc);
}

WindowHelper::~WindowHelper() 
{
	if (this->bWindowClassRegistered) 
	{
		if (UnregisterClass(this->WindowClassName.c_str(), GetModuleHandle(NULL)))
		{
			LOG("Window class successfully unregistered");
		}
		else
		{
			LOG("FAILEd to unregister window class");
		}
	}
}

WindowHelper::WindowHelper(WindowHelper && Right) :
WindowClassName(Right.WindowClassName), WindowClassMessageProc{ Right.WindowClassMessageProc }, bWindowClassRegistered{ Right.bWindowClassRegistered }
{
	Right.bWindowClassRegistered = false;
}

WindowHelper& WindowHelper::operator=(WindowHelper && Right)
{
	if (&Right == this) {
		return *this;
	}
	this->WindowClassName = Right.WindowClassName;
	this->WindowClassMessageProc = Right.WindowClassMessageProc;
	this->bWindowClassRegistered = Right.bWindowClassRegistered;
	Right.bWindowClassRegistered = false;
	Right.WindowClassName.clear();
	return *this;
}

HWND WindowHelper::CreateWnd(const wchar_t * WindowName, int Width, int Height)
{
	assert(WindowName);
	assert(Width > 0);
	assert(Height > 0);

	if (!this->bWindowClassRegistered) 
	{
		WNDCLASSEX WinClass;
		RtlSecureZeroMemory(&WinClass, sizeof(WNDCLASSEX));
		WinClass.hInstance = GetModuleHandle(NULL);
		WinClass.cbClsExtra = NULL;
		WinClass.cbSize = sizeof(WNDCLASSEX);
		WinClass.cbWndExtra = NULL;
		WinClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		WinClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		WinClass.hIcon = NULL;
		WinClass.hIconSm = NULL;
		WinClass.lpfnWndProc = (WNDPROC)this->WindowClassMessageProc;
		WinClass.lpszClassName = this->WindowClassName.c_str();
		WinClass.lpszMenuName = NULL;
		WinClass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;

		if (!RegisterClassEx(&WinClass)) {
			LOG("FAILED to register window class");
			return false;
		}
		LOG("Window class successfully registered");
		this->bWindowClassRegistered = true;
	}

	RECT DesktopRect;
	GetWindowRect(GetDesktopWindow(), &DesktopRect);

	RECT WindowRect;
	WindowRect.left = static_cast<int>(((DesktopRect.right - DesktopRect.left) / 2) - (Width / 2));
	WindowRect.top = static_cast<int>(((DesktopRect.bottom - DesktopRect.top) / 2) - (Height / 2));
	WindowRect.right = WindowRect.left + Width;
	WindowRect.bottom = WindowRect.top + Height;
	AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, NULL);

	const HWND WindowHandle = CreateWindow(this->WindowClassName.c_str(), WindowName, WS_OVERLAPPEDWINDOW, WindowRect.left, WindowRect.top, 
		WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, NULL, NULL, GetModuleHandle(NULL), NULL);

	if (WindowHandle) 
	{
		LOG("Window successfully created");
	}
	else 
	{
		LOG("FAILED to create a window");
	}
	return WindowHandle;
}