#include "QualityAnalysis.h"
#include "Anaylzer.h"

QualityAnalysis::Anaylzer anaylzer;

std::vector<QualityAnalysis::MeshAnalysis::TriangleAnalysisResult> QualityAnalysis::MeshAnalysis::calculateOrthogonality(Geometry::Triangulation& triangulation)
{
	std::vector<TriangleAnalysisResult> angleList;
	std::vector<int> angleAnalysis = anaylzer.identifyGoodAndBadAngles(triangulation);
	//std::vector<int> angleAnalysis = {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0};
	std::vector<TriangleAnalysisResult> triangleAnalysis; 

	for (size_t i = 0; i < triangulation.Triangles.size(); ++i)
	{
		TriangleAnalysisResult result = { triangulation.Triangles[i], angleAnalysis[i] };
		angleList.push_back(result);
	}
	return angleList;
}

std::vector<QualityAnalysis::MeshAnalysis::TriangleAnalysisResult> QualityAnalysis::MeshAnalysis::calculateAspectRatio(Geometry::Triangulation& triangulation)
{
	std::vector<TriangleAnalysisResult> aspectRatioList;
	std::vector<int> lengthAnalysis = anaylzer.identifyGoodAndBadAspectRatio(triangulation);

	for (size_t i = 0; i < triangulation.Triangles.size(); ++i)
	{
		TriangleAnalysisResult result = { triangulation.Triangles[i], lengthAnalysis[i] };
		aspectRatioList.push_back(result);
	}
	return aspectRatioList;
}
