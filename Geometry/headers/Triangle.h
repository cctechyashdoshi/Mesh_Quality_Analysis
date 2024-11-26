#pragma once
#include <vector>
#include "point.h"

namespace Geometry {

    class Triangle
    {
        Point normal;
        Point p1;
        Point p2;
        Point p3;
        std::vector<float> color;

    public:
        Triangle(Point normal, Point p1, Point p2, Point p3);

        Point P1() const;
        Point P2() const;
        Point P3() const;
        Point Normal() const;

        std::vector<Point> Points() const;
        std::vector<float> Color() const;
        void setColor(float r, float g, float b, float a);
    };
}
