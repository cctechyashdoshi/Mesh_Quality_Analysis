#pragma once

#include "Triangulation.h"

using namespace Geometry;	
namespace QualityAnalysis
{
	class QualityAnalysis
	{
		std::vector<std::vector<Triangle, int>> angleInformation(Triangulation& triangulation, std::vector<int> angleAnalysis);
		std::vector<std::vector<Triangle, int>> lengthInformation(Triangulation& triangulation, std::vector<int> lengthAnalysis);
	};
}
