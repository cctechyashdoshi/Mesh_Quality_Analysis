#pragma once
#include <string> 
#include "ModifiedTriangulation.h"
#include "Reader.h"

using namespace Geometry;

class STLReader : public Reader
{

    bool operator()(double a, double b) const;
public:
    STLReader();
    ~STLReader();

    void read(const std::string& fileName, ModifiedTriangulation& triangulation);

};
