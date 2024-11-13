#pragma once

#include "Triangulation.h"

namespace QualityAnalysis {

	class QualityAnalysis
	{
		std::vector<double> negativePoint(std::vector<double> point);
		double clamp(double value, double min, double max);
		double calculateDistanceBetweenPoints(std::vector<double> firstPoint, std::vector<double> secondPoint);
		double calculateSingleTriangleArea(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
		double calculateAngleBetweenVectors(std::vector<double> v1, std::vector<double> v2);
		double calculateSingleTriangleAspectRatio(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
		double calculateSingleTriangleInteriorAngle(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
	public:
		QualityAnalysis();
		~QualityAnalysis();
		size_t numberOfTriangles(Geometry::Triangulation triangulation);
		size_t numberOfVertices(Geometry::Triangulation triangulation);
		double surfaceArea(Geometry::Triangulation triangulation);
		double aspectRatio(Geometry::Triangulation triangulation);
		double orthogonality(Geometry::Triangulation triangulation);
		double objectLength(Geometry::Triangulation triangulation);
		double objectBreadth(Geometry::Triangulation triangulation);
		double objectHeight(Geometry::Triangulation triangulation);
		double timeToLoad(Geometry::Triangulation triangulation);
		Geometry::Triangulation drawGoodAndBadTriangles(Geometry::Triangulation triangulation);
		Geometry::Triangulation drawBoundingBox(Geometry::Triangulation triangulation);
	};
}
