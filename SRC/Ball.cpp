//
//  Ball.cpp
//  COP Assignment 1
//
//  Created by Shikhar on 25/01/15.
//  Copyright (c) 2015 Akshay Gupta. All rights reserved.
//

#include <stdio.h>
#include "Ball.h"
#include <iostream>


using namespace std;


Ball::Ball()
{
    radius = red = green = blue = mass = 0.0;
}

Ball::Ball(const Ball &a)
{
    centre = a.centre;
    velocity = a.velocity;
    radius = a.radius;
    red = a.red;
    green = a.green;
    blue = a.blue;
    mass = a.mass;
}

Ball& Ball::operator=(const Ball& a)
{
    centre = a.centre;
    velocity = a.velocity;
    radius = a.radius;
    red = a.red;
    green = a.green;
    blue = a.blue;
    mass = a.mass;
    return *this;
}

void Ball::initBall(urd& xposGen, urd& yposGen, urd& zposGen, urd& radGen, urd& velGen, urd& colorGen, mt19937& ran)
{
    centre.x = xposGen(ran);
    centre.y = yposGen(ran);
    centre.z = zposGen(ran);
    radius = radGen(ran);
    velocity.x = velGen(ran);
    velocity.y = velGen(ran);
    velocity.z = velGen(ran);
    red = colorGen(ran);
    green = colorGen(ran);
    blue = colorGen(ran);
    mass = radius * radius * radius;
    #ifdef DEBUG
		cout<<velocity.x<<" "<<velocity.y<<" "<<velocity.z<<endl;
	#endif
}
