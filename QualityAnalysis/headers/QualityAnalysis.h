#pragma once

#include "Triangulation.h"
#include "MeshQualityData.h"
#include <vector>

using namespace Geometry;

namespace QualityAnalysis
{
	class MeshAnalysis
	{

	public:
		std::vector<double> getAngleValues(Triangulation& triangulation);
		void GetMeshAspectRatioData(Triangulation& tri, MeshQualityData& meshData);
		void GetMeshOrthogonalityData(Triangulation& tri, MeshQualityData& meshData);
	};
}
