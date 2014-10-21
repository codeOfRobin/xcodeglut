//
//  Keyboard.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 21/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "Keyboard.h"

bool keyBoard::key[256];
void keyBoard::keyDown(unsigned char k, int x, int y)
{
    key[k]=true;
    
}

void keyBoard::keyUp(unsigned char k, int x, int y)
{
    key[k]=false;
}