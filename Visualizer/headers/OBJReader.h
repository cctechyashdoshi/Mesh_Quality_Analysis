#pragma once

#include <string> 
#include "ModifiedTriangulation.h"
#include <vector>
#include "Reader.h"

using namespace Geometry;

class OBJReader : public Reader
{
public:
	OBJReader();
	~OBJReader();

	void read(const std::string& fileName, ModifiedTriangulation& tri);
	void helper(double xyz[3],std::vector<Point>&, std::map<double, int, OBJReader>&, ModifiedTriangulation& triangulation);
	bool operator()(double a, double b) const;
};
