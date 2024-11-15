#include "ModifiedTriangle.h"

ModifiedTriangle::ModifiedTriangle() : Geometry::Triangle() 
{
    color[0] = 0.0;
    color[1] = 0.0;
    color[2] = 0.0;
}

ModifiedTriangle::ModifiedTriangle(
    const Geometry::Point& normal,
    const Geometry::Point& p1,
    const Geometry::Point& p2,
    const Geometry::Point& p3,
    const double color[3]
) : Geometry::Triangle(normal, p1, p2, p3) 
{
    for (int i = 0; i < 3; ++i) {
        this->color[i] = color[i];
    }
}


ModifiedTriangle::~ModifiedTriangle()
{
}
