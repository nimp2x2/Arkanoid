#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cmath>

class Vector2f
{
public:
	float X;
	float Y;

	inline Vector2f(float _X = 0.f, float _Y = 0.f)
	{
		this->X = _X;
		this->Y = _Y;
	}
	inline Vector2f(const Vector2f & Right)
	{
		this->X = Right.X;
		this->Y = Right.Y;
	}

	inline Vector2f & operator=(const Vector2f & Right)
	{
		if (this == &Right)
		{
			return *this;
		}

		this->X = Right.X;
		this->Y = Right.Y;
		return *this;
	}
	inline void Normalize()
	{
		const float Modulus = sqrtf((this->X * this->X) + (this->Y * this->Y));
		this->X /= Modulus;
		this->Y /= Modulus;
	}
};

#endif