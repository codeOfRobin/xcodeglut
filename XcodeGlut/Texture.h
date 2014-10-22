//
//  Texture.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 22/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__Texture__
#define __XcodeGlut__Texture__

#include <iostream>
#include <OpenGL/gl.h>
using namespace std;
class Texture
{
public:

    unsigned int textureID;
    
    Texture(void *data,int w, int h,int format);
    
    static Texture* loadBMP(const char* filename);
};
#endif /* defined(__XcodeGlut__Texture__) */
