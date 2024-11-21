#include "QualityAnalysis.h"
#include "Triangulation.h"
#include "BoundingBox.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include <limits>

#define PI 3.14159265358979323846

using namespace Geometry;

std::vector<std::vector<Triangle, int>> QualityAnalysis::QualityAnalysis::angleInformation(Triangulation& triangulation,std::vector<int> angleAnalysis)
{
	std::vector<std::vector<Triangle, int>> angleList;
	for (int i = 0; i < triangulation.Triangles.size(); i++)
	{
		std::vector<Triangle, int> triangleint((triangulation.Triangles[i], angleAnalysis[i]));
		angleList.push_back(triangleint);
	}
}

std::vector<std::vector<Triangle, int>> QualityAnalysis::QualityAnalysis::lengthInformation(Triangulation& triangulation, std::vector<int> lengthAnalysis)
{
	std::vector<std::vector<Triangle, int>> angleList;
	for (int i = 0; i < triangulation.Triangles.size(); i++)
	{
		std::vector<Triangle, int> triangleint((triangulation.Triangles[i], lengthAnalysis[i]));
		angleList.push_back(triangleint);
	}
	return angleList
}