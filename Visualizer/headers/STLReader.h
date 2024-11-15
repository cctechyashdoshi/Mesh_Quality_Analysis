#pragma once
#include <string> 
#include "ModifiedTriangulation.h"
#include "Reader.h"

using namespace Geometry;

// STLReader class inherits from Reader to specifically handle STL file reading
class STLReader : public Reader
{
public:
    STLReader();
    ~STLReader();

    // Reads the STL file specified by fileName and stores the triangulation data
    void read(const std::string& fileName, ModifiedTriangulation& triangulation);

    bool operator()(double a, double b) const;
};
