#ifndef COLORED_SPRITE_H
#define COLORED_SPRITE_H

#include <Helpers\Math\Vector3f\Vector3f.h>

class ColoredSprite
{
public:
	Vector3f Position; // bottom left point
	float Width;
	float Height;
	Vector3f Color; // R G B

	ColoredSprite();
	ColoredSprite(Vector3f Position, float Width, float Height, Vector3f Color = Vector3f{ 1.f, 1.f, 1.f });
	~ColoredSprite();
};

#endif