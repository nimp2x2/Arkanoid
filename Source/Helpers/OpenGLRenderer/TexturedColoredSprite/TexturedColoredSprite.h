#ifndef COLORED_TEXTURED_SPRITE_H
#define COLORED_TEXTURED_SPRITE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <gl\gl.h>
#include <Helpers\Math\Vector3f\Vector3f.h>
#include <Helpers\Math\Vector4f\Vector4f.h>

class TexturedColoredSprite
{
public:
	Vector3f Position;
	float Width;
	float Height;
	Vector3f Color; // R G B
	GLuint Texture;
	Vector4f TextureCoordinates; // x0 y0 x1 y1

	TexturedColoredSprite();
	~TexturedColoredSprite();
	TexturedColoredSprite(Vector3f Position, float Width, float Height, Vector3f Color = Vector3f{ 1.f, 1.f, 1.f }, GLuint Texture = 0, Vector4f TextureCoordinates = Vector4f{ 0.f, 0.f, 1.f, 1.f });
};

#endif