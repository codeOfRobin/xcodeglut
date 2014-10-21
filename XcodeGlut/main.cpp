//
//  main.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 20/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include <iostream>
#include <OpenGL/OpenGL.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <GLUT/GLUT.h>
#include "Math.h"
#include "Vector3f.h"
#include "mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"

vector3f CAMERA_ROTATION;
vector3f CAMERA_POSITION;
using namespace std;
const int WINDOW_HEIGHT=720;
const int WINDOW_WIDTH=1200;
const char* WINDOW_TITLE="something";

const float WALKING_SPEED=0.01;
float LAST_TIME;
float CURRENT_TIME;
float DELTA_TIME;
const float MAX_TILT=85;
int MOUSE_LAST_X, MOUSE_LAST_Y;
int MOUSE_CURRENT_X, MOUSE_CURRENT_Y;
int MOUSE_DELTA_X, MOUSE_DELTA_Y;
const float MOUSE_SENSITIVITY=0.1;

void preProcessEvents()
{
    CURRENT_TIME=(float)glutGet(GLUT_ELAPSED_TIME);
    DELTA_TIME=CURRENT_TIME-LAST_TIME;
    LAST_TIME=CURRENT_TIME;
    

    mouse::update();
    //mouse processing
    Camera::rotation.y+=(float)mouse::deltaX*MOUSE_SENSITIVITY;
    Camera::rotation.x+=(float)mouse::deltaY*MOUSE_SENSITIVITY;
    
    if (Camera::rotation.x>MAX_TILT)
    {
        Camera::rotation.x=MAX_TILT;
    }
    else if (Camera::rotation.x<-1*MAX_TILT)
    {
        Camera::rotation.x=-1*MAX_TILT;
    }
    if (keyBoard::key['w'])
    {
        Camera::position.x-=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotation.y);
        Camera::position.z-=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotation.y);
    }
    else if (keyBoard::key['s'])
    {
        Camera::position.x-=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotation.y+180);
        Camera::position.z-=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotation.y+180);
    }
    else if (keyBoard::key['a'])
    {
        Camera::position.x+=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotation.y+270);
        Camera::position.z+=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotation.y+270);
    }
    else if (keyBoard::key['d'])
    {
        Camera::position.x+=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotation.y+90);
        Camera::position.z+=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotation.y+90);
    }
    else if (keyBoard::key[' '])
    {
    
    }
    
}
void reshape(int w, int h)
{
    float aspectRatio;
    if (h==0)
    {
        h=1;
    }
    aspectRatio=float(w)/float(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w ,h);
    gluPerspective(45, aspectRatio, 0.01, 100000000);
    glMatrixMode(GL_MODELVIEW);
}


void display()
{
    preProcessEvents();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glRotatef(Camera::rotation.x, 1, 0, 0);
    glRotatef(Camera::rotation.y, 0, 1, 0);
    glRotatef(Camera::rotation.z, 0, 0, 1);
    glTranslatef(-Camera::position.x, -Camera::position.y, -Camera::position.z);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1.0f,-3);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 1.0f,-3);
    glColor3f(0, 0, 1);
    glVertex3f(1.0f, -1.0f,-3);
    glEnd();
    
    glutSwapBuffers();
}

int main(int argc,char ** argv)
{
    
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow(WINDOW_TITLE);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    
    glutKeyboardFunc(keyBoard::keyDown);
    glutKeyboardUpFunc(keyBoard::keyUp);
    
    glutMotionFunc(mouse::move);
    glutPassiveMotionFunc(mouse::move);
    
    Texture* texture=Texture::loadBMP("something.bmp");
    glutMainLoop();
    return 0;
}

