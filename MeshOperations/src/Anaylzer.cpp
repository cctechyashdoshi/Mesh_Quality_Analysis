#include "Anaylzer.h"
#include "Triangulation.h"
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

double Anaylzer::calculateLength(std::vector<double> p1, std::vector<double> p2)
{
    double dx = p1[0] - p2[0];
    double dy = p1[1] - p2[1];
    double dz = p1[2] - p2[2];
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double calculateAngle(std::vector<double> p1, std::vector<double> p2, std::vector<double> p3)
{
    std::vector<double> v1 = { p1[0] - p2[0], p1[1] - p2[1], p1[2] - p2[2] };
    std::vector<double> v2 = { p3[0] - p2[0], p3[1] - p2[1], p3[2] - p2[2] };

    double dot = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    double mag1 = std::sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
    double mag2 = std::sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);

    double angleRadians = std::acos(dot / (mag1 * mag2));

    // Convert radians to degrees
    double angleDegrees = angleRadians * (180.0 / M_PI);

    return angleDegrees;
}

std::vector<double> Anaylzer::calculateTriangleAngles(std::vector<double> A,std::vector<double> B,std::vector<double> C)
{
    double angleA = calculateAngle(B, A, C);
    double angleB = calculateAngle(A, B, C);
    double angleC = calculateAngle(A, C, B);
    return std::vector<double> {angleA,angleB,angleC};
}

std::vector<int> Anaylzer::AngleAnalyzer(Geometry::Triangulation tri)
{
	std::vector<int> angleAnalysis;
    for (Geometry::Triangle triangle : tri.Triangles)
    {
        std::vector<double> p1 = { tri.UniqueNumbers[triangle.P1().X()],tri.UniqueNumbers[triangle.P1().Y()] ,tri.UniqueNumbers[triangle.P1().Z()] };
        std::vector<double> p2 = { tri.UniqueNumbers[triangle.P2().X()],tri.UniqueNumbers[triangle.P2().Y()] ,tri.UniqueNumbers[triangle.P2().Z()] };
        std::vector<double> p3 = { tri.UniqueNumbers[triangle.P3().X()],tri.UniqueNumbers[triangle.P3().Y()] ,tri.UniqueNumbers[triangle.P3().Z()] };
        std::vector<double> angles = calculateTriangleAngles(p1, p2, p3);
		double avgAngle = (angles[0] + angles[1] + angles[2]) / 3;
        if (avgAngle >= 50 && avgAngle <= 70)
        {
			angleAnalysis.push_back(1);
        }
        else
			angleAnalysis.push_back(0);
	}
	return angleAnalysis;   
}

std::vector<int> Anaylzer::LengthAnalyzer(Geometry::Triangulation tri)
{
    std::vector<int> lengthAnalysis;
    for (Geometry::Triangle triangle : tri.Triangles)
    {
        std::vector<double> p1 = { tri.UniqueNumbers[triangle.P1().X()],tri.UniqueNumbers[triangle.P1().Y()] ,tri.UniqueNumbers[triangle.P1().Z()] };
        std::vector<double> p2 = { tri.UniqueNumbers[triangle.P2().X()],tri.UniqueNumbers[triangle.P2().Y()] ,tri.UniqueNumbers[triangle.P2().Z()] };
        std::vector<double> p3 = { tri.UniqueNumbers[triangle.P3().X()],tri.UniqueNumbers[triangle.P3().Y()] ,tri.UniqueNumbers[triangle.P3().Z()] };

        double l1 = calculateLength(p1, p2);
        double l2 = calculateLength(p2, p3);
        double l3 = calculateLength(p3, p1);
        double avgaspectratio = std::max({ l1, l2, l3 }) / std::min({ l1, l2, l3 }); 
        if (avgaspectratio >= 0.8 && avgaspectratio <= 1.2)
        {
            lengthAnalysis.push_back(1);
        }
        else
            lengthAnalysis.push_back(0);
    }
    return lengthAnalysis;
}
