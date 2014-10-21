//
//  Texture.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 22/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "Texture.h"

Texture::Texture(void *data, int w, int h, int format)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    

}

Texture* Texture::loadBMP(const char *filename)
{
    FILE *fp;
    fp=fopen(filename, "r");
    Texture *texture;
    if (!fp)
    {
        cout<<"filename could not be openead";
        fclose(fp);
        
    }
    return texture;
}