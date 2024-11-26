#include <vector>
#include "Triangle.h"

using namespace Geometry;

Point Geometry::Triangle::P1() const
{
    return p1;
}

Point Geometry::Triangle::P2() const
{ 
    return p2;
}

Point Geometry::Triangle::P3() const
{
    return p3;
}

Triangle::Triangle(Geometry::Point normal, Geometry::Point p1, Geometry::Point p2, Geometry::Point p3):
    normal(normal),
    p1(p1),
    p2(p2),
    p3(p3),
    color({ 0.0,0.0,0.0,1.0 })
{
}

std::vector<Point> Triangle::Points() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}
    
Point Geometry::Triangle::Normal() const
{
    return normal;
}

std::vector<float> Triangle::Color() const
{
    return color;
}

void Triangle::setColor(float r, float g, float b, float a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}
