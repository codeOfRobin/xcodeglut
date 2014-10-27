//
//  Vector3f.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 20/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__Vector3f__
#define __XcodeGlut__Vector3f__

#include <iostream>
class vector3f
{
public:
    float x=0.0f;
    float y=0.0f;
    float z=0.0f;
    
    vector3f(float xx, float yy, float zz)
    {
        x=xx;
        y=yy;
        z=zz;
    }
};
#endif /* defined(__XcodeGlut__Vector3f__) */
