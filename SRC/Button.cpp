//
//  Button.cpp
//  COP Assignment 1
//
//  Created by Shikhar on 25/01/15.
//  Copyright (c) 2015 Akshay Gupta. All rights reserved.
//

#include "Button.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

void Button::initButton(int x, int y, int w, int h, char *s)
{
    
    xTopLeft = x;
    yTopLeft = y;
    width = w;
    height = h;
    textLength = 0.0;
    int i;
    
    for(i = 0; s[i]!= '\0'; i++)
    {
        text[i] = s[i];
    }
     textLength += glutBitmapLength(GLUT_BITMAP_HELVETICA_12,reinterpret_cast<unsigned char*> (text));
    textLength *= 3;
    text[i] = '\0';
    
    pressed = false;
    back_color.resize(3);
    
    click_color.resize(3);
    back_color[0]=1.0;back_color[1]=0.698;back_color[2]=0.4;
    
    click_color[0]=1.0;click_color[1]=0.6;click_color[2]=0.6;
    
}

void Button::initButton(int x, int y, int w, int h, char *s,vector<float> &bc,vector<float>& fc)
{
    
    xTopLeft = x;
    yTopLeft = y;
    width = w;
    height = h;
    textLength = 0.0;
    int i;
    for(i = 0; s[i]!= '\0'; i++)
    {
        text[i] = s[i];

    }
    text[i] = '\0';
    textLength += glutBitmapLength(GLUT_BITMAP_HELVETICA_12,reinterpret_cast<unsigned char*> (text));
    textLength *= 3;
    pressed = false;
    back_color.resize(3);
    back_color[0] = bc[0];back_color[1]=bc[1];back_color[2]=bc[2];
    click_color.resize(3);
    click_color[0]=fc[0];click_color[1]=fc[1];click_color[2]=fc[2];
    
}


void Button::setText(char *s)
{
    
    int i;
    textLength = 0.0;
    
    for(i = 0; s[i]!= '\0'; i++){
        text[i] = s[i];
    }
    text[i] = '\0';
     textLength += glutBitmapLength(GLUT_BITMAP_HELVETICA_12,reinterpret_cast<unsigned char*> (text));
    textLength *= 3;
    
}




