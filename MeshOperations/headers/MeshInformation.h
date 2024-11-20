#pragma once

#include "ModifiedTriangulation.h"

namespace MeshOperations
{
	class MeshInformation
	{
	public:
		double triangleDensity(ModifiedTriangulation triangulation);
		double objectLength(ModifiedTriangulation triangulation);
		double objectBreadth(ModifiedTriangulation triangulation);
		double objectHeight(ModifiedTriangulation triangulation);
		size_t numberOfTriangles(ModifiedTriangulation triangulation);
		size_t numberOfVertices(ModifiedTriangulation triangulation);
	};
}