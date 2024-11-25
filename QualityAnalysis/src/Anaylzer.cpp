#include "Anaylzer.h"
#include "Triangulation.h"
#include "RealPoint.h"
#include <cmath>
#include <vector>
#include <memory>

#define M_PI 3.14159265358979323846

using namespace QualityAnalysis;

Anaylzer::Anaylzer()
{
}

Anaylzer::~Anaylzer()
{
}

double Anaylzer::calculateLength(Geometry::RealPoint p1, Geometry::RealPoint p2)
{
    double dx = p1.X() - p2.X();
    double dy = p1.Y() - p2.Y();
    double dz = p1.Z() - p2.Z();
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double Anaylzer::calculateAngle(Geometry::RealPoint p1, Geometry::RealPoint p2, Geometry::RealPoint p3)
{
    Geometry::RealPoint v1 = { p1.X() - p2.X(), p1.Y() - p2.Y(), p1.Z() - p2.Z() };
    Geometry::RealPoint v2 = { p3.X() - p2.X(), p3.Y() - p2.Y(), p3.Z() - p2.Z() };

    double dot = v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
    double mag1 = std::sqrt(v1.X() * v1.X() + v1.Y() * v1.Y() + v1.Z() * v1.Z());
    double mag2 = std::sqrt(v2.X() * v2.X() + v2.Y() * v2.Y() + v2.Z() * v2.Z());

    double angleRadians = std::acos(dot / (mag1 * mag2));

    // Convert radians to degrees
    double angleDegrees = angleRadians * (180.0 / M_PI);

    return angleDegrees;
}

std::vector<double> Anaylzer::calculateTriangleInteriorAngles(Geometry::RealPoint firstVertex, Geometry::RealPoint secondVertex, Geometry::RealPoint thirdVertex)
{
    double angleA = calculateAngle(secondVertex, firstVertex, thirdVertex);
    double angleB = calculateAngle(firstVertex, secondVertex, thirdVertex);
    double angleC = calculateAngle(firstVertex, thirdVertex, secondVertex);
    return { angleA,angleB,angleC };
}

std::vector<int> Anaylzer::identifyGoodAndBadAngles(Geometry::Triangulation& tri)
{
    std::vector<int> angleAnalysis;
    const double tolerance = 5.0;

    for (const Geometry::Triangle& triangle : tri.Triangles)
    {
        Geometry::RealPoint p1 = { tri.UniqueNumbers[triangle.P1().X()], tri.UniqueNumbers[triangle.P1().Y()], tri.UniqueNumbers[triangle.P1().Z()] };
        Geometry::RealPoint p2 = { tri.UniqueNumbers[triangle.P2().X()], tri.UniqueNumbers[triangle.P2().Y()], tri.UniqueNumbers[triangle.P2().Z()] };
        Geometry::RealPoint p3 = { tri.UniqueNumbers[triangle.P3().X()], tri.UniqueNumbers[triangle.P3().Y()], tri.UniqueNumbers[triangle.P3().Z()] };

        std::vector<double> angles = calculateTriangleInteriorAngles(p1, p2, p3);

        double minAngleLimit = 55;
		double maxAngleLimit = 65;
        for (double angle : angles)
        {
            if (angle >= minAngleLimit && angle <= maxAngleLimit)
            {
                angleAnalysis.push_back(1);
            }
            else 
            {
                angleAnalysis.push_back(0);
                break;
            }
        }
    }
    return angleAnalysis;
}

std::vector<int> Anaylzer::identifyGoodAndBadAspectRatio(Geometry::Triangulation& tri)
{
    std::vector<int> lengthAnalysis;
    for (Geometry::Triangle triangle : tri.Triangles)
    {
        Geometry::RealPoint p1 = { tri.UniqueNumbers[triangle.P1().X()],tri.UniqueNumbers[triangle.P1().Y()] ,tri.UniqueNumbers[triangle.P1().Z()] };
        Geometry::RealPoint p2 = { tri.UniqueNumbers[triangle.P2().X()],tri.UniqueNumbers[triangle.P2().Y()] ,tri.UniqueNumbers[triangle.P2().Z()] };
        Geometry::RealPoint p3 = { tri.UniqueNumbers[triangle.P3().X()],tri.UniqueNumbers[triangle.P3().Y()] ,tri.UniqueNumbers[triangle.P3().Z()] };

        double l1 = calculateLength(p1, p2);
        double l2 = calculateLength(p2, p3);
        double l3 = calculateLength(p3, p1);
        double avgaspectratio = std::max({ l1, l2, l3 }) / std::min({ l1, l2, l3 }); 
		double minAspectRatioLimit = 0.5;
		double maxAspectRatioLimit = 1.5;
        if (avgaspectratio >= minAspectRatioLimit && avgaspectratio <= maxAspectRatioLimit)
        {
            lengthAnalysis.push_back(1);
        }
        else
        {
            lengthAnalysis.push_back(0);
        }
    }
    return lengthAnalysis;
}
