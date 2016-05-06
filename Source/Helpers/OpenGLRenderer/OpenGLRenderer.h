#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <Helpers\OpenGLRenderer\Line\Line.h>
#include <Helpers\OpenGLRenderer\ColoredSprite\ColoredSprite.h>
#include <Helpers\OpenGLRenderer\TexturedColoredSprite\TexturedColoredSprite.h>
#include <cassert>

class OpenGLRenderer 
{
public:
	void BeginScene();
	void Render(const Line & Line);
	void Render(const ColoredSprite & ColoredSprite);
	void Render(const TexturedColoredSprite & TexturedColoredSprite);
	void EndScene();

	OpenGLRenderer(HDC DeviceContext, GLuint DefaultTexture);
	OpenGLRenderer(const OpenGLRenderer & Right) = delete;
	OpenGLRenderer(OpenGLRenderer && Right) = delete;
	OpenGLRenderer & operator=(const OpenGLRenderer & Right) = delete;
	OpenGLRenderer & operator=(OpenGLRenderer && Right) = delete;
	~OpenGLRenderer();
private:
	GLuint CurrentTexture;
	GLuint DefaultTexture;
	HDC DeviceContext;
	enum class PrimitiveType { NONE, LINE, COLORED_SPRITE, TEXTURED_COLORED_SPRITE } CurrentPrimitive;
};

#endif