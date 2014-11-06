//
//  skyBoxTexture.cpp
//  XcodeGlut
//
//  Created by Robin Malhotra on 06/11/14.
//  Copyright (c) 2014 Robin's code kitchen. All rights reserved.
//

#include "skyBoxTexture.h"
void skyBoxTexture::render()
{
    // Store the current matrix
    glPushMatrix();
    // Reset and transform the matrix.
    // Enable/Disable features
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    // Just in case we set all vertices to white.
    glColor4f(1,1,1,1);
    // Render the front quad
    glBindTexture(GL_TEXTURE_2D, textures[0]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  1000, -1000.0f, -1000.0f );
    glTexCoord2f(1, 0); glVertex3f( -1000.0f, -1000.0f, -1000.0f );
    glTexCoord2f(1, 1); glVertex3f( -1000.0f,  1000.0f, -1000.0f );
    glTexCoord2f(0, 1); glVertex3f(  1000.0f,  1000.0f, -1000.0f );
    glEnd();
    // Render the left quad
    glBindTexture(GL_TEXTURE_2D, textures[1]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 0); glVertex3f(  1000.0f, -1000.0f, -1000.0f );
    glTexCoord2f(1, 1); glVertex3f(  1000.0f,  1000.0f, -1000.0f );
    glTexCoord2f(0, 1); glVertex3f(  1000.0f,  1000.0f,  1000.0f );
    glEnd();
    // Render the back quad
    glBindTexture(GL_TEXTURE_2D,textures[2]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 0); glVertex3f(  1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 1); glVertex3f(  1000.0f,  1000.0f,  1000.0f );
    glTexCoord2f(0, 1); glVertex3f( -1000.0f,  1000.0f,  1000.0f );
    glEnd();
    // Render the right quad
    glBindTexture(GL_TEXTURE_2D,textures[3]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -1000.0f, -1000.0f, -1000.0f );
    glTexCoord2f(1, 0); glVertex3f( -1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 1); glVertex3f( -1000.0f,  1000.0f,  1000.0f );
    glTexCoord2f(0, 1); glVertex3f( -1000.0f,  1000.0f, -1000.0f );
    glEnd();
    // Render the top quad
    glBindTexture(GL_TEXTURE_2D, textures[4]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f( -1000.0f,  1000.0f, -1000.0f );
    glTexCoord2f(0, 0); glVertex3f( -1000.0f,  1000.0f,  1000.0f );
    glTexCoord2f(1, 0); glVertex3f(  1000.0f,  1000.0f,  1000.0f );
    glTexCoord2f(1, 1); glVertex3f(  1000.0f,  1000.0f, -1000.0f );
    glEnd();
    // Render the bottom quad
    glBindTexture(GL_TEXTURE_2D, textures[5]->textureID);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f( -1000.0f, -1000.0f, -1000.0f );
    glTexCoord2f(0, 1); glVertex3f( -1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 1); glVertex3f(  1000.0f, -1000.0f,  1000.0f );
    glTexCoord2f(1, 0); glVertex3f(  1000.0f, -1000.0f, -1000.0f );
    glEnd();
    glDepthMask(GL_TRUE);
    // Restore enable bits and matrix
    glPopAttrib();
    glPopMatrix();
}
