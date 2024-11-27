#include "QualityAnalysis.h"
#include "Anaylzer.h"
#include "Triangulation.h"
#include "MeshQualityData.h"

using namespace Geometry;
using namespace QualityAnalysis;

void MeshAnalysis::GetMeshOrthogonalityData(Triangulation& tri,  MeshQualityData& meshData)
{
	Anaylzer analyzedata;
	analyzedata.computeOrthogonality(tri, meshData.orthogonality.triangulation);
}

std::vector<double> QualityAnalysis::MeshAnalysis::getAngleValues(Triangulation& triangulation)
{
	Anaylzer analyzedata;
	std::vector<double> angles;
	for (Triangle& triangle : triangulation.Triangles)
	{
		RealPoint p1 = { triangulation.UniqueNumbers[triangle.P1().X()], triangulation.UniqueNumbers[triangle.P1().Y()], triangulation.UniqueNumbers[triangle.P1().Z()] };
		RealPoint p2 = { triangulation.UniqueNumbers[triangle.P2().X()], triangulation.UniqueNumbers[triangle.P2().Y()], triangulation.UniqueNumbers[triangle.P2().Z()] };
		RealPoint p3 = { triangulation.UniqueNumbers[triangle.P3().X()], triangulation.UniqueNumbers[triangle.P3().Y()], triangulation.UniqueNumbers[triangle.P3().Z()] };

		angles.push_back(analyzedata.calculateAngle(p2, p1, p3));
		angles.push_back(analyzedata.calculateAngle(p1, p2, p3));
		angles.push_back(analyzedata.calculateAngle(p2, p3, p1));
	}
	return angles;
}

void MeshAnalysis::GetMeshAspectRatioData(Triangulation& tri, MeshQualityData& meshData)
{
	Anaylzer analyzedata;
	analyzedata.computeAspectRatio(tri, meshData.aspectRatio.triangulation);
}
