#pragma once
#include<string>
#include "Triangulation.h"

using namespace std;
using namespace Geometry;

class Reader
{
	virtual void read(const string& fileName, Triangulation& triangulation) = 0;
};
