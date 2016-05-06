#include "ColoredSprite.h"

ColoredSprite::ColoredSprite() : Position{}, Width{ 0.f }, Height{ 0.f }, Color{ 1.f, 1.f, 1.f }
{
}

ColoredSprite::ColoredSprite(Vector3f _Position, float _Width, float _Height, Vector3f _Color)
	: Position{ _Position }, Width{ _Width }, Height{ _Height }, Color{ _Color }
{
}

ColoredSprite::~ColoredSprite()
{
}