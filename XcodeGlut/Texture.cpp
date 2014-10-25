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
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

}

Texture* Texture::loadBMP(const char *filename)
{
    FILE *fp;
    fp=fopen(filename, "r");
    if (!fp)
    {
        cout<<"filename could not be openead";
        fclose(fp);
        
        return NULL;
    }
    
    
    char* headerField=new char[2];
    fread(headerField, 2, sizeof(char), fp);
    if (strcmp(headerField, "BM"))
    {
        cout<<"file is not a bitmap";
        fclose(fp);
        
        return NULL;
    }
    
    
    delete [] headerField;//we've already checked if it's a BMP
    unsigned int bmpDataLocation,bmpWidth,bmpHeight;
    unsigned short numColorPlanes,bitsPerPixel;
    unsigned int compressionMethod,bmpDataSize;
    
    fseek(fp, 0x000a, SEEK_SET);
    fread(&bmpDataLocation, 1, sizeof(unsigned int), fp);
    
    fseek(fp, 0x0012, SEEK_SET);
    
    fread(&bmpWidth, 1, sizeof(unsigned int), fp);//http://en.wikipedia.org/wiki/BMP_file_format#Example_2
    fread(&bmpHeight, 1, sizeof(unsigned int), fp);
    fread(&numColorPlanes, 1, sizeof(unsigned short), fp);
    fread(&bitsPerPixel,1, sizeof(unsigned short), fp);
    fread(&compressionMethod, 1, sizeof(unsigned int), fp);
    fread(&bmpDataSize, 1, sizeof(unsigned int), fp);
    
    if (numColorPlanes!=1||bitsPerPixel!=24||compressionMethod!=0)//dealing with 24 bit BMPs
    {
        cout<<"file is not raw bmp24";
        fclose(fp);
        
        return NULL;
    }
    unsigned char *bmpData=new unsigned char[bmpDataSize];//unsigned char is a byte
    fseek(fp, bmpDataLocation, SEEK_SET);
    fread(bmpData, bmpDataSize, sizeof(unsigned char), fp);
    fclose(fp);

    return new Texture(bmpData, bmpWidth,bmpHeight,GL_RGB);
}