//
//  Math.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 22/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__Math__
#define __XcodeGlut__Math__

#include <iostream>
#include<cmath>
class Math
{
public:
   static double degreesToRadians(double degrees);
    static double sind(double theta);
    static double cosd(double theta);
    static double fract(double f);
};
#endif /* defined(__XcodeGlut__Math__) */
