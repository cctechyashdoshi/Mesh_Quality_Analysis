#include <vector>
#include "Triangle.h"

using namespace std;
using namespace Geometry;

Point Triangle::P1() const
{
    return p1;
}

Point Triangle::P2() const
{ 
    return p2;
}

Point Triangle::P3() const
{
    return p3;
}

Triangle::Triangle(Point normal, Point p1, Point p2, Point p3):
    normal(normal),
    p1(p1),
    p2(p2),
    p3(p3),
    color({ 0.0,0.0,0.0,1.0 })
{
}

vector<Point> Triangle::Points() const
{
    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    return points;
}
    
Point Triangle::Normal() const
{
    return normal;
}

vector<float> Triangle::Color() const
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
