//
//  loadObject.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 24/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__loadObject__
#define __XcodeGlut__loadObject__

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
class loadObject
{public:
    
    int load(const char* filename);
    struct coordinate
    {
        float x,y,z;
        coordinate(float a, float b, float c):x(a),y(b),z(c){};
    };
    struct face
    {
        int facenum;
        bool four;
        int faces[4];
        

        face(int facen, int f1, int f2, int f3):facenum(facen)
        {
            faces[0]=f1;
            faces[1]=f2;
            faces[2]=f3;
            four=false;
        }
        face(int facen, int f1, int f2, int f3, int f4):facenum(facen)
        {
            faces[0]=f1;
            faces[1]=f2;
            faces[2]=f3;
            faces[3]=f4;
            four=true;
        }
    };
};

#endif /* defined(__XcodeGlut__loadObject__) */
