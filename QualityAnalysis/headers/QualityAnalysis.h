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
		void GetMeshAspectRatioData(Triangulation& tri, MeshQualityData& meshData);
		void GetMeshOrthogonalityData(Triangulation& tri, MeshQualityData& meshData);
	};
}
