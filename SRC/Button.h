//
//  Button.h
//  COP Assignment 1
//
//  Created by Shikhar on 25/01/15.
//  Copyright (c) 2015 Akshay Gupta. All rights reserved.
//

#ifndef __COP_Assignment_1__Button__
#define __COP_Assignment_1__Button__

#include <stdio.h>
#include <vector>

using namespace std;
class Button {
public:
    
    int xTopLeft; //!<  describes position of the button on the screen.
    int yTopLeft; //!<  describes position of the button on the screen
    int width; //!<  describes the width of the button on the screen
    int height; //!<  describes the height of the button on the screen
    char text[100]; //!<  a char array for storing the text
    float textLength; //!<  length of the text that shows up on the GUI button
    bool pressed; //!<  Boolean indicator that checks for click and release events
    void initButton(int x, int y, int w, int h, char *s);
    void initButton(int x, int y, int w, int h, char *s,vector<float>&,vector<float>&);
    vector<float> back_color; //!< color of the button when it's not pressed
    vector<float> click_color; //!< describes the color to which the button changes to on clicking it
    void setText(char *s); //!<  sets the text on the button to parameter specified by user
    
};




#endif /* defined(__COP_Assignment_1__Button__) */
