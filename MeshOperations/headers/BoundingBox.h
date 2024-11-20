#pragma once

#include "ModifiedTriangulation.h"

namespace MeshOperations
{
	class BoundingBox
	{
	public:
		double minX(MeshOperations::ModifiedTriangulation triangulation);
		double minY(MeshOperations::ModifiedTriangulation triangulation);
		double minZ(MeshOperations::ModifiedTriangulation triangulation);
		double maxX(MeshOperations::ModifiedTriangulation triangulation);
		double maxY(MeshOperations::ModifiedTriangulation triangulation);
		double maxZ(MeshOperations::ModifiedTriangulation triangulation);
		void createBoundingBoxTriangulation(ModifiedTriangulation triangulation);
		double boundingBoxArray[24];
	};
}
