#pragma once

#include "ModifiedTriangulation.h"

class BoundingBox
{
	double minX(ModifiedTriangulation triangulation);
	double minY(ModifiedTriangulation triangulation);
	double minZ(ModifiedTriangulation triangulation);
	double maxX(ModifiedTriangulation triangulation);
	double maxY(ModifiedTriangulation triangulation);
	double maxZ(ModifiedTriangulation triangulation);
public:
	BoundingBox();
	~BoundingBox();
	void createBoundingBoxTriangulation(ModifiedTriangulation triangulation);
	std::vector<std::vector<std::vector<double>>> boundingBoxTriangulation;
};
