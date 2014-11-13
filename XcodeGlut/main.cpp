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
#include <GLUI/GLUI.h>
#include "Math.h"
#include "Vector3f.h"
#include "mouse.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Texture.h"
#include "loadObject.h"
#include "Monopoly.h"
#include "skyBoxTexture.h"
#include "drawtext.h"
skyBoxTexture skybox;
dtx_font *font;

Monopoly game;

//bools for display
bool menu, globe=true, city;

//text
struct dtx_font *font2;
string menuText[3]={"      Welcome to \nStar Wars Monopoly\n","\n             New Game\n","\n                 Exit\n"};

//dice stuff
int facevalue;
GLfloat diceRotate=0;
int i = 0;

// Picking Stuff //
#define RENDER					1
#define SELECT					2
#define BUFSIZE 1024
GLuint selectBuf[BUFSIZE];
GLint hits;
int mode = RENDER;
int cursorX,cursorY;
bool isWithinCoordinates(int upperLeftX,int upperLeftY,int lowerRightX, int lowerRightY)
{
    if (menu && cursorX>upperLeftX && cursorY>upperLeftY && cursorX<lowerRightX &&cursorY<lowerRightY)
    {
        return true;
    }
    return false;
}

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




int w,h, border=6;
loadObject object1,object2;


GLUquadric *quad;

Texture* tex;
Texture* tex2;
int mainWindow;

float venusRotate;
vector<vector3f>cityVertices;



//locations at distance

vector<int> locationsFromTraversal;
void locationsAtDistance(int location, int distance)
{
    if (distance==0)
    {
        locationsFromTraversal.push_back(location);
    }
    else
    {
        for (int i=0; i<game.locations.size(); i++)
        {
            if (game.graph[location][i]==1)
            {
                locationsAtDistance(i, distance-1);
                
            }
            
        }
    }
}


//player actions

void payRent()
{
    cout<<"paid rent";
}

int getDiceFace()
{
    srand((int)time(NULL));
    int facevalue = (rand() % 6) + 1;
    return facevalue;
}

void reportCheating(int id)
{
    cout<<"repos";
}

//bezier curve

GLfloat bezierCurve(float t, GLfloat P0,
                    GLfloat c1, GLfloat c2 ,GLfloat P1) {

    GLfloat point=pow(1-t, 3)*P0+ 3*t*pow(1-t, 2)*c1+ 3*t*t*(1-t)*c2+pow(t, 3)*P1;
    return point;
}



vector3f randomSpherePoint()
{
    float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float v = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float theta = 2 * M_PI * u;
    float phi = acos(2*v-1);
    float x=(10*sin(phi)*cos(theta));
    float y=(10 * sin(phi) * sin(theta));
    float z=10*cos(phi);
    return vector3f(x, y, z);
}


void drawRandomSpherePoints()
{
    for (int i=0; i<40; i++)
    {
        glPushMatrix();
        
        vector3f point=cityVertices.at(i);
        glTranslatef(point.x, point.y, point.z);
        glPushName(i);
        glutSolidSphere(1.0, 10, 10);
        glPopName();
        glPopMatrix();
    }
    
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
    return vector3f(posX, posY, posZ);
}

