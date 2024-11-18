#pragma once
#include <vector>
#include "point.h"

namespace Geometry {

    class Triangle
    {
    public:
        Point normal;
        Point p1;
        Point p2;
        Point p3;

    public:
		Triangle();
        Triangle(Point normal, Point p1, Point p2, Point p3);
        ~Triangle();

        Point P1() const;
        Point P2() const;
        Point P3() const;
        Point Normal() const;

        std::vector<Point> Points() const;
    };
}
