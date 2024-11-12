#include "QualityAnalysis.h"
#include "Triangulation.h"
#include <cmath>
#include <algorithm>

#define M_PI 3.14159265358979323846

QualityAnalysis::QualityAnalysis::QualityAnalysis()
{
}

QualityAnalysis::QualityAnalysis::~QualityAnalysis()
{
}

double QualityAnalysis::QualityAnalysis::clamp(double value, double min, double max)
{
    return (value < min) ? min : (value > max) ? max : value;
}

Geometry::Point QualityAnalysis::QualityAnalysis::negativePoint(const Geometry::Point& point)
{
    return Geometry::Point(-point.X(), -point.Y(), -point.Z());
}

double QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(const Geometry::Point& firstPoint, const Geometry::Point& secondPoint)
{
    // Calculate the distance using Euclidean distance formula
    double dx = firstPoint.X() - secondPoint.X();
    double dy = firstPoint.Y() - secondPoint.Y();
    double dz = firstPoint.Z() - secondPoint.Z();

    return std::sqrt(dx * dx + dy * dy + dz * dz);
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

	Geometry::Point vertex1New(vertex11, vertex12, vertex13);
	Geometry::Point vertex2New(vertex21, vertex22, vertex23);
	Geometry::Point vertex3New(vertex31, vertex32, vertex33);

    double side1 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex1New, vertex2New);
    double side2 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex2New, vertex3New);
    double side3 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex3New, vertex1New);

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

    Geometry::Point vertex1New(vertex11, vertex12, vertex13);
    Geometry::Point vertex2New(vertex21, vertex22, vertex23);
    Geometry::Point vertex3New(vertex31, vertex32, vertex33);

    double side1 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex1New, vertex2New);
    double side2 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex2New, vertex3New);
    double side3 = QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(vertex3New, vertex1New);

    double longestEdge = std::max(std::max(side1, side2), side3);
    double shortestEdge = std::min(std::min(side1, side2), side3);

    double aspectRatio = longestEdge / shortestEdge;
    return aspectRatio;
}

double QualityAnalysis::QualityAnalysis::calculateAngleBetweenVectors(const Geometry::Point& v1, const Geometry::Point& v2) {
    double dotProduct = v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
    double magnitudeV1 = std::sqrt(v1.X() * v1.X() + v1.Y() * v1.Y() + v1.Z() * v1.Z());
    double magnitudeV2 = std::sqrt(v2.X() * v2.X() + v2.Y() * v2.Y() + v2.Z() * v2.Z());
    double cosTheta = dotProduct / (magnitudeV1 * magnitudeV2);
    cosTheta = clamp(cosTheta, -1.0, 1.0); // Ensure the value is within the valid range for acos
    return std::acos(cosTheta) * (180.0 / M_PI); // Convert to degrees
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

    Geometry::Point vertex1New(vertex11, vertex12, vertex13);
    Geometry::Point vertex2New(vertex21, vertex22, vertex23);
    Geometry::Point vertex3New(vertex31, vertex32, vertex33);

    Geometry::Point AB(vertex2New.X() - vertex1New.X(), vertex2New.Y() - vertex1New.Y(), vertex2New.Z() - vertex1New.Z());
    Geometry::Point BC(vertex3New.X() - vertex2New.X(), vertex3New.Y() - vertex2New.Y(), vertex3New.Z() - vertex2New.Z());
    Geometry::Point CA(vertex1New.X() - vertex3New.X(), vertex1New.Y() - vertex3New.Y(), vertex1New.Z() - vertex3New.Z());

    double angleA = calculateAngleBetweenVectors(AB, negativePoint(CA));
    double angleB = calculateAngleBetweenVectors(AB, BC);
    double angleC = calculateAngleBetweenVectors(BC, negativePoint(CA));

    double averageAngle = (angleA + angleB + angleC) / 3.0;

    return averageAngle;
}

double QualityAnalysis::QualityAnalysis::surfaceArea(Geometry::Triangulation triangulation)
{
	double totalArea = 0;
	for (auto triangle : triangulation.Triangles)
	{
		totalArea += QualityAnalysis::QualityAnalysis::calculateSingleTriangleArea(triangle, triangulation);
	}
	return totalArea;
}

int QualityAnalysis::QualityAnalysis::numberOfTriangles(Geometry::Triangulation triangulation)
{
	return triangulation.Triangles.size();
}

int QualityAnalysis::QualityAnalysis::numberOfVertices(Geometry::Triangulation triangulation)
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
	double minX = 0;
	double maxX = 0;
	for (auto vertex : triangulation.UniqueNumbers)
	{
		minX = std::min(minX, vertex.X());
		maxX = std::max(maxX, vertex.X());
	}
	return maxX - minX;
}