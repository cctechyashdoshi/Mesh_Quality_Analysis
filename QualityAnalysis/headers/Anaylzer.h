#pragma once
#include "Triangulation.h"
#include "RealPoint.h"

namespace QualityAnalysis
{ 
	class Anaylzer
	{
	private:
		double calculateLength(Geometry::RealPoint p1, Geometry::RealPoint p2);
		std::vector<double> calculateTriangleInteriorAngles(Geometry::RealPoint firstVertex, Geometry::RealPoint secondVertex, Geometry::RealPoint thirdVertex);
		double calculateAngle(Geometry::RealPoint p1, Geometry::RealPoint p2, Geometry::RealPoint p3);
	public:
		Anaylzer();
		~Anaylzer();
		std::vector<int> identifyGoodAndBadAngles(Geometry::Triangulation& tri);
		std::vector<int> identifyGoodAndBadAspectRatio(Geometry::Triangulation& tri);
	};
}
