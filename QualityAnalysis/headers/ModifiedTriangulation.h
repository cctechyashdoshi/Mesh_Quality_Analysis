#pragma once

#include "Triangulation.h"
#include "ModifiedTriangle.h"

class ModifiedTriangulation : public Geometry::Triangulation
{
public:
	ModifiedTriangulation();
	~ModifiedTriangulation();
	double _minX;
	double _maxX;
	double _minY;
	double _maxY;
	double _minZ;
	double _maxZ;
	std::vector<ModifiedTriangle> mTriangles;
};