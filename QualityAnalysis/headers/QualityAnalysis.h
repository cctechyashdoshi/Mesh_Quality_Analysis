#pragma once

#include "Triangulation.h"

namespace QualityAnalysis {

	class QualityAnalysis
	{
		Geometry::Point negativePoint(const Geometry::Point& point);
		double clamp(double value, double min, double max);
		double calculateDistanceBetweenPoints(const Geometry::Point& firstPoint, const Geometry::Point& secondPoint);
		double calculateSingleTriangleArea(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
		double calculateSingleTriangleAspectRatio(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
		double calculateSingleTriangleInteriorAngle(Geometry::Triangle& triangle, Geometry::Triangulation triangulation);
		double calculateAngleBetweenVectors(const Geometry::Point& v1, const Geometry::Point& v2);
	public:
		QualityAnalysis();
		~QualityAnalysis();
		double surfaceArea(Geometry::Triangulation);
		int numberOfTriangles(Geometry::Triangulation);
		int numberOfVertices(Geometry::Triangulation);
		double aspectRatio(Geometry::Triangulation);
		double orthogonality(Geometry::Triangulation);
		double objectLength(Geometry::Triangulation);
		double objectBreadth(Geometry::Triangulation);
		double objectHeight(Geometry::Triangulation);
		double timeToLoad(Geometry::Triangulation);
		Geometry::Triangulation drawGoodAndBadTriangles(Geometry::Triangulation);
		Geometry::Triangulation drawBoundingBox(Geometry::Triangulation);
	};
}
