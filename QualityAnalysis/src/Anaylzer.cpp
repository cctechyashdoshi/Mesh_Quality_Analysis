#include "Anaylzer.h"
#include "Triangulation.h"
#include "RealPoint.h"
#include <cmath>
#include <vector>
#include <memory>

#define M_PI 3.14159265358979323846
#define MIN_ANGLE_LIMIT 44
#define MAX_ANGLE_LIMIT 91
#define MIN_ASPECT_RATIO_LIMIT 0.5
#define MAX_ASPECT_RATIO_LIMIT 1.5

using namespace QualityAnalysis;
using namespace Geometry;

Anaylzer::Anaylzer()
{
}

Anaylzer::~Anaylzer()
{
}

double Anaylzer::calculateLength( RealPoint p1,  RealPoint p2)
{
	double dx = p1.X() - p2.X();
	double dy = p1.Y() - p2.Y();
	double dz = p1.Z() - p2.Z();
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double Anaylzer::calculateAngle( RealPoint p1,  RealPoint p2,  RealPoint p3)
{
	 RealPoint v1 = { p1.X() - p2.X(), p1.Y() - p2.Y(), p1.Z() - p2.Z() };
	 RealPoint v2 = { p3.X() - p2.X(), p3.Y() - p2.Y(), p3.Z() - p2.Z() };

	double dot = v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
	double mag1 = std::sqrt(v1.X() * v1.X() + v1.Y() * v1.Y() + v1.Z() * v1.Z());
	double mag2 = std::sqrt(v2.X() * v2.X() + v2.Y() * v2.Y() + v2.Z() * v2.Z());

	double angleRadians = std::acos(dot / (mag1 * mag2));

	// Convert radians to degrees
	double angleDegrees = angleRadians * (180.0 / M_PI);

	return angleDegrees;
}

std::vector<double> Anaylzer::calculateTriangleInteriorAngles( RealPoint firstVertex,  RealPoint secondVertex,  RealPoint thirdVertex)
{
	double angleA = calculateAngle(secondVertex, firstVertex, thirdVertex);
	double angleB = calculateAngle(firstVertex, secondVertex, thirdVertex);
	double angleC = calculateAngle(firstVertex, thirdVertex, secondVertex);
	return { angleA,angleB,angleC };
}

void Anaylzer::computeOrthogonality( Triangulation& tri,  Triangulation& orthogonalityTri)
{
	// create copy of original to modify orthogonality data

	orthogonalityTri.UniqueNumbers = tri.UniqueNumbers;
	orthogonalityTri.Triangles = tri.Triangles;

	for ( Triangle& triangle : orthogonalityTri.Triangles)
	{
		 RealPoint p1 = { orthogonalityTri.UniqueNumbers[triangle.P1().X()], orthogonalityTri.UniqueNumbers[triangle.P1().Y()], orthogonalityTri.UniqueNumbers[triangle.P1().Z()] };
		 RealPoint p2 = { orthogonalityTri.UniqueNumbers[triangle.P2().X()], orthogonalityTri.UniqueNumbers[triangle.P2().Y()], orthogonalityTri.UniqueNumbers[triangle.P2().Z()] };
		 RealPoint p3 = { orthogonalityTri.UniqueNumbers[triangle.P3().X()], orthogonalityTri.UniqueNumbers[triangle.P3().Y()], orthogonalityTri.UniqueNumbers[triangle.P3().Z()] };

		std::vector<double> angles = calculateTriangleInteriorAngles(p1, p2, p3);

		for (double angle : angles)
		{
			if (angle >= MIN_ANGLE_LIMIT && angle <= MAX_ANGLE_LIMIT)
			{
				triangle.setColor(0.0, 1.0, 0.0, 1.0);
			}
			else
			{
				triangle.setColor(1.0, 0.0, 0.0, 1.0);
				break;
			}
		}
	}
}

void Anaylzer::computeAspectRatio(Triangulation& tri, Triangulation& aspectRatioTri)
{
	// create copy of original to modify aspect ratio data

	aspectRatioTri.UniqueNumbers = tri.UniqueNumbers;
	aspectRatioTri.Triangles = tri.Triangles;

	for ( Triangle& triangle : aspectRatioTri.Triangles)
	{
		RealPoint p1 = { aspectRatioTri.UniqueNumbers[triangle.P1().X()],aspectRatioTri.UniqueNumbers[triangle.P1().Y()] ,aspectRatioTri.UniqueNumbers[triangle.P1().Z()] };
		RealPoint p2 = { aspectRatioTri.UniqueNumbers[triangle.P2().X()],aspectRatioTri.UniqueNumbers[triangle.P2().Y()] ,aspectRatioTri.UniqueNumbers[triangle.P2().Z()] };
		RealPoint p3 = { aspectRatioTri.UniqueNumbers[triangle.P3().X()],aspectRatioTri.UniqueNumbers[triangle.P3().Y()] ,aspectRatioTri.UniqueNumbers[triangle.P3().Z()] };

		double l1 = calculateLength(p1, p2);
		double l2 = calculateLength(p2, p3);
		double l3 = calculateLength(p3, p1);
		double avgaspectratio = std::max({ l1, l2, l3 }) / std::min({ l1, l2, l3 });

		if (avgaspectratio >= MIN_ASPECT_RATIO_LIMIT && avgaspectratio <= MAX_ASPECT_RATIO_LIMIT)
		{
			triangle.setColor(0.0, 1.0, 0.0, 1.0);
		}
		else
		{
			triangle.setColor(1.0, 0.0, 0.0, 1.0);
		}
	}
}
