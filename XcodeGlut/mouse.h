//
//  mouse.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 21/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__mouse__
#define __XcodeGlut__mouse__

#include <iostream>
class mouse
{
public:
    static int lastX, lastY;
    static int currentX, currentY;
    static int deltaX, deltaY;
    
    static void move(int x, int y);
    static void update();
};
#endif /* defined(__XcodeGlut__mouse__) */