void mouseClick(int button,int state,int x, int y)
{
    
	if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
		return;
    
	cursorX = x;
	cursorY = y;
    if (menu && isWithinCoordinates(831, 295, 1006, 320) )
    {
        menu=false;
        globe=true;
        city=true;
    }
    else if (menu && isWithinCoordinates(880, 342, 962, 384))
    {
        exit(8);
    }
    else
    {
	mode = SELECT;

    }
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
    else if (keyBoard::key[27])
    {
        menu=true;
        globe=false;
        city=false;
    }
    else if (keyBoard::key['n'])
    {
        menu=false;
        city=true;
        globe=true;
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
    GLUI_Master.auto_set_viewport();
    gluPerspective(45, aspectRatio, 0.01, 100000000);
    glMatrixMode(GL_MODELVIEW);
}


//---------------
// Picking Stuff
//---------------


void startPicking() {
    
	GLint viewport[4];
	float ratio;
    
	glSelectBuffer(BUFSIZE,selectBuf);
    
	glGetIntegerv(GL_VIEWPORT,viewport);
    
	glRenderMode(GL_SELECT);
    
	glInitNames();
    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}


void processHits2 (GLint hits, GLuint buffer[], int sw)
{
    GLint i, j, numberOfNames = 0;
    GLuint names, *ptr, minZ,*ptrNames = nullptr;
    
    ptr = (GLuint *) buffer;
    minZ = 0xffffffff;
    for (i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < minZ) {
            numberOfNames = names;
            minZ = *ptr;
            ptrNames = ptr+2;
        }
        
        ptr += names+2;
	}
    if (numberOfNames > 0) {
        printf ("You picked snowman  ");
        ptr = ptrNames;
        for (j = 0; j < numberOfNames; j++,ptr++) {
            printf ("%d ", *ptr);
        }
	}
    


    printf("You didn't click a snowman!");
    printf ("\n");
    
}

void stopPicking() {
    
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
		processHits2(hits,selectBuf,0);
	}
	mode = RENDER;
}


void display()
{
    glutSetWindow(mainWindow);
    
    glutPostRedisplay();
    preProcessEvents();
    
    
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    skybox.render();
    

    glLoadIdentity();
    
    //camera
    gluLookAt(Camera::position.x, Camera::position.y, Camera::position.z,
              Camera::position.x+Math::sind(Camera::rotationAngles.x)*Math::cosd(Camera::rotationAngles.y),
              Camera::position.y+Math::cosd(Camera::rotationAngles.x),
              Camera::position.z+Math::sind(Camera::rotationAngles.x)*Math::sind(Camera::rotationAngles.y),
              0.0, 1.0, 0.0);
    if (city==true && menu==false)
    {
        glEnable(GL_LIGHTING);
        //stupid triangle thing
        glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0);
        glVertex3f(-1, 0,-3);
        glColor3f(0, 1, 0);
        glVertex3f(0.0f, 2.0f,-3);
        glColor3f(0, 0, 1);
        glVertex3f(1.0f, 0.0f,-3);
        glEnd();
        
        
        //dice code
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        vector3f start=vector3f(-150, 100, 10);
        vector3f end=vector3f(-10,0,0);
        vector3f perpBisectorDirection=vector3f((start.x+end.x),(start.y+end.y),(start.z+end.z));
        vector3f tan1(-(start.x-8*perpBisectorDirection.x+end.x)/6,-(start.y-8*perpBisectorDirection.y+end.y)/6, -(start.z-8*perpBisectorDirection.z+end.z)/6);
        
        glColor3f(1.0, 0.0, 0.0);
        glLineWidth(12.0);
        int t=360;
        if (i<=t)
        {
            diceRotate++;
            i++;

        }
        float pos = (float) i / (float) t;
        
        GLfloat x=bezierCurve(pos, start.x, tan1.x, tan1.x,end.x);
        GLfloat y=bezierCurve(pos, start.y, tan1.y, tan1.y,end.y);
        GLfloat z=bezierCurve(pos, start.z, tan1.z, tan1.z,end.z);
        glTranslatef(10, +10, 0);
        glTranslatef(x, y, z);

        if (facevalue==1)
        {
            glRotatef(90, 0, 1, 0);
        }
        else if (facevalue==2)
        {
            glRotatef(-90, 0, 0, 1);
        }
        else if (facevalue==3)
        {
            glRotatef(180, 0, 1, 0);
        }
        else if (facevalue==4)
        {
            glRotatef(0, 0, 1, 0);
        }
        else if (facevalue==5)
        {
            glRotatef(90, 0, 0, 1);
        }
        else if (facevalue==6)
        {
            glRotatef(-90, 0, 1, 0);
        }
        
        glRotatef(diceRotate, 1, 1, 1);
        object2.draw();
        
        glPopMatrix();
        


        //floor
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
        
        //castle
        glPushMatrix();
        object1.draw();
        glPopMatrix();
    }
    
    if (globe==true)
    {
        
        if (mode == SELECT) {
            startPicking();
        }
        //globe
        glTranslatef(-10.0, 10.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, tex2->textureID);
        gluQuadricTexture(quad,1);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef(venusRotate, 0.0, 0.0, 1.0);
        drawRandomSpherePoints();
        
        for (int i=0; i<cityVertices.size()-1; i++)
        {
            vector3f start=cityVertices.at(i);
            vector3f end=cityVertices.at(i+1);
            vector3f perpBisectorDirection=vector3f((start.x+end.x),(start.y+end.y),(start.z+end.z));
            vector3f tan1(-(start.x-8*perpBisectorDirection.x+end.x)/6,-(start.y-8*perpBisectorDirection.y+end.y)/6, -(start.z-8*perpBisectorDirection.z+end.z)/6);
            
            glColor3f(1.0, 0.0, 0.0);
            glLineWidth(12.0);
            glBegin(GL_LINE_STRIP);

            int t = 30;
            for (int i = 0; i <= t; i++) {
                float pos = (float) i / (float) t;
                
                GLfloat x=bezierCurve(pos, start.x, tan1.x, tan1.x,end.x);
                GLfloat y=bezierCurve(pos, start.y, tan1.y, tan1.y,end.y);
                GLfloat z=bezierCurve(pos, start.z, tan1.z, tan1.z,end.z);
                
                vector3f result(x, y, z);
                glVertex3f(x, y, z);
            }
            glEnd();

        }
        gluSphere(quad,10,20,20);
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    
    if (menu==true)
    {
    
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 10.0);
        glMatrixMode(GL_MODELVIEW);
        //glPushMatrix();        ----Not sure if I need this
        glLoadIdentity();
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glClear(GL_DEPTH_BUFFER_BIT);
    
        glPushMatrix();
        glTranslatef(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/4, 0);
        glScalef(1, -1, 1);
        glScalef(2, 2, 2);
        glColor3f(1, 1, 0);
        dtx_string(menuText[0].c_str());
        cout<<cursorX<<" "<<cursorY<<endl;
        glPopMatrix();
        glPushMatrix();
        glTranslatef(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/4+80, 0);
        glScalef(1, -1, 1);
        glScalef(1.5, 1.5, 1.5);
        dtx_string(menuText[1].c_str());
        glPopMatrix();
        glPushMatrix();
        glTranslatef(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/4+130, 0);
        glScalef(1, -1, 1);
        glScalef(1.5, 1.5, 1.5);
        dtx_string(menuText[2].c_str());
        glPopMatrix();
        // Making sure we can render 3d again
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        //glPopMatrix();        ----and this?
    }
    if (mode == SELECT)
		stopPicking();

	else
		glutSwapBuffers();
}

