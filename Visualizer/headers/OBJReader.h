#pragma once

#include <string> 
#include <vector>
#include <map>
#include "Reader.h"
#include "Triangulation.h"

using namespace std;
using namespace Geometry;

class OBJReader : public Reader
{

public:
	OBJReader();
	~OBJReader();

	void read(const string& fileName, Triangulation& tri);
	void helper(double xyz[3], vector<Point>&, map<double, int, OBJReader>&, Triangulation& triangulation);
	bool operator()(double a, double b) const;
};