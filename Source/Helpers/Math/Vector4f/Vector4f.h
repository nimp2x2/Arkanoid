#ifndef VECTOR4F_H
#define VECTOR4F_H

class Vector4f
{
public:
	float X;
	float Y;
	float Z;
	float W;

	inline Vector4f(float _X = 0.f, float _Y = 0.f, float _Z = 0.f, float _W = 0.f)
	{
		this->X = _X;
		this->Y = _Y;
		this->Z = _Z;
		this->W = _W;
	}
	inline Vector4f(const Vector4f & Right)
	{
		this->X = Right.X;
		this->Y = Right.Y;
		this->Z = Right.Z;
		this->W = Right.W;
	}

	inline Vector4f & operator=(const Vector4f & Right)
	{
		if (this == &Right)
		{
			return *this;
		}

		this->X = Right.X;
		this->Y = Right.Y;
		this->Z = Right.Z;
		this->W = Right.W;
		return *this;
	}
};

#endif