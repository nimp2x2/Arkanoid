#include "OrthoCamera.h"

OrthoCamera::OrthoCamera(int SceneWidth, int SceneHeight) : Width{ SceneWidth }, Height{ SceneHeight }
{
	assert(SceneWidth);
	assert(SceneHeight);
	this->Aspect = (static_cast<float>(SceneWidth)) / (static_cast<float>(SceneHeight));
}

void OrthoCamera::ApplyTransformations(int WindowWidth, int WindowHeight) const
{
	glViewport(0, 0, WindowWidth, WindowHeight);

	const float WindowAspect = (static_cast<float>(WindowWidth)) / (static_cast<float>(WindowHeight));
	const float HeightScale = WindowAspect / this->Aspect;
	GLdouble Left = 0;
	GLdouble Right = this->Width;
	GLdouble Bottom = 0;
	GLdouble Top = this->Height;

	if (HeightScale > 1.0f) {
		//pillarbox
		const float WidthScale = 1.0f / HeightScale;
		Left = -((1.0f - WidthScale) / 2.0f) * this->Width;
		Right = ((1.0f - WidthScale) / 2.0f) * this->Width + this->Width;
	}
	else
	{
		//lettebox
		Bottom = -((1.0f - HeightScale) / 2.0f) * this->Height;
		Top = ((1.0f - HeightScale) / 2.0f) * this->Height + this->Height;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(Left, Right, Bottom, Top, 1, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}