#pragma once

#include "Triangle.h"

class ModifiedTriangle : public Geometry::Triangle
{
public:
	ModifiedTriangle();
	ModifiedTriangle(const Geometry::Point& normal, const Geometry::Point& p1, const Geometry::Point& p2, const Geometry::Point& p3);
	~ModifiedTriangle();
	double color[3];
};