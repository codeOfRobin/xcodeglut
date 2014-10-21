//
//  Keyboard.h
//  XcodeGlut
//
//  Created by Robin Malhotra on 21/10/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#ifndef __XcodeGlut__Keyboard__
#define __XcodeGlut__Keyboard__

#include <iostream>
using namespace std;
class keyBoard {
    
public:
    static bool key[256];
    static void keyDown(unsigned char key, int x, int y);
    static void keyUp(unsigned char key, int x, int y);
};
#endif /* defined(__XcodeGlut__Keyboard__) */
