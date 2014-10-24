//
//  loadObject.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 24/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "loadObject.h"
using namespace std;
int loadObject::load(const char *filename)
{
    vector<string*> coord;
    vector<coordinate*> vertex;
    vector<face> faces;
    vector<coordinate*> normals;
    FILE* fin;
    fin=fopen(filename, "r");
    if(fin==NULL)
    {
    
        cout<<"not open";
        return 4;
    }
    else
    {
        string x;
        while (!feof(fin))
        {
            
            fread(&x, 256, sizeof(char), fin);
            coord.push_back(&x);
            
        }
        
        for (int i=0; i<coord.size(); i++)
        {
            if (coord[i][0]=="#")
            {
                continue;
            }
            else if (coord[i][0]=="v" && coord[i][1]==" ")
            {
                float tempx, tempy, tempz;
                sscanf(coord[i]->c_str(), "v %f %f %f",&tempx,&tempy,&tempz);
                vertex.push_back(new coordinate(tempx, tempy,tempz));//shoould've used Vector3f here
                
            }
        else if (coord[i][0]=="v" && coord[i][1]=="n")
            {
                float tempx, tempy,tempz;
                sscanf(coord[i]->c_str(), "vn %f %f %f", &tempx, &tempy, &tempz);
                normals.push_back(new coordinate(tempx,tempy,tempz));
            }
            
        else if (coord[i][0]=="f")
            {
                bool isTexture, isNormal;
                
            }
            
        }
        for (int i; i<coord.size(); i++)
        {
            delete coord[i];
        }
    }
    return 1;
}