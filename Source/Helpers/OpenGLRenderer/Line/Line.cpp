#include "Line.h"

Line::Line() : Point1{}, Point2{}, Color{ 1.f, 1.f, 1.f }
{
}

Line::Line(const Vector3f & _Point1, const Vector3f & _Point2, const Vector3f & _Color) : Point1{ _Point1 }, Point2{ _Point2 }, Color{ _Color }
{
}

Line::~Line()
{
}