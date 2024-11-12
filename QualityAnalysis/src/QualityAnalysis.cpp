#include "QualityAnalysis.h"
#include <cmath>

double QualityAnalysis::QualityAnalysis::calculateDistanceBetweenPoints(const Geometry::Point& firstPoint, const Geometry::Point& secondPoint)
{
    // Calculate the distance using Euclidean distance formula
    double dx = firstPoint.X() - secondPoint.X();
    double dy = firstPoint.Y() - secondPoint.Y();
    double dz = firstPoint.Z() - secondPoint.Z();

    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

double QualityAnalysis::QualityAnalysis::calculateSingleTriangleArea(Geometry::Triangle& triangle)
{
    Geometry::Point vertex1 = triangle.P1();
    Geometry::Point vertex2 = triangle.P2();
    Geometry::Point vertex3 = triangle.P3();

    Shapes3D::Point3D vertex1 = triangulation.uniquePoints()[index1];
    Shapes3D::Point3D vertex2 = triangulation.uniquePoints()[index2];
    Shapes3D::Point3D vertex3 = triangulation.uniquePoints()[index3];

    double side1 = ;
    double side2 = Shapes3D::Point3D::distanceBetweenPoints(vertex2, vertex3);
    double side3 = Shapes3D::Point3D::distanceBetweenPoints(vertex3, vertex1);

    double semiPerimeter = (side1 + side2 + side3) / 2;
    double area = sqrt(semiPerimeter * (semiPerimeter - side1) * (semiPerimeter - side2) * (semiPerimeter - side3));

    return area;
}

QualityAnalysis::QualityAnalysis::QualityAnalysis()
{
}

QualityAnalysis::QualityAnalysis::~QualityAnalysis()
{
}
