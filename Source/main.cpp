#include <Application\States\CloseState\CloseState.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

LRESULT CALLBACK MsgProc(HWND HWND, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_SIZE:
		if (gCamera)
		{
			RECT WindowClientRect;
			GetClientRect(gWindowHandle, &WindowClientRect);
			gCamera->ApplyTransformations(WindowClientRect.right - WindowClientRect.left, WindowClientRect.bottom - WindowClientRect.top);
		}
		break;
	}
	return DefWindowProc(HWND, uMsg, wParam, lParam);
}

bool Render(DWORD dt)
{
	return gGame->Render(dt);
}

bool Logic(DWORD dt)
{
	return gGame->Logic(dt);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (InitApp()) {
		MainLoop loop(60, Render, Logic);
		loop.Run();
	}
	CloseApp();
	return 0;
}

