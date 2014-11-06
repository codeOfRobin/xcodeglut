//
//  skyBoxTexture.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 06/11/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__skyBoxTexture__
#define __XcodeGlut__skyBoxTexture__

#include <iostream>
#include <GLUT/glut.h>
#include "Texture.h"
#endif /* defined(__XcodeGlut__skyBoxTexture__) */
using namespace std;
class skyBoxTexture
{
public:
    Texture* textures[6];
    void loadSkyBox(string directory, string filenames[6])
    {
        for (int i=0; i<6; i++)
        {
            string complete=directory+filenames[i];
            textures[i]=Texture::loadBMP(complete.c_str());
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    }
    
    
    void render();
};