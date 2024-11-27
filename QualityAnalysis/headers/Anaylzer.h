#pragma once
#include "Triangulation.h"
#include "RealPoint.h"

using namespace std;
using namespace Geometry;

namespace QualityAnalysis
{ 
	class Anaylzer
	{
	private:
		double calculateLength( RealPoint p1,  RealPoint p2);
		vector<double> calculateTriangleInteriorAngles( RealPoint firstVertex,  RealPoint secondVertex,  RealPoint thirdVertex);
		double calculateAngle( RealPoint p1,  RealPoint p2,  RealPoint p3);

	public:
		Anaylzer();
		~Anaylzer();
		void computeOrthogonality( Triangulation& tri,  Triangulation& orthogonalityTri);
		void computeAspectRatio( Triangulation& tri,  Triangulation& aspectRatioTri);
	};
}
