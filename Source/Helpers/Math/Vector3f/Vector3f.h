#ifndef VECTOR3F_H
#define VECTOR3F_H

class Vector3f
{
public:
	float X;
	float Y;
	float Z;

	inline Vector3f(float _X = 0.f, float _Y = 0.f, float _Z = 0.f)
	{
		this->X = _X;
		this->Y = _Y;
		this->Z = _Z;
	}
	inline Vector3f(const Vector3f & Right)
	{
		this->X = Right.X;
		this->Y = Right.Y;
		this->Z = Right.Z;
	}

	inline Vector3f & operator=(const Vector3f & Right)
	{
		if (this == &Right)
		{
			return *this;
		}

		this->X = Right.X;
		this->Y = Right.Y;
		this->Z = Right.Z;
		return *this;
	}

	inline bool operator==(const Vector3f & Right) const
	{
		return ((this->X == Right.X) && (this->Y == Right.Y) && (this->Z == Right.Z));
	}
};

#endif