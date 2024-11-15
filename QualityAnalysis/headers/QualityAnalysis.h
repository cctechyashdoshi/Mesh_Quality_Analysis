#pragma once

#include "ModifiedTriangulation.h"
#include "ModifiedTriangle.h"

namespace QualityAnalysis {

	class QualityAnalysis
	{
		std::vector<double> negativePoint(std::vector<double> point);
		std::vector<double> convertPointToVector(Geometry::Point point, ModifiedTriangulation triangulation);
		double clamp(double value, double min, double max);
		double calculateDistanceBetweenPoints(std::vector<double> firstPoint, std::vector<double> secondPoint);
		double calculateAngleBetweenVectors(std::vector<double> v1, std::vector<double> v2);
	public:
		QualityAnalysis();
		~QualityAnalysis();
		double minX(ModifiedTriangulation triangulation);
		double minY(ModifiedTriangulation triangulation);
		double minZ(ModifiedTriangulation triangulation);
		double maxX(ModifiedTriangulation triangulation);
		double maxY(ModifiedTriangulation triangulation);
		double maxZ(ModifiedTriangulation triangulation);
		double surfaceArea(ModifiedTriangulation triangulation);
		double triangleDensity(ModifiedTriangulation triangulation);
		double objectLength(ModifiedTriangulation triangulation);
		double objectBreadth(ModifiedTriangulation triangulation);
		double objectHeight(ModifiedTriangulation triangulation);
		double calculateSingleTriangleAspectRatio(ModifiedTriangle& triangle, ModifiedTriangulation triangulation);
		double calculateSingleTriangleInteriorAngle(ModifiedTriangle& triangle, ModifiedTriangulation triangulation);
		double calculateSingleTriangleArea(ModifiedTriangle& triangle, ModifiedTriangulation triangulation);
		size_t numberOfTriangles(ModifiedTriangulation triangulation);
		size_t numberOfVertices(ModifiedTriangulation triangulation);
		std::vector<double> calcuateSingleTriangleNormal(std::vector<double> v1, std::vector<double> v2, std::vector<double> v3);
	};
}