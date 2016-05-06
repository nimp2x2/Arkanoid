#include "OpenGLHelper.h"

OpengGLHelper::OpengGLHelper() : DeviceContext{ NULL }, RenderingContext{ NULL }, WindowHandle{ NULL }
{
}

OpengGLHelper::~OpengGLHelper()
{
	this->Cleanup();
}

bool OpengGLHelper::Init(HWND _WindowHandle)
{
	assert(_WindowHandle);

	GLuint PixelFormat;
	PIXELFORMATDESCRIPTOR pfd;
	RtlSecureZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	if (DeviceContext = GetDC(_WindowHandle))
	{
		LOG("DeviceContext acquired");
	}
	else 
	{
		LOG("FAILED to acquire DeviceContext");
		this->Cleanup();
		return false;
	}

	if (PixelFormat = ChoosePixelFormat(DeviceContext, &pfd))
	{
		LOG("Pixel format chosen");
	}
	else
	{
		LOG("FAILED to choose pixel format");
		this->Cleanup();
		return false;
	}

	if (SetPixelFormat(DeviceContext, PixelFormat, &pfd))
	{
		LOG("Pixel format set");
	}
	else 
	{
		LOG("FAILED to set pixel format");
		this->Cleanup();
		return false;
	}

	if (RenderingContext = wglCreateContext(DeviceContext))
	{
		LOG("RenderingContext created");
	}
	else
	{
		LOG("FAILED to create RenderingContext");
		this->Cleanup();
		return false;
	}

	if (wglMakeCurrent(DeviceContext, RenderingContext))
	{
		LOG("Binded DeviceContext and RenderingContext to OpenGL");
	}
	else
	{
		LOG("FAILED to bind DeviceContext and RenderingContext to OpenGL");
		this->Cleanup();
		return false;
	}
	this->WindowHandle = _WindowHandle;
	return true;
}

void OpengGLHelper::Cleanup()
{
	if (RenderingContext)
	{
		if (wglMakeCurrent(NULL, NULL))
		{
			LOG("Unbinded DeviceContext and RenderingContext");
		}
		else
		{
			LOG("FAILED to unbind DeviceContext and RenderingContext");
		}

		if (wglDeleteContext(RenderingContext))
		{
			LOG("RenderingContext released");
		}
		else
		{
			LOG("FAILED to release RenderingContext");
		}
		RenderingContext = NULL;
	}

	if (DeviceContext)
	{
		if (ReleaseDC(WindowHandle, DeviceContext)) 
		{
			LOG("DeviceContext released");
		}
		else
		{
			LOG("FAILED to release DeviceContext");
		}
		DeviceContext = NULL;
	}
	this->WindowHandle = NULL;
}