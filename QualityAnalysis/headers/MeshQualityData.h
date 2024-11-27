#pragma once

#include "Triangulation.h"
#include <vector>

using namespace Geometry;

namespace QualityAnalysis
{
	class MeshQualityData
	{
	public:

		struct Orthogonality
		{
			Triangulation triangulation;
		};

		struct AspectRatio
		{
			Triangulation triangulation;
		};

		Orthogonality orthogonality;
		AspectRatio aspectRatio;
	};
}
