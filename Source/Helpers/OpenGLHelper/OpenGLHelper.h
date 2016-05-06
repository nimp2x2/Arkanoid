#ifndef OPENGL_HELPER_H
#define OPENGL_HELPER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Helpers\Logger\Logger.h>
#include <gl\gl.h>

class OpengGLHelper 
{
public:
	bool Init(HWND WindowHandle);
	inline HDC	GetDeviceContext() const { return this->DeviceContext; }
	inline HGLRC GetRenderingContext() const { return this->RenderingContext; }

	OpengGLHelper();
	OpengGLHelper(const OpengGLHelper & Right) = delete;
	OpengGLHelper(OpengGLHelper && Right) = delete;
	OpengGLHelper & operator=(const OpengGLHelper & Right) = delete;
	OpengGLHelper & operator=(OpengGLHelper && Right) = delete;
	~OpengGLHelper();
private:
	HDC	DeviceContext;
	HGLRC RenderingContext;
	HWND WindowHandle;
	void Cleanup();
};

#endif