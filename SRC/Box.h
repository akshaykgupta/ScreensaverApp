//
//  Box.h
//  COP Assignment 1
//
//  Created by Akshay Gupta on 1/20/15.
//  Copyright (c) 2015 Akshay Gupta. All rights reserved.
//

#ifndef COP_Assignment_1_Box_h
#define COP_Assignment_1_Box_h

/*! \brief Box class encapsulates the cube in which the balls are contained
 
 
 */

class Box {
public:
    float boxWidth; //!<  float describing the width of the box,with default value 500
    float boxHeight; //!< float describing the height of the box,with default value 500
    float boxDepth; //!<  float describing the depth of the box,with default value 500
    Box()
    {
        boxWidth = 500;
        boxHeight = 500;
        boxDepth = 500;
    }
};
#endif
