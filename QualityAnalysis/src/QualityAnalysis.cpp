#include "QualityAnalysis.h"
#include "Triangulation.h"
#include <cmath>
#include <algorithm>
#include <vector>

#define M_PI 3.14159265358979323846

QualityAnalysis::QualityAnalysis::QualityAnalysis()
{
}

QualityAnalysis::QualityAnalysis::~QualityAnalysis()
{
}

std::vector<double> QualityAnalysis::QualityAnalysis::negativePoint(std::vector<double> point)
{
    return std::vector<double>{ -point[0], -point[1], -point[2]};
}

double QualityAnalysis::QualityAnalysis::clamp(double value, double min, double max)
{
    return (value < min) ? min : (value > max) ? max : value;
}

double QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(std::vector<double> firstPoint, std::vector<double> secondPoint)
{
    // Calculate the distance using Euclidean distance formula
    double dx = firstPoint[0] - secondPoint[0];
    double dy = firstPoint[1] - secondPoint[1];
    double dz = firstPoint[2] - secondPoint[2];

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double QualityAnalysis::QualityAnalysis::calculateAngleBetweenVectors(std::vector<double> v1, std::vector<double> v2) {
    double dotProduct = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    double magnitudeV1 = std::sqrt(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
    double magnitudeV2 = std::sqrt(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);
    double cosTheta = dotProduct / (magnitudeV1 * magnitudeV2);
    cosTheta = clamp(cosTheta, -1.0, 1.0); // Ensure the value is within the valid range for acos
    return std::acos(cosTheta) * (180.0 / M_PI); // Convert to degrees
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleArea(Geometry::Triangle& triangle, Geometry::Triangulation triangulation)
{
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    double vertex11 = triangulation.UniqueNumbers[vertex1.X()];
    double vertex12 = triangulation.UniqueNumbers[vertex1.Y()];
    double vertex13 = triangulation.UniqueNumbers[vertex1.Z()];

    double vertex21 = triangulation.UniqueNumbers[vertex2.X()];
    double vertex22 = triangulation.UniqueNumbers[vertex2.Y()];
    double vertex23 = triangulation.UniqueNumbers[vertex2.Z()];

    double vertex31 = triangulation.UniqueNumbers[vertex3.X()];
    double vertex32 = triangulation.UniqueNumbers[vertex3.Y()];
    double vertex33 = triangulation.UniqueNumbers[vertex3.Z()];

    std::vector<double> vertex1Double{ vertex11, vertex12, vertex13 };
    std::vector<double> vertex2Double{ vertex21, vertex22, vertex23 };
    std::vector<double> vertex3Double{ vertex31, vertex32, vertex33 };

    double side1 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex1Double, vertex2Double);
    double side2 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex2Double, vertex3Double);
    double side3 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex3Double, vertex1Double);

    double semiPerimeter = (side1 + side2 + side3) / 2;
    double area = std::sqrt(semiPerimeter * (semiPerimeter - side1) * (semiPerimeter - side2) * (semiPerimeter - side3));

    return area;
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleAspectRatio(Geometry::Triangle& triangle, Geometry::Triangulation triangulation)
{
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    double vertex11 = triangulation.UniqueNumbers[vertex1.X()];
    double vertex12 = triangulation.UniqueNumbers[vertex1.Y()];
    double vertex13 = triangulation.UniqueNumbers[vertex1.Z()];

    double vertex21 = triangulation.UniqueNumbers[vertex2.X()];
    double vertex22 = triangulation.UniqueNumbers[vertex2.Y()];
    double vertex23 = triangulation.UniqueNumbers[vertex2.Z()];

    double vertex31 = triangulation.UniqueNumbers[vertex3.X()];
    double vertex32 = triangulation.UniqueNumbers[vertex3.Y()];
    double vertex33 = triangulation.UniqueNumbers[vertex3.Z()];

    std::vector<double> vertex1Double{ vertex11, vertex12, vertex13 };
    std::vector<double> vertex2Double{ vertex21, vertex22, vertex23 };
    std::vector<double> vertex3Double{ vertex31, vertex32, vertex33 };

    double side1 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex1Double, vertex2Double);
    double side2 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex2Double, vertex3Double);
    double side3 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex3Double, vertex1Double);

    double longestEdge = std::max(std::max(side1, side2), side3);
    double shortestEdge = std::min(std::min(side1, side2), side3);

    double aspectRatio = longestEdge / shortestEdge;
    return aspectRatio;
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleInteriorAngle(Geometry::Triangle& triangle, Geometry::Triangulation triangulation) {
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    double vertex11 = triangulation.UniqueNumbers[vertex1.X()];
    double vertex12 = triangulation.UniqueNumbers[vertex1.Y()];
    double vertex13 = triangulation.UniqueNumbers[vertex1.Z()];

    double vertex21 = triangulation.UniqueNumbers[vertex2.X()];
    double vertex22 = triangulation.UniqueNumbers[vertex2.Y()];
    double vertex23 = triangulation.UniqueNumbers[vertex2.Z()];

    double vertex31 = triangulation.UniqueNumbers[vertex3.X()];
    double vertex32 = triangulation.UniqueNumbers[vertex3.Y()];
    double vertex33 = triangulation.UniqueNumbers[vertex3.Z()];

    std::vector<double> vertex1New{ vertex11, vertex12, vertex13 };
    std::vector<double> vertex2New{ vertex21, vertex22, vertex23 };
    std::vector<double> vertex3New{ vertex31, vertex32, vertex33 };

    std::vector<double> AB{ vertex2New[0] - vertex1New[0], vertex2New[1] - vertex1New[1], vertex2New[2] - vertex1New[2] };
    std::vector<double> BC{ vertex3New[0] - vertex2New[0], vertex3New[1] - vertex2New[1], vertex3New[2] - vertex2New[2] };
    std::vector<double> CA{ vertex1New[0] - vertex3New[0], vertex1New[1] - vertex3New[1], vertex1New[2] - vertex3New[2] };

    double angleA = calculateAngleBetweenVectors(AB, negativePoint(CA));
    double angleB = calculateAngleBetweenVectors(AB, BC);
    double angleC = calculateAngleBetweenVectors(BC, negativePoint(CA));

    double averageAngle = (angleA + angleB + angleC) / 3.0;

    return averageAngle;
}

