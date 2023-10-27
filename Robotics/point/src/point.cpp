// The point class implementation
#include "point.h"
#include <cmath>
#include <iostream>
#include <point.h>


Point::Point(int xvar, int yvar)
{
    xvar_ = xvar;
    yvar_ = yvar;
}

int Point::getX(void) const
{
    return xvar_;
}

int Point::getY(void) const
{
    return yvar_;
}

void Point::setX(int xvar)
{
    xvar_ = xvar;
}


void Point::setY(int yvar)
{
yvar_ = yvar;
}
void Point::setXY(int xvar, int yvar)
{
    xvar_ = xvar;
    yvar_ = yvar;
}

double Point::getMagnitude(void) const
{
    return sqrt(xvar_*xvar_ + yvar_*yvar_);
}

double Point::getArgument(void) const
{
    return atan( yvar_ / xvar_);
}

void Point::print(void) const
{
    std::cout << "(" << xvar_ << "," << yvar_ << ")";
}