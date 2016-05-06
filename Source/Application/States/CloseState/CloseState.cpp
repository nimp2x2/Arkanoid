#include "CloseState.h"

#define SAFE_RELEASE(pointer) { if (pointer != nullptr) { delete (pointer); (pointer)=nullptr; } }

void CloseApp()
{
	SAFE_RELEASE(gGame);
	SAFE_RELEASE(gRenderer);
	SAFE_RELEASE(gTextureManager);
	SAFE_RELEASE(gCamera);
	SAFE_RELEASE(gOpnGLHelper);
	if (gWindowHandle)
	{
		if (DestroyWindow(gWindowHandle))
		{
			LOG("Window successfully destroyed");
		}
		else
		{
			LOG("FAILED to destory window");
		}
		gWindowHandle = NULL;
	}
	SAFE_RELEASE(gWndHelper);
}