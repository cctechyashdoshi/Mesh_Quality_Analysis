#include "RealPoint.h"

Geometry::RealPoint::RealPoint(): 
	mX(0), 
	mY(0), 
	mZ(0)
{
}

Geometry::RealPoint::RealPoint(double x, double y, double z): 
	mX(x), 
	mY(y), 
	mZ(z)
{
}

Geometry::RealPoint::~RealPoint()
{
}

double Geometry::RealPoint::X() const
{
	return mX;
}

double Geometry::RealPoint::Y() const
{
	return mY;
}

double Geometry::RealPoint::Z() const
{
	return mZ;
}