#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
}

BoundingBox::~BoundingBox()
{
}

double BoundingBox::minX(ModifiedTriangulation triangulation)
{
    double minX = std::numeric_limits<double>::infinity();

    for (ModifiedTriangle triangle : triangulation.mTriangles) {
        if (triangle.P1().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P1().X()];
        }
        if (triangle.P2().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P2().X()];
        }
        if (triangle.P3().X() < minX) {
            minX = triangulation.UniqueNumbers[triangle.P3().X()];
        }
    }
    return minX;
}

double BoundingBox::minY(ModifiedTriangulation triangulation)
{
    double minY = std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P2().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P2().Y()];
        }
        if (vertex.P3().Y() < minY) {
            minY = triangulation.UniqueNumbers[vertex.P3().Y()];
        }
    }
    return minY;
}

double BoundingBox::minZ(ModifiedTriangulation triangulation)
{
    double minZ = std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P2().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P2().Z()];
        }
        if (vertex.P3().Z() < minZ) {
            minZ = triangulation.UniqueNumbers[vertex.P3().Z()];
        }
    }
    return minZ;
}

double BoundingBox::maxX(ModifiedTriangulation triangulation)
{
    double maxX = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
        if (vertex.P2().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
        if (vertex.P3().X() > maxX) {
            maxX = triangulation.UniqueNumbers[vertex.P1().X()];
        }
    }
    return maxX;
}

double BoundingBox::maxY(ModifiedTriangulation triangulation)
{
    double maxY = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P2().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
        if (vertex.P3().Y() > maxY) {
            maxY = triangulation.UniqueNumbers[vertex.P1().Y()];
        }
    }
    return maxY;
}

double BoundingBox::maxZ(ModifiedTriangulation triangulation)
{
    double maxZ = -std::numeric_limits<double>::infinity();

    for (auto vertex : triangulation.mTriangles) {
        if (vertex.P1().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P2().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
        if (vertex.P3().Z() > maxZ) {
            maxZ = triangulation.UniqueNumbers[vertex.P1().Z()];
        }
    }
    return maxZ;
}

void BoundingBox::createBoundingBoxTriangulation(ModifiedTriangulation triangulation)
{
    ModifiedTriangulation modifiedTriangulation;

    modifiedTriangulation._minX = minX(triangulation);
    modifiedTriangulation._minY = minY(triangulation);
    modifiedTriangulation._minZ = minZ(triangulation);
    modifiedTriangulation._maxX = maxX(triangulation);
    modifiedTriangulation._maxY = maxY(triangulation);
    modifiedTriangulation._maxZ = maxZ(triangulation);

    std::vector<double> p1 = { modifiedTriangulation._minX, modifiedTriangulation._minY, modifiedTriangulation._minZ };
    std::vector<double> p2 = { modifiedTriangulation._maxX, modifiedTriangulation._minY, modifiedTriangulation._minZ };
    std::vector<double> p3 = { modifiedTriangulation._maxX, modifiedTriangulation._maxY, modifiedTriangulation._minZ };
    std::vector<double> p4 = { modifiedTriangulation._minX, modifiedTriangulation._maxY, modifiedTriangulation._minZ };
    std::vector<double> p5 = { modifiedTriangulation._minX, modifiedTriangulation._minY, modifiedTriangulation._maxZ };
    std::vector<double> p6 = { modifiedTriangulation._maxX, modifiedTriangulation._minY, modifiedTriangulation._maxZ };
    std::vector<double> p7 = { modifiedTriangulation._maxX, modifiedTriangulation._maxY, modifiedTriangulation._maxZ };
    std::vector<double> p8 = { modifiedTriangulation._minX, modifiedTriangulation._maxY, modifiedTriangulation._maxZ };

    boundingBoxTriangulation.push_back({ p1, p2, p3 });
    boundingBoxTriangulation.push_back({ p1, p4, p3 });
    boundingBoxTriangulation.push_back({ p1, p4, p8 });
    boundingBoxTriangulation.push_back({ p1, p5, p8 });
    boundingBoxTriangulation.push_back({ p1, p2, p6 });
    boundingBoxTriangulation.push_back({ p1, p5, p6 });
    boundingBoxTriangulation.push_back({ p2, p7, p6 });
    boundingBoxTriangulation.push_back({ p2, p7, p3 });
    boundingBoxTriangulation.push_back({ p5, p6, p7 });
    boundingBoxTriangulation.push_back({ p5, p8, p7 });
    boundingBoxTriangulation.push_back({ p3, p4, p8 });
    boundingBoxTriangulation.push_back({ p3, p7, p8 });
}
