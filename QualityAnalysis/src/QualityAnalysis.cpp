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

void MeshAnalysis::GetMeshAspectRatioData(Triangulation& tri, MeshQualityData& meshData)
{
	Anaylzer analyzedata;
	analyzedata.computeAspectRatio(tri, meshData.aspectRatio.triangulation);
}
