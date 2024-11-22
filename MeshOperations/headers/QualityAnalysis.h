#pragma once

#include "Triangulation.h"
#include <vector>

namespace QualityAnalysis
{
	class QualityAnalysis
	{
	public:
		struct TriangleAnalysisResult {
			Geometry::Triangle triangle;
			int value;
		};

		std::vector<std::vector<TriangleAnalysisResult>> calculateOrthogonality(Geometry::Triangulation& triangulation);

		std::vector<std::vector<TriangleAnalysisResult>> calculateAspectRatio(Geometry::Triangulation& triangulation);
	};
}
