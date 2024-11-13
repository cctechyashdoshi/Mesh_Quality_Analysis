#include "QualityAnalysis.h"
#include "Triangulation.h"
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include "Point.h"

#define PI 3.14159265358979323846

QualityAnalysis::QualityAnalysis::QualityAnalysis()
{
}

QualityAnalysis::QualityAnalysis::~QualityAnalysis()
{
}

std::vector<double> QualityAnalysis::QualityAnalysis::convertPointToVector(Geometry::Point point, Geometry::Triangulation triangulation)
{
    double v1 = triangulation.UniqueNumbers[point.X()];
    double v2 = triangulation.UniqueNumbers[point.Y()];
    double v3 = triangulation.UniqueNumbers[point.Z()];
    return std::vector<double>{ v1, v2, v3 };
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
    cosTheta = clamp(cosTheta, -1.0, 1.0);
    return std::acos(cosTheta) * (180.0 / PI);
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleArea(Geometry::Triangle& triangle, Geometry::Triangulation triangulation)
{
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    std::vector<double> vertex1Double = convertPointToVector(vertex1, triangulation);
    std::vector<double> vertex2Double = convertPointToVector(vertex2, triangulation);
    std::vector<double> vertex3Double = convertPointToVector(vertex3, triangulation);

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

    std::vector<double> vertex1Double = convertPointToVector(vertex1, triangulation);
    std::vector<double> vertex2Double = convertPointToVector(vertex2, triangulation);
    std::vector<double> vertex3Double = convertPointToVector(vertex3, triangulation);

    double side1 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex1Double, vertex2Double);
    double side2 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex2Double, vertex3Double);
    double side3 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex3Double, vertex1Double);

    double longestEdge = std::max(std::max(side1, side2), side3);
    double shortestEdge = std::min(std::min(side1, side2), side3);

    double aspectRatio = longestEdge / shortestEdge;
    return aspectRatio;
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleInteriorAngle(Geometry::Triangle& triangle, Geometry::Triangulation triangulation) 
{
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    std::vector<double> vertex1Double = convertPointToVector(vertex1, triangulation);
    std::vector<double> vertex2Double = convertPointToVector(vertex2, triangulation);
    std::vector<double> vertex3Double = convertPointToVector(vertex3, triangulation);

    std::vector<double> AB{ vertex2Double[0] - vertex1Double[0], vertex2Double[1] - vertex1Double[1], vertex2Double[2] - vertex1Double[2] };
    std::vector<double> BC{ vertex3Double[0] - vertex2Double[0], vertex3Double[1] - vertex2Double[1], vertex3Double[2] - vertex2Double[2] };
    std::vector<double> CA{ vertex1Double[0] - vertex3Double[0], vertex1Double[1] - vertex3Double[1], vertex1Double[2] - vertex3Double[2] };

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

double QualityAnalysis::QualityAnalysis::triangleDensity(Geometry::Triangulation triangulation)
{
    double meshDensity = 0.0;

    double _surfaceArea = QualityAnalysis::QualityAnalysis::surfaceArea(triangulation);

    if (_surfaceArea != 0.0)
    {
        meshDensity = triangulation.Triangles.size() / _surfaceArea;
    }
    return meshDensity;
}

size_t QualityAnalysis::QualityAnalysis::numberOfTriangles(Geometry::Triangulation triangulation)
{
	return triangulation.Triangles.size();
}

size_t QualityAnalysis::QualityAnalysis::numberOfVertices(Geometry::Triangulation triangulation)
{
	std::vector<Geometry::Point> verticesList;
	for (auto triangle : triangulation.Triangles)
	{
		verticesList.push_back(triangle.P1());
		verticesList.push_back(triangle.P2());
		verticesList.push_back(triangle.P3());
	}
	std::set<Geometry::Point> verticesSet(verticesList.begin(), verticesList.end());
	return verticesSet.size();
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
