#pragma once
#include "Triangulation.h"

namespace QualityAnalysis
{ 
	class Anaylzer
	{
	private:
		double calculateLength(std::vector<double> p1, std::vector<double> p2);
		std::vector<double> calculateTriangleAngles(std::vector<double> A, std::vector<double> B, std::vector<double> C);
		double calculateAngle(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3);
	public:
		Anaylzer();
		~Anaylzer();
		std::vector<int> angleAnalyzer(Geometry::Triangulation tri);
		std::vector<int> lengthAnalyzer(Geometry::Triangulation tri);
	};
}
