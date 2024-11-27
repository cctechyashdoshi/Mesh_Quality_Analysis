#pragma once
#include <string> 
#include "Triangulation.h"
#include "Reader.h"

using namespace std;
using namespace Geometry;

class STLReader : public Reader
{
public:
    STLReader();
    ~STLReader();

    void read(const string& fileName, Triangulation& triangulation);
    bool operator()(double a, double b) const;
};
