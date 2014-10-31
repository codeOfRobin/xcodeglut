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


float venusRotate;

//bezier curve
GLfloat bezierCurve(float t, GLfloat P0,
                    GLfloat P1, GLfloat P2, GLfloat P3) {
    // Cubic bezier Curve
    GLfloat point = (pow((1-t), 3.0) * P0) +
    (3 * pow((1-t),2) * t * P1) +
    (3 * (1-t) * t * t * P2) +
    (pow(t, 3) * P3);
    return point;
}


vector3f randomSpherePoint()
{
    float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float theta = 2 * M_PI * u;
    float phi = acos(2*v-1);
    float x=-10+(10*sin(phi*cos(theta)));
    float y=50+(10 * sin(phi) * sin(theta));
    float z=10*cos(phi);
    
    return vector3f(x,y,z);
}

vector3f GetOGLPos(int x, int y)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    cout<<posX<<" "<<posY<<" "<<posZ<<" "<<endl;
    return vector3f(posX, posY, posZ);
}

void mouseClick(int button,int state,int x, int y)
{
    vector3f Coord=GetOGLPos(x, y);
}



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
    else if (keyBoard::key['f'])
    {
        venusRotate++;
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
    
    
    glBegin(GL_TRIANGLES);
    for (int i=0; i<400; i++)
    {
        
        vector3f point=randomSpherePoint();
        glVertex3f(point.x, point.y, point.z);
    }
    glEnd();
    
    //example for bezier
    vector3f start(-3.07,7.07,0);
    vector3f tan1(-10,0,12);
    vector3f tan2(-10,5,12);
    vector3f end(-10,10,0);
    
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(6.0);

    glBegin(GL_LINE_STRIP);
    int t = 30;
    for (int i = 0; i <= t; i++) {
        float pos = (float) i / (float) t;
        GLfloat x = bezierCurve( pos,start.x, tan1.x, tan2.x, end.x);
        GLfloat y = bezierCurve( pos,start.y, tan1.y, tan2.y, end.y);
        // In our case, the z should always be empty
        GLfloat z = bezierCurve(pos,start.z, tan1.z, tan2.z, end.z);
        
        vector3f result(x, y, z);
        glVertex3f(x, y, z);
    }
    glEnd();
    
    
    
    
    glBindTexture(GL_TEXTURE_2D, tex->textureID);

    glBegin(GL_QUADS);
    
    glColor3f(1, 1, 1);
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
    
    //globe
    glTranslatef(-10.0, 10.0, 0.0);
    glBindTexture(GL_TEXTURE_2D, tex2->textureID);
    gluQuadricTexture(quad,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(venusRotate, 0.0, 0.0, 1.0);
    
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
    glutMouseFunc(mouseClick);
    
    glutMotionFunc(mouse::move);
    glutPassiveMotionFunc(mouse::move);
    
    //Enable features
    //stuff about light COLOR MATERIAL allows GL_color to actually work
    GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);
    GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};

    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
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
    tex2=Texture::loadBMP("/Users/robinmalhotra2/Downloads/venusmap.bmp");
    
    Camera::position.y=1;
    
    object1.load("/Volumes/UNTITLED/Cities/tzfhx79fnc-castle/castle/castle.obj");

    glutMainLoop();
    return 0;
}

