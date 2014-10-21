//
//  mouse.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 21/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "mouse.h"
int mouse::lastX=0, mouse::lastY=0;
int mouse::currentX=0, mouse::currentY=0;
int mouse::deltaX=0, mouse::deltaY=0;
void mouse::move(int x, int y)
{
    currentX=x;
    currentY=y;

}

void mouse::update()
{
    

    deltaX=currentX-lastX;
    deltaY=currentY-lastY;
    
    lastX=currentX;
    lastY=currentY;
    

}