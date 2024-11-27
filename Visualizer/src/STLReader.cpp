#include "STLReader.h"
#include "Point.h"
#include "Reader.h"
#include "QualityAnalysis.h"
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

#define TOLERANCE 0.0000001

using namespace std;
using namespace Geometry;

STLReader::STLReader()
{
}

STLReader::~STLReader()
{
}

bool STLReader::operator()(double a, double b) const
{
    return fabs(a - b) > TOLERANCE ? a < b : false;
}

void STLReader::read(const string& fileName, Triangulation& triangulation)
{
    map<double, int, STLReader> uniqueValueMap;
    double xyz[3];
    vector<int> pointIndices; 

    ifstream infile(fileName);
    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            stringstream ss(line);
            string word;

            while (ss >> word)
            {
                if (word == "vertex" || word == "normal")
                {
                    ss >> xyz[0] >> xyz[1] >> xyz[2];

                    for (int i = 0; i < 3; i++)
                    {
                        auto pair = uniqueValueMap.find(xyz[i]);
                        if (pair == uniqueValueMap.end())
                        {
                            triangulation.UniqueNumbers.push_back(xyz[i]);
                            uniqueValueMap[xyz[i]] = triangulation.UniqueNumbers.size() - 1;
                            pointIndices.push_back(triangulation.UniqueNumbers.size() - 1);
                        }
                        else
                        {
                            pointIndices.push_back(pair->second);
                        }
                    }
                }

                if (pointIndices.size() == 12)
                {
                    Point normal = Point(pointIndices[0], pointIndices[1], pointIndices[2]);
                    Point p1 = Point(pointIndices[3], pointIndices[4], pointIndices[5]);
                    Point p2 = Point(pointIndices[6], pointIndices[7], pointIndices[8]);
                    Point p3 = Point(pointIndices[9], pointIndices[10], pointIndices[11]);
                    Triangle t(normal, p1, p2, p3);
                    t.setColor(1.0, 0.0, 0.0, 1.0);
                    triangulation.Triangles.push_back(t);

                    pointIndices.clear();
                }
            }
        }
    }
}
