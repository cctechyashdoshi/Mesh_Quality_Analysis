#pragma once

#include "Triangulation.h"
#include <vector>

namespace QualityAnalysis
{
	class MeshAnalysis
	{
	public:
		struct TriangleAnalysisResult {
			Geometry::Triangle triangle;
			int value;
		};
		std::vector<TriangleAnalysisResult> calculateOrthogonality(Geometry::Triangulation& triangulation);
		std::vector<TriangleAnalysisResult> calculateAspectRatio(Geometry::Triangulation& triangulation);
	};
}
