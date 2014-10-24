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
using namespace std;
class loadObject
{public:
    
    int load(const char* filename);
    vector<string> coord;

    void draw();
    struct coordinate
    {
        float x,y,z;
        coordinate(float a, float b, float c):x(a),y(b),z(c){};
    };
    struct face
    {
        int facenum;
        bool four;
        int faceVertices[4];
        int normals[4];
        int textureVertices[4];

        face(int facen, int f1, int f2, int f3):facenum(facen)
        {
            faceVertices[0]=f1;
            faceVertices[1]=f2;
            faceVertices[2]=f3;
            textureVertices[0]=-42;//sentinelValue
            normals[0]=-42;
            four=false;
        }
        face(int facen, int f1, int f2, int f3, int f4):facenum(facen)
        {
            faceVertices[0]=f1;
            faceVertices[1]=f2;
            faceVertices[2]=f3;
            faceVertices[3]=f4;
            textureVertices[0]=-42;
            normals[0]=-42;
            four=true;
        }
        
        void setTextureVertices(int t1, int t2, int t3, int t4)
        {
            textureVertices[0]=t1;
            textureVertices[1]=t2;
            textureVertices[2]=t3;
            textureVertices[3]=t4;
        }
        
        void setTextureVertices(int t1, int t2, int t3)
        {
            textureVertices[0]=t1;
            textureVertices[1]=t2;
            textureVertices[2]=t3;
        }
        
        void setNormals(int n1, int n2, int n3, int n4)
        {
            normals[0]=n1;
            normals[1]=n2;
            normals[2]=n3;
            normals[3]=n4;
        }
        void setNormals(int n1, int n2, int n3)
        {
            normals[0]=n1;
            normals[1]=n2;
            normals[2]=n3;
        }
        
    
        
        
    };
    
    vector<coordinate*> vertex;
    vector<face> faces;
    vector<coordinate*> normals;
    vector<coordinate*> textureVertex;
};

#endif /* defined(__XcodeGlut__loadObject__) */