//game buttons
GLUI *glui_subwin2;
GLUI_Panel *playerPanel,*controlsPanel, *taxPanel, *cardsPanel, *jailFinePanel, *mortgagePanel;
GLUI_Listbox *moneyListBox,*currentLocationListBox,*playerIDListBox,*reportCheatingListBox,*mortgageListBox,*taxAmountListBox;
GLUI_Listbox *cardNameListBox,*cardOwnerListBox,*cardStatusListBox,*cardMortgageListBox,*cardTaxListBox;
GLUI_RadioGroup *taxRadio;
void gameButtons()
{
    int money=1299;
    string currentLocation="Medittersoemthign";
    int playerID=2;
    
    
     glui_subwin2 = GLUI_Master.create_glui_subwindow(mainWindow, GLUI_SUBWINDOW_LEFT );
    
    glui_subwin2->set_main_gfx_window( mainWindow );
    playerPanel=glui_subwin2->add_panel("player data");
    glui_subwin2->add_statictext_to_panel(playerPanel, "something");

    moneyListBox=glui_subwin2->add_listbox_to_panel(playerPanel, "cash", NULL, 1, (GLUI_Update_CB)NULL);
    moneyListBox->add_item(1,to_string(money).c_str());
    
    currentLocationListBox=glui_subwin2->add_listbox_to_panel(playerPanel, "currentLocation",NULL, 2, (GLUI_Update_CB)NULL);
    currentLocationListBox->add_item(2, currentLocation.c_str());
    
    playerIDListBox=glui_subwin2->add_listbox_to_panel(playerPanel, "player ID", NULL,3,(GLUI_Update_CB)NULL);
    playerIDListBox->add_item(3,to_string(playerID).c_str());
    
    controlsPanel=glui_subwin2->add_panel("controls");
    glui_subwin2->add_button_to_panel(controlsPanel, "pay rent", 4,(GLUI_Update_CB)payRent);
    reportCheatingListBox=glui_subwin2->add_listbox_to_panel(controlsPanel, "player who is Cheating",NULL,5,(GLUI_Update_CB)reportCheating);
    reportCheatingListBox->add_item(1, "player1");
    glui_subwin2->add_button("report cheating");
    mortgageListBox=glui_subwin2->add_listbox_to_panel(controlsPanel, "mortgage",NULL,6,(GLUI_Update_CB)payRent);
    
    taxPanel=glui_subwin2->add_panel("Tax");
    taxRadio=glui_subwin2->add_radiogroup_to_panel(taxPanel,NULL,7,(GLUI_Update_CB)NULL);
    glui_subwin2->add_radiobutton_to_group(taxRadio, "percent");
    glui_subwin2->add_radiobutton_to_group(taxRadio, "amount");
    taxAmountListBox= glui_subwin2->add_listbox_to_panel(taxPanel,"taxAmount",NULL,7,(GLUI_Update_CB)NULL);
    glui_subwin2->add_button_to_panel(taxPanel, "pay taxes",8,(GLUI_Update_CB)NULL);
    glui_subwin2->add_button_to_panel(playerPanel, "other thign",1,(GLUI_Update_CB)payRent);
    
    
    cardsPanel=glui_subwin2->add_panel("cards data");
    cardNameListBox=glui_subwin2->add_listbox_to_panel(cardsPanel, "Name",NULL,8,(GLUI_Update_CB)NULL);
    cardOwnerListBox=glui_subwin2->add_listbox_to_panel(cardsPanel, "Owner",NULL,9,(GLUI_Update_CB)NULL);
    cardStatusListBox=glui_subwin2->add_listbox_to_panel(cardsPanel, "Status",NULL,10,(GLUI_Update_CB)NULL);
    cardMortgageListBox=glui_subwin2->add_listbox_to_panel(cardsPanel, "Mortgage", NULL,11, (GLUI_Update_CB)NULL);
    cardTaxListBox=glui_subwin2->add_listbox_to_panel(cardsPanel, "Tax",NULL,12,(GLUI_Update_CB)NULL);
    
    jailFinePanel=glui_subwin2->add_panel("jailFine");
    glui_subwin2->add_button_to_panel(jailFinePanel, "pay JailFine",13,(GLUI_Update_CB)NULL);
    

    
}


int main(int argc,char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    mainWindow=glutCreateWindow(WINDOW_TITLE);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    GLUI_Master.set_glutIdleFunc( display );
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
    
    object1.load("/Users/robinmalhotra2/Downloads/Cities/tzfhx79fnc-castle/castle/castle.obj");
    object2.load("/Users/robinmalhotra2/Downloads/dice-2.obj");
    for (int i=0; i<40; i++)
    {
        
        vector3f point=randomSpherePoint();
        cityVertices.push_back(point);
    }
    
    facevalue = getDiceFace();
    gameButtons();
    string filenames[6]={
        "snow_positive_z.bmp",
        "snow_negative_x.bmp",
        "snow_negative_z.bmp",
        "snow_positive_x.bmp",
        "snow_positive_y.bmp",
        "snow_negative_y.bmp",
    };
    skybox.loadSkyBox("/Users/robinmalhotra2/Downloads/skybox/", filenames);
    if(!(font = dtx_open_font("/Users/robinmalhotra2/Developer/xcodeglut/XcodeGlut/Starjout.ttf", 25))) {
        		fprintf(stderr, "failed to open font\n");
        	return 1;
    }
    glutMainLoop();
    return 0;
}

