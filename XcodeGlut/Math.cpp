//
//  Math.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 22/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "Math.h"
double Math::degreesToRadians(double degrees)
{
    return degrees*M_PI/180;
}

double Math::sind(double theta)
{
    return sin(degreesToRadians(theta));
}

double Math::cosd(double theta)
{
    return cos(degreesToRadians(theta));
}

double Math::fract(double f)
{
    return f-(long)f;
}