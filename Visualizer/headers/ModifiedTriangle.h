#pragma once

#include "Triangle.h"


class ModifiedTriangle : public Geometry::Triangle
{
public:
	double color[3];
	ModifiedTriangle(const Geometry::Point& normal, const Geometry::Point& p1, const Geometry::Point& p2, const Geometry::Point& p3): Triangle(normal, p1, p2, p3) {}
};