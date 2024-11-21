#pragma once

#include "Triangulation.h"
#include "Reader.h"
#include "Point.h"

class OBJReader : public Reader
{
public:
	OBJReader();
	~OBJReader();

	void read(const std::string& fileName, Triangulation& tri);
	bool operator()(double a, double b) const;
	Geometry::Point vectorReader(const QStringList& lineList, std::map<double, int, OBJReader>& uniqueMap, Triangulation& tri);
};
