#pragma once
#include "Triangulation.h"

namespace QualityAnalysis
{ 
	class Anaylzer
	{
	private:
		double calculateLength(std::vector<double> p1, std::vector<double> p2);
		std::vector<double> calculateTriangleAngles(std::vector<double> a, std::vector<double> b, std::vector<double> c);
		double calculateAngle(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3);
	public:
		Anaylzer();
		~Anaylzer();
		std::vector<int> identifyGoodAndBadAngles(Geometry::Triangulation& tri);
		std::vector<int> identifyGoodAndBadAspectRatio(Geometry::Triangulation& tri);
	};
}
