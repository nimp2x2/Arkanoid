#ifndef LINE_H
#define LINE_H

#include <Helpers\Math\Vector3f\Vector3f.h>
#include <Helpers\Math\Vector2f\Vector2f.h>

class Line
{
public:
	Vector3f Point1;
	Vector3f Point2;
	Vector3f Color; // R G B

	Line();
	Line(const Vector3f & Point1, const Vector3f & Point2, const Vector3f & Color = Vector3f{1.f, 1.f, 1.f});
	~Line();
};

#endif