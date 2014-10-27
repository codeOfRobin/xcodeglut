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
#include <stdio.h>
#include "Math.h"
#include "Vector3f.h"
#include "mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"
#include "loadObject.h"

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

loadObject object1;

GLUquadric *quad;

Texture* tex;
Texture* tex2;
void preProcessEvents()
{
    CURRENT_TIME=(float)glutGet(GLUT_ELAPSED_TIME);
    DELTA_TIME=CURRENT_TIME-LAST_TIME;
    LAST_TIME=CURRENT_TIME;
    

    mouse::update();
    //mouse processing
    Camera::rotationAngles.y+=(float)mouse::deltaX*MOUSE_SENSITIVITY;
    Camera::rotationAngles.x-=(float)mouse::deltaY*MOUSE_SENSITIVITY;
    
    if (Camera::rotationAngles.x>MAX_TILT)
    {
        Camera::rotationAngles.x=MAX_TILT;
    }
    else if (Camera::rotationAngles.x<-1*MAX_TILT)
    {
        Camera::rotationAngles.x=-1*MAX_TILT;
    }
    if (keyBoard::key['w'])
    {
        Camera::position.z-=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotationAngles.y);
        Camera::position.x-=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotationAngles.y);
    }
    else if (keyBoard::key['s'])
    {
        Camera::position.z+=WALKING_SPEED*DELTA_TIME*Math::sind(Camera::rotationAngles.y);
        Camera::position.x+=WALKING_SPEED*DELTA_TIME*Math::cosd(Camera::rotationAngles.y);
    }
    else if (keyBoard::key['a'])
    {
        Camera::rotationAngles.y-=WALKING_SPEED*DELTA_TIME*3;
    }
    else if (keyBoard::key['d'])
    {
        Camera::rotationAngles.y+=WALKING_SPEED*DELTA_TIME*3;
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
    gluLookAt(Camera::position.x, Camera::position.y, Camera::position.z,
              Camera::position.x+Math::sind(Camera::rotationAngles.x)*Math::cosd(Camera::rotationAngles.y),
              Camera::position.y+Math::cosd(Camera::rotationAngles.x),
              Camera::position.z+Math::sind(Camera::rotationAngles.x)*Math::sind(Camera::rotationAngles.y),
              0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex3f(-1, 0,-3);
    glColor3f(0, 1, 0);
    glVertex3f(0.0f, 2.0f,-3);
    glColor3f(0, 0, 1);
    glVertex3f(1.0f, 0.0f,-3);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, tex->textureID);
    
    glBegin(GL_QUADS);
    
    glColor3f(1, 1, 1);
    cout<<Camera::rotationAngles.x;
    glTexCoord2f(100, 100);
    glVertex3f(100,0,100);
    
    glTexCoord2f(-100, 100);
    glVertex3f(-100,0,100);
    
    glTexCoord2f(-100,-100);
    glVertex3f(-100,0,-100);
    
    glTexCoord2f(100,-100);
    glVertex3f(100,0,-100);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    object1.draw();
    
    glTranslatef(-10.0, 10.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex2->textureID);
    gluQuadricTexture(quad,1);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(CURRENT_TIME, 0.0, 0.0, 1.0);
    
    gluSphere(quad,10,20,20);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);

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
    
    //Enable features
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //setup content
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glGetError();
    tex=Texture::loadBMP("/Users/robinmalhotra2/Downloads/tiles.bmp");
    if (!tex)
    {
        return 1;
    }
    
    quad=gluNewQuadric();
    tex2=Texture::loadBMP("/Users/robinmalhotra2/Downloads/earthmap1k.bmp");
    
    Camera::position.y=1;
    
    object1.load("/Volumes/UNTITLED/Cities/tzfhx79fnc-castle/castle/castle.obj");

    glutMainLoop();
    return 0;
}

