#include "ModifiedTriangulation.h"

using namespace MeshOperations;

ModifiedTriangulation::ModifiedTriangulation()
{
}

ModifiedTriangulation::~ModifiedTriangulation()
{
}

std::vector<double> ModifiedTriangulation::convertIndicesToDoublePoints(Geometry::Point p)
{
    std::vector<double> doubledPoint;

    doubledPoint[0] = UniqueNumbers[p.X()];
    doubledPoint[0] = UniqueNumbers[p.Y()];
    doubledPoint[0] = UniqueNumbers[p.Z()];

    return doubledPoint;
}
