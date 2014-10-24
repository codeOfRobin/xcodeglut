//
//  loadObject.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 24/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "loadObject.h"
#include <ctype.h>
#include <fstream>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

using namespace std;

int loadObject::load(const char *filename)
{
    int facenum=0;
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open())
    {
    
        cout<<"not open";
        return 4;
    }
    else
    {

        string x;
        while (fin)
        {
            getline(fin, x, '\n');
            
            coord.push_back(x);
            
        }
        
        for (int i=0; i<coord.size(); i++)
        {
            if ((coord[i].c_str())[0]=='#')
            {
                continue;
            }
            else if ((coord[i].c_str())[0]=='v' && (coord[i].c_str())[1]==' ')
            {
                float tempx, tempy, tempz;
                sscanf(coord[i].c_str(), "v %f %f %f",&tempx,&tempy,&tempz);
                vertex.push_back(new coordinate(tempx, tempy,tempz));//shoould've used Vector3f here
                
            }
        else if ((coord[i].c_str())[0]=='v' && (coord[i].c_str())[1]=='n')
            {
                float tempx, tempy,tempz;
                sscanf(coord[i].c_str(), "vn %f %f %f", &tempx, &tempy, &tempz);
                normals.push_back(new coordinate(tempx,tempy,tempz));
            }
        else if ((coord[i].c_str())[0]=='v' && (coord[i].c_str())[1]=='t')
            {
                float tempx, tempy,tempz;
                sscanf(coord[i].c_str(), "vt %f %f %f", &tempx, &tempy, &tempz);
                textureVertex.push_back(new coordinate(tempx,tempy,tempz));
            }
            
        else if ((coord[i].c_str())[0]=='f')
            {
                facenum++;
                int a[12];
                if (count(coord[i].begin(), coord[i].end(), ' ')==5)
                {
                    if(sscanf(coord[i].c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8],&a[9],&a[10],&a[11])==12)
                    {
                        face* face1=new face(facenum,a[0],a[3],a[6],a[9]);
                        face1->setTextureVertices(a[1], a[4], a[7], a[10]);
                        face1->setNormals(a[2], a[5], a[8], a[11]);
                        faces.push_back(*face1);
                    }
                    
                    else if((coord[i].c_str())[4]=='/' && (coord[i].c_str())[3]=='/')
                    {
                        sscanf(coord[i].c_str(), "f %d//%d %d//%d %d//%d %d//%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7]);
                        face*face1=new face(facenum,a[0],a[2],a[4],a[6]);
                        face1->setNormals(a[1], a[3], a[5], a[7]);
                        faces.push_back(*face1);
                    }
                    
                    else if((coord[i].c_str())[4]=='/' && isdigit((coord[i].c_str())[5]))
                    {
                        sscanf(coord[i].c_str(), "f %d/%d %d/%d %d/%d %d/%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7]);
                        face*face1=new face(facenum,a[0],a[2],a[4],a[6]);
                        face1->setTextureVertices(a[1], a[3], a[5], a[7]);
                        faces.push_back(*face1);
                    }
                    else
                    {
                        sscanf(coord[i].c_str(), "f %d %d %d %d",&a[0],&a[1],&a[2],&a[3]);
                        face *face1=new face(facenum,a[0],a[1],a[2],a[3]);
                        faces.push_back(*face1);
                    }
                }
                else
                {
                    
                    
                    if (sscanf(coord[i].c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5],&a[6],&a[7],&a[8])==9)
                    {
                        face* face1=new face(facenum,a[0],a[3],a[6]);
                        face1->setTextureVertices(a[1], a[4], a[7]);
                        face1->setNormals(a[2], a[5], a[8]);
                        faces.push_back(*face1);
                    }
                    
                    else if((coord[i].c_str())[4]=='/' && (coord[i].c_str())[3]=='/')
                    {
                        sscanf(coord[i].c_str(), "f %d//%d %d//%d %d//%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5]);
                        face*face1=new face(facenum,a[0],a[2],a[4],a[6]);
                        face1->setNormals(a[1], a[3], a[5], a[7]);
                        faces.push_back(*face1);
                    }
                    
                    else if((coord[i].c_str())[4]=='/' && isdigit((coord[i].c_str())[5]))
                    {
                        sscanf(coord[i].c_str(), "f %d/%d %d/%d %d/%d",&a[0],&a[1],&a[2],&a[3],&a[4],&a[5]);
                        face*face1=new face(facenum,a[0],a[2],a[4]);
                        face1->setTextureVertices(a[1], a[3], a[5]);
                        faces.push_back(*face1);
                    }
                    else
                    {
                        sscanf(coord[i].c_str(), "f %d %d %d",&a[0],&a[1],&a[2]);
                        face *face1=new face(facenum,a[0],a[1],a[2]);
                        faces.push_back(*face1);
                    }

                    
                }
                
            }
            
        }
        coord.clear();
    }
    return 1;
}

void loadObject::draw()
{
    if (faces.at(0).four==true)
    {
        cout<<faces.size();
        glBegin(GL_QUADS);

        for (int i=0; i<faces.size(); i++)
        {
            glVertex3f(vertex.at(faces.at(i).faceVertices[0]-1)->x, vertex.at(faces.at(i).faceVertices[0]-1)->y, vertex.at(faces.at(i).faceVertices[0]-1)->z);
            glVertex3f(vertex.at(faces.at(i).faceVertices[1]-1)->x, vertex.at(faces.at(i).faceVertices[1]-1)->y, vertex.at(faces.at(i).faceVertices[1]-1)->z);
            glVertex3f(vertex.at(faces.at(i).faceVertices[2]-1)->x, vertex.at(faces.at(i).faceVertices[2]-1)->y, vertex.at(faces.at(i).faceVertices[2]-1)->z);
            glVertex3f(vertex.at(faces.at(i).faceVertices[3]-1)->x, vertex.at(faces.at(i).faceVertices[3]-1)->y, vertex.at(faces.at(i).faceVertices[3]-1)->z);

        }
        glEnd();

    }
    else
    {
        glBegin(GL_TRIANGLES);

    
        for (int i=0; i<faces.size(); i++)
        {
            glVertex3f(vertex.at(faces.at(i).faceVertices[0]-1)->x, vertex.at(faces.at(i).faceVertices[0]-1)->y, vertex.at(faces.at(i).faceVertices[0]-1)->z);
            glVertex3f(vertex.at(faces.at(i).faceVertices[1]-1)->x, vertex.at(faces.at(i).faceVertices[1]-1)->y, vertex.at(faces.at(i).faceVertices[1]-1)->z);
            glVertex3f(vertex.at(faces.at(i).faceVertices[2]-1)->x, vertex.at(faces.at(i).faceVertices[2]-1)->y, vertex.at(faces.at(i).faceVertices[2]-1)->z);
        }
        glEnd();


    }
}