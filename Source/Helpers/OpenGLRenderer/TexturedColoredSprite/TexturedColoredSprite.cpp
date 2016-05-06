#include "TexturedColoredSprite.h"

TexturedColoredSprite::TexturedColoredSprite()
	: Position{}, Width{ 0.f }, Height{ 0.f }, Color{ 1.f, 1.f, 1.f }, Texture{ 0 }, TextureCoordinates{ 0.f, 0.f, 1.f, 1.f }
{
}

TexturedColoredSprite::TexturedColoredSprite(Vector3f _Position, float _Width, float _Height, Vector3f _Color, GLuint _Texture, Vector4f _TextureCoordinates)
	: Position{ _Position }, Width{ _Width }, Height{ _Height }, Color{ _Color }, Texture{ _Texture }, TextureCoordinates{ _TextureCoordinates }
{
}

TexturedColoredSprite::~TexturedColoredSprite()
{
}