#include "QualityAnalysis.h"
#include "Anaylzer.h"

namespace QualityAnalysis
{
	std::vector<std::vector<QualityAnalysis::QualityAnalysis::TriangleAnalysisResult>> QualityAnalysis::calculateOrthogonality( Geometry::Triangulation& triangulation)
	{
		Anaylzer anaylzer;
		std::vector<std::vector<TriangleAnalysisResult>> angleList;
		std::vector<int> angleAnalysis = anaylzer.AngleAnalyzer(triangulation);

		for (size_t i = 0; i < triangulation.Triangles.size(); ++i)
		{
			std::vector<TriangleAnalysisResult> triangleAnalysis;
			TriangleAnalysisResult result = { triangulation.Triangles[i], angleAnalysis[i] };
			triangleAnalysis.push_back(result);
			angleList.push_back(triangleAnalysis);
		}
		return angleList;
	}

	std::vector<std::vector<QualityAnalysis::QualityAnalysis::TriangleAnalysisResult>> QualityAnalysis::calculateAspectRatio( Geometry::Triangulation& triangulation)
	{
		Anaylzer anaylzer;
		std::vector<std::vector<TriangleAnalysisResult>> aspectRatioList;
		std::vector<int> lengthAnalysis = anaylzer.LengthAnalyzer(triangulation);
		for (size_t i = 0; i < triangulation.Triangles.size(); ++i)
		{
			std::vector<TriangleAnalysisResult> triangleAnalysis;
			TriangleAnalysisResult result = { triangulation.Triangles[i], lengthAnalysis[i] };
			triangleAnalysis.push_back(result);
			aspectRatioList.push_back(triangleAnalysis);
		}
		return aspectRatioList;
	}
}
