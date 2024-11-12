#pragma once

#include "Triangulation.h"

namespace QualityAnalysis {

	class QualityAnalysis
	{
		double calculateDistanceBetweenPoints(const Geometry::Point& firstPoint, const Geometry::Point& secondPoint);
		double calculateSingleTriangleArea(Geometry::Triangle& triangle);
		double calculateSingleTriangleAspectRatio(Geometry::Triangle& triangle);
		double calculateSingleTriangleInteriorAngle(Geometry::Triangle& triangle);
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