double QualityAnalysis::QualityAnalysis::surfaceArea(Geometry::Triangulation triangulation)
{
	double totalSurfaceArea = 0;
	for (auto triangle : triangulation.Triangles)
	{
        totalSurfaceArea += QualityAnalysis::QualityAnalysis::calculateSingleTriangleArea(triangle, triangulation);
	}
	return totalSurfaceArea;
}

size_t QualityAnalysis::QualityAnalysis::numberOfTriangles(Geometry::Triangulation triangulation)
{
	return triangulation.Triangles.size();
}

size_t QualityAnalysis::QualityAnalysis::numberOfVertices(Geometry::Triangulation triangulation)
{
	return triangulation.UniqueNumbers.size();
}

double QualityAnalysis::QualityAnalysis::aspectRatio(Geometry::Triangulation triangulation)
{
	double totalAspectRatio = 0;
	for (auto triangle : triangulation.Triangles)
	{
		totalAspectRatio += QualityAnalysis::QualityAnalysis::calculateSingleTriangleAspectRatio(triangle, triangulation);
	}
	return totalAspectRatio / triangulation.Triangles.size();
}

double QualityAnalysis::QualityAnalysis::orthogonality(Geometry::Triangulation triangulation)
{
	double totalOrthogonality = 0;
	for (auto triangle : triangulation.Triangles)
	{
		totalOrthogonality += QualityAnalysis::QualityAnalysis::calculateSingleTriangleInteriorAngle(triangle, triangulation);
	}
	return totalOrthogonality / triangulation.Triangles.size();
}

double QualityAnalysis::QualityAnalysis::objectLength(Geometry::Triangulation triangulation) 
{
    double maxX = -1000000;
    double minX = 1000000;
    for (auto vertex : triangulation.UniqueNumbers) {
        if (vertex > maxX) {
            maxX = vertex;
        }
        if (vertex < minX) {
            minX = vertex;
        }
    }
    return maxX - minX;
}

double QualityAnalysis::QualityAnalysis::objectBreadth(Geometry::Triangulation triangulation)
{
	double maxY = -1000000;
	double minY = 1000000;
	for (auto vertex : triangulation.UniqueNumbers) {
		if (vertex > maxY) {
			maxY = vertex;
		}
		if (vertex < minY) {
			minY = vertex;
		}
	}
	return maxY - minY;
}

double QualityAnalysis::QualityAnalysis::objectHeight(Geometry::Triangulation triangulation)
{
	double maxZ = -1000000;
	double minZ = 1000000;
	for (auto vertex : triangulation.UniqueNumbers) {
		if (vertex > maxZ) {
			maxZ = vertex;
		}
		if (vertex < minZ) {
			minZ = vertex;
		}
	}
	return maxZ - minZ;
}
