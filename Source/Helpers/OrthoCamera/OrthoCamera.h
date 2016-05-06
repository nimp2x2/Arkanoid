#ifndef ORTHO_CAMERA_H
#define ORTHO_CAMERA_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <Helpers\Logger\Logger.h>

class OrthoCamera 
{
public:
	OrthoCamera(int SceneWidth, int SceneHeight);
	void ApplyTransformations(int WindowWidth, int WindowHeight) const;
private:
	int Width;
	int Height;
	float Aspect;
};

#endif