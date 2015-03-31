#ifndef COP_ASSIGNMENT1_BALL_H
#define COP_ASSIGNMENT1_BALL_H

#include "Vector.h"
#include <random>
using namespace std;
/*! \brief Ball class defines the 3d ball
 *
 *  contains ctors,equality operators,and a factory method for random instantiation
 * 
 *
 */
typedef uniform_real_distribution<> urd;

class Ball {
public:
	Vector3d<float> centre;
	Vector3d<float> velocity;
	float radius;
	float red;
	float green;
	float blue;
	float mass;
    Ball();
    Ball(const Ball& a);
    
    //! copy assignment operator for the ball class
    
    
    /*!
     \param a,a Ball object 
     \result a reference to a Ball object is returned as output
     
     */
    Ball& operator=(const Ball& a);
    
    
    
    //! factory method for creating a ball with random coordinates
    
    /*!
     \param xposGen, utility for generating random number for x coordinate
     \param yposGen,utility for generating random number for y coordinate 
     
     \param zposgen,utility for generating random number for z coordinate
     
     \param radGen,utility for generating random number for radius of ball
     \param velGen,utility for generating x,y and z components of velocity
     \param colorGen, utility for generating rgb components of ball's color
     
     \result a Ball object with random state variables
     
     */
	void initBall(urd& xposGen, urd& yposGen, urd& zposGen, urd& radGen, urd& velGen, urd& colorGen, mt19937& ran);
    void scale(float amt){radius*=amt;}
};

#endif