#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <random>
#include <pthread.h>
#include <string>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include "Box.h"
#include "Ball.h"
#include "messageQueue.h"
#include "Button.h"
#include <string.h>
using namespace std;


/*! \brief main class contains implementations of utilities passed to openGL callbacks
    such as display,timer,resize,callbacks for handling clicking events,and keyboard inputs
 *
 *
 *
 *
 
 */

#define PI 3.14159
#define NUMSEGMENTS 20
#define WINDOWWIDTH  1000
float old_height = 650;
float old_width = 650;
float MaxVelocity= 50;
bool enable_gravity = 0;
float Cr = 1.0;
int numBalls = 100;
int numThreads = 30;
int timingInterval = 5;
int threadCount = 0; //so that timer can know when all threads are done
int prevIndex = numBalls;
float prevGreen = 0.0;
float prevRed = 0.0;
float prevBlue = 0.0;
float xrotate = 0.0;
float yrotate = 0.0;
float zrotate = 0.0;
bool togglePause = false;
pthread_mutex_t parentCondMutex = PTHREAD_MUTEX_INITIALIZER; //!< mutex for timer function (parent)
pthread_cond_t parentConditional = PTHREAD_COND_INITIALIZER; //!< conditional for timer function (parent)
vector<pthread_mutex_t> childCondMutex; //!< vector of mutexes for ball threads (children)
vector<pthread_cond_t> childConditional; //!< vector of conditionals for ball threads (children)
vector<bool> startThreadComp; //!< boolean vector for start thread condition
Vector3d<float> gravity(0.0,-0.49,0.0);
Box box; //!<  global Box object
vector<Ball> Balls; //!<  vector containing numBalls Ball objects
vector< messageQueue<Ball> > messageQueues; //!<  describes position of the button on the screen.
vector<Vector3d<float> > old_speed;
vector<float> old_z_coordinates(numBalls);
Button increaseSpeedButton, decreaseSpeedButton, gravityButton,pauseButton;
bool is2D = false;



class Graphics{
public:
    
    //! initializes the program by drawing the screen using glOrtho and randomly initializing the balls

    void operator()(){
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glFrustum(-100, 100, -100, 100,0,  WINDOWWIDTH);
        glOrtho(-WINDOWWIDTH, WINDOWWIDTH, -WINDOWWIDTH, WINDOWWIDTH, -WINDOWWIDTH, WINDOWWIDTH);
        glEnable(GL_DEPTH_TEST);
        GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
        //GLfloat light_position[] = { 0.0, 0.0, 0.0, 0.0 };
        glShadeModel(GL_SMOOTH);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
        
        
        
        randInitBalls();
        
    }
    
    
    //! draws GUI buttons on the screen using openGL utilities
    /*!
     \param b,a reference to a button object
     \result the button b,is drawn on the screen
     \sa drawBall(Ball& ball)
     
     */
    
    void operator()(Box& box)
    {
        glColor3f(1.0, 1.0, 1.0);
        GLfloat mat_color[] = {1.0, 1.0, 1.0, 1.0};
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_color);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        
        //Back face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-box.boxWidth, -box.boxHeight, -box.boxDepth);
        glVertex3f(-box.boxWidth, box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, -box.boxHeight, -box.boxDepth);
        glEnd();
        
        //Front face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-box.boxWidth, -box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, box.boxHeight, box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, box.boxDepth);
        glVertex3f(box.boxWidth, -box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, -box.boxHeight, box.boxDepth);
        glEnd();
        
        
        
        //Left face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-box.boxWidth, -box.boxHeight, -box.boxDepth);
        glVertex3f(-box.boxWidth, -box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, box.boxHeight, -box.boxDepth);
        glEnd();
        
        //Right face
        glBegin(GL_LINE_LOOP);
        glVertex3f(box.boxWidth, -box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, -box.boxHeight, box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, -box.boxDepth);
        glEnd();
        
        
        
        //Top face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-box.boxWidth, box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, box.boxHeight, box.boxDepth);
        glEnd();
        
        //Bottom face
        glBegin(GL_LINE_LOOP);
        glVertex3f(-box.boxWidth, -box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, -box.boxHeight, -box.boxDepth);
        glVertex3f(box.boxWidth, -box.boxHeight, box.boxDepth);
        glVertex3f(-box.boxWidth, -box.boxHeight, box.boxDepth);
        glEnd();

    }
    
    
    
    //! draws a ball on the screen using openGL utilities
    /*!
     \param ball,a reference to a Ball object
     \result the Ball ball,is drawn on the screen
     \sa drawButton(Button& b)
     
     */
    void operator()(Ball& ball)
    {
        glColor3f(ball.red, ball.green, ball.blue);
        GLfloat mat_color[] = {ball.red, ball.green, ball.blue, 1.0};
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_color);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        for (int i = 0; i < NUMSEGMENTS; i++)
        {
            for (int j = 0; j < NUMSEGMENTS; j++)
            {
                glBegin(GL_POLYGON);
                glNormal3f(X[i][j], Y[i][j], Z[i][j]);
                glVertex3f(ball.centre.x + ball.radius * X[i][j], ball.centre.y + ball.radius * Y[i][j], ball.centre.z + ball.radius * Z[i][j]);
                glNormal3f(X[i][j + 1], Y[i][j + 1], Z[i][j + 1]);
                glVertex3f(ball.centre.x + ball.radius * X[i][j + 1], ball.centre.y + ball.radius * Y[i][j + 1], ball.centre.z + ball.radius * Z[i][j + 1]);
                glNormal3f(X[i + 1][j + 1], Y[i + 1][j + 1], Z[i + 1][j + 1]);
                glVertex3f(ball.centre.x + ball.radius * X[i + 1][j + 1], ball.centre.y + ball.radius * Y[i + 1][j + 1], ball.centre.z + ball.radius * Z[i + 1][j + 1]);
                glNormal3f(X[i + 1][j], Y[i + 1][j], Z[i + 1][j]);
                glVertex3f(ball.centre.x + ball.radius * X[i + 1][j], ball.centre.y + ball.radius * Y[i + 1][j], ball.centre.z + ball.radius * Z[i + 1][j]);
                glEnd();
            }
        }
    }
    
    
    void operator()(Button& b)
    {
        if(!b.pressed)
            glColor3f(b.back_color[0], b.back_color[1], b.back_color[2]);
        else
            glColor3f(b.click_color[0], b.click_color[1], b.click_color[2]);
        glBegin(GL_POLYGON);
        glVertex2f(b.xTopLeft, b.yTopLeft);
        glVertex2f(b.xTopLeft + b.width, b.yTopLeft);
        glVertex2f(b.xTopLeft + b.width, b.yTopLeft - b.height);
        glVertex2f(b.xTopLeft, b.yTopLeft - b.height);
        glVertex2f(b.xTopLeft, b.yTopLeft);
        glEnd();
        int fontx = b.xTopLeft + (b.width - b.textLength) / 2;
        int fonty = b.yTopLeft - (b.height + 10) / 2;
        glColor3f(0, 0, 0);
        glRasterPos2f(fontx, fonty);
        for(int i = 0; b.text[i] != '\0'; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, b.text[i]);
        }
        GLfloat mat_emission1[] = {0.0, 0.0, 0.0, 1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission1);
    }
    
    
    void randInitBalls()
    {
        Balls.reserve(numBalls);
        mt19937 ran((random_device())());
        uniform_real_distribution<> xposGen(-box.boxWidth, box.boxWidth);
        uniform_real_distribution<> yposGen(-box.boxHeight, box.boxHeight);
        uniform_real_distribution<> zposGen(-box.boxDepth, box.boxDepth);
        uniform_real_distribution<> radGen(20.0, 30.0);
        uniform_real_distribution<> velGen(-5.0, 5.0);
        uniform_real_distribution<> colorGen(0.2, 1.0);
        for (int i = 0; i < numBalls; i++)
        {
            Ball newBall;
            newBall.initBall(xposGen, yposGen, zposGen, radGen, velGen, colorGen, ran);
            Balls.push_back(newBall);
        }
        for (int i = 0; i <= NUMSEGMENTS; i++)
        {
            // Last vertex same as first vertex
            float angle1 = i * 2.0 * PI / NUMSEGMENTS;  // 360 deg for all segments
            
            for (int j = 0; j <= NUMSEGMENTS; j++)
            {
                float angle2 = j * PI / NUMSEGMENTS;
                X[i][j] = cos(angle1) * sin(angle2);
                Y[i][j] = sin(angle1) * sin(angle2);
                Z[i][j] = cos(angle2);
            }
        }
        
        initializeButtons();
    }
    
private:
    
    
    float X[NUMSEGMENTS + 1][NUMSEGMENTS + 1]; //!<  global 2D array of floats for drawing a sphere
    float Y[NUMSEGMENTS + 1][NUMSEGMENTS + 1]; //!<  global 2D array of floats for drawing a sphere
    float Z[NUMSEGMENTS + 1][NUMSEGMENTS + 1]; //!<  global 2D array of floats for drawing a sphere
    

    
        
    void initializeButtons(){
        char s[100] = "Increase Speed";
        vector<float> back_color(3);
        vector<float> click_color(3);
        back_color[0]=0.2;back_color[1]=0.6;back_color[2]=1.0;
        click_color[0]=0.8;click_color[1]=0.6;click_color[2]=1.0;
        increaseSpeedButton.initButton(-WINDOWWIDTH+200, -WINDOWWIDTH + 250, 500, 225, s,click_color,back_color);
        strcpy(s, "Decrease Speed");
        decreaseSpeedButton.initButton(WINDOWWIDTH - 700, -WINDOWWIDTH + 250, 500, 225, s,click_color,back_color);
        strcpy(s, "Enable Gravity");
        gravityButton.initButton(-250, -WINDOWWIDTH + 250, 500, 100, s);
        strcpy(s, "Pause");
        pauseButton.initButton(-250, -WINDOWWIDTH + 125, 500, 100, s);
        }
    
    
};



Graphics graphics;


//! updates the velocities of the 2 balls after collision
/*!
 \param a,a reference to a Ball object
 \param b, a reference to a Ball object
 \param Cr, a float initialized to 1.0, describing the coefficient of restitution between the balls
 \result the two balls are updated after collision
 
 
 */

void updateBalls(Ball &a, Ball& b, float Cr)
{
    Vector3d<float> t(b.centre);
    t.subtract(a.centre);
    Vector3d<float> velocityA(a.velocity);
    Vector3d<float> velocityB(b.velocity);
    if(t.mod() > (a.radius + b.radius))
        return;
    t.normalize();
    Vector3d<float> t1(t),t2(t),t3(t),t4(t);
    float u1 = t.dot(velocityA);
    float u2 = t.dot(velocityB);
    float mass1 = a.mass;
    float mass2 = b.mass;
    float v1 =( Cr*mass2*(u2-u1) + mass1*u1 + mass2*u2)/(mass1 + mass2);
    float v2 =( Cr*mass1*(u1 - u2) + mass2*u2 + mass1*u1)/(mass1 + mass2);
    t.scale(u1);
    velocityA.subtract(t);
    t1.scale(v1);
    velocityA.add(t1);
    t2.scale(u2);
    velocityB.subtract(t2);
    t3.scale(v2);
    velocityB.add(t3);
    velocityA.comp(a.velocity);
    velocityB.comp(b.velocity);
    Vector3d<float> fpos(a.centre);
    t4.scale(a.radius + b.radius + 0.000001);
    fpos.add(t4);
    fpos.comp(b.centre);
}


//! updates the velocity and position of a ball after a wall collision
/*!
 \param ball,a reference to a Ball object

 \result the velocity and position of the ball is updated after collision
 
 
 */

void wallCollision(Ball& ball)
{
    if(ball.centre.x + ball.radius > box.boxWidth)
    {
        ball.centre.x = box.boxWidth - ball.radius;
        ball.velocity.x *= -Cr;
    }
    if(ball.centre.x - ball.radius < -box.boxWidth)
    {
        ball.centre.x = -box.boxWidth + ball.radius;
        ball.velocity.x *= -Cr;
    }
    if(ball.centre.y + ball.radius > box.boxHeight)
    {
        ball.centre.y = box.boxHeight - ball.radius;
        ball.velocity.y *= -Cr;
    }
    if(ball.centre.y - ball.radius < -box.boxHeight)
    {
        ball.centre.y = -box.boxHeight + ball.radius;
        ball.velocity.y *= -Cr;
    }
    if(ball.centre.z + ball.radius > box.boxDepth)
    {
        ball.centre.z = box.boxDepth - ball.radius;
        ball.velocity.z *= -Cr;
    }
    if(ball.centre.z - ball.radius < -box.boxDepth)
    {
        ball.centre.z = -box.boxDepth + ball.radius;
        ball.velocity.z *= -Cr;
    }
}

//! handles the physics in a gravity enabled environment
/*!
 \param ball,a reference to a Ball object
 \param enable_gravity, a boolean indicating where gravity is enabled or disabled
 \param togglePause, a boolean indicating whether the motion has been paused

 
 
 */

void handleGravity(Ball& ball,bool enable_gravity, bool togglePause)
{
    if(enable_gravity && !togglePause)
    {   //Changing y coordinate and speed:
        if (ball.centre.y + 0.5 * gravity.y - ball.radius > -box.boxHeight)
        {
            ball.centre.y += 0.5 * gravity.y;
            ball.velocity.add(gravity);
        }
        else
        {
            float x = abs(box.boxHeight + ball.centre.y);
            ball.centre.y = -box.boxHeight + ball.radius;
            ball.velocity.y = Cr*sqrt(abs((ball.velocity.y*ball.velocity.y)- 2*gravity.y*x));
        }
    }
}



//! thread function,handles computation that each thread performs in every loop

/*!
 \param args,a void pointer that carries information about the thread's unique ID
 
 The thread computation manages threadRatio( = numBalls/numThreads) number of balls
 the computation is carried out in a while loop,and begins after receiving a signal from the timer
 function. it manages wallCollision,and mutual collision among all the threadRatio balls,and then
 using one to one communication model,handles ball collision with other balls
 
 */


void* ballControl(void* args)
{
    int i = (long) args;
    int threadRatio = numBalls / numThreads;
    int left = numBalls % numThreads;
    int lessBalls = numThreads - left;
    while(true)
    {
        //wait for signal from timer
        pthread_mutex_lock(&childCondMutex[i]);
        while(!startThreadComp[i])
            pthread_cond_wait(&childConditional[i], &childCondMutex[i]);
        pthread_mutex_unlock(&childCondMutex[i]);
        //after signal update ball position and check wall collisions
        int startIndex = i * threadRatio;
        int endIndex = startIndex + threadRatio;
        if(i >= lessBalls)
        {
            startIndex += (i - lessBalls);
            endIndex = startIndex + threadRatio + 1;
        }
        for(int j = startIndex; j < endIndex; j++)
        {
            Balls[j].centre.add(Balls[j].velocity);
            handleGravity(Balls[j],enable_gravity, togglePause);
            wallCollision(Balls[j]);
        }
        
        
        //ball collision
        for(int j = startIndex; j < endIndex; j++)
        {
            for(int k = j + 1; k < endIndex; k++)
            {
                updateBalls(Balls[j], Balls[k], Cr);
            }
        }
        for (int j = 0; j < numThreads; j++)
        {
            if(j != i)
            {
                for(int k = startIndex; k < endIndex; k++)
                    messageQueues[j].addItem(Balls[k]);
            }
        }
        int doneSofar = 0;
        while(doneSofar != numBalls - (endIndex - startIndex))
        {
            Ball m = messageQueues[i].remove();
            //float d = sqrt((Balls[i].centre.x - m.centre.x) * (Balls[i].centre.x - m.centre.x) + (Balls[i].centre.y - m.centre.y) * (Balls[i].centre.y - m.centre.y));
            //if(d < Balls[i].radius + m.radius)
            for(int j = startIndex; j < endIndex; j++)
                updateBalls(m, Balls[j], Cr);
            doneSofar++;
        }
        pthread_mutex_lock(&parentCondMutex);
        threadCount += 1;
        startThreadComp[i] = false;
        pthread_cond_signal(&parentConditional);
        pthread_mutex_unlock(&parentCondMutex);
    }
}


//! display function that is passed to glutDisplayFunc
/*!
 call relevant routines for drawing buttons,balls and box
 
 
 */

void display() {
    // if(togglePause)
    // 	cout<<"hi\n";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    graphics(increaseSpeedButton);
    graphics(decreaseSpeedButton);
    graphics(gravityButton);
    graphics(pauseButton);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glRotatef(zrotate, 0.0, 0.0, 1.0);
    glRotatef(yrotate, 0.0, 1.0, 0.0);
    glRotatef(xrotate, 1.0, 0.0, 0.0);
    for (int i = 0; i < numBalls; i++)
        graphics(Balls[i]);
    graphics(box);
    glutSwapBuffers();
}



//! timer function,called every timingInterval seconds,handles the animation and signals threads to start computation

void timer(int timerParam)
{
  
    //signal to threads to start computation
    for (int i = 0; i < numThreads; i++)
    {
        pthread_mutex_lock(&childCondMutex[i]);
        startThreadComp[i] = true;
        pthread_cond_signal(&childConditional[i]);
        pthread_mutex_unlock(&childCondMutex[i]);
    }
    //wait till threads are done
    pthread_mutex_lock(&parentCondMutex);
    while(threadCount < numThreads)
    {
        pthread_cond_wait(&parentConditional, &parentCondMutex);
    }
    pthread_mutex_unlock(&parentCondMutex);
    //put threadCount to zero for next cycle
    threadCount = 0;
    //display
    glutPostRedisplay();
    glutTimerFunc(timingInterval, timer, 0);
}



void pausefunction(bool pause)
{
    if(pause)
    {
        for(int i = 0; i < numBalls; i++)
        {
            old_speed[i] = Balls[i].velocity;
            Balls[i].velocity.x = Balls[i].velocity.y = Balls[i].velocity.z = 0;
            
        }
    }
    else
    {
        for(int i = 0; i < numBalls; i++)
        {
            Balls[i].velocity = old_speed[i];
            old_speed[i].x = old_speed[i].y = old_speed[i].z = 0;
        }
    }
}

//! routine for handling button clicks and mouse clicks

void mouse(int button, int state, int a, int b)
{
    float x = ((float) a - ((float)old_width / 2)) * (1000.0 / ((float)old_width / 2));
    float y = -((float) b - ((float)old_height / 2)) * (1000.0 / ((float)old_height / 2));
    if(button == GLUT_LEFT_BUTTON)
    {
        if(x > increaseSpeedButton.xTopLeft && x < increaseSpeedButton.xTopLeft + increaseSpeedButton.width &&
           y < increaseSpeedButton.yTopLeft && y > increaseSpeedButton.yTopLeft - increaseSpeedButton.height)
        {
            if(state == GLUT_DOWN)
            {
                if(Balls[prevIndex].velocity.x < MaxVelocity && Balls[prevIndex].velocity.x > -MaxVelocity)
                    Balls[prevIndex].velocity.x *= 1.20;
                if(Balls[prevIndex].velocity.y < MaxVelocity && Balls[prevIndex].velocity.y > -MaxVelocity)
                    Balls[prevIndex].velocity.y *= 1.20;
                if(Balls[prevIndex].velocity.z < MaxVelocity && Balls[prevIndex].velocity.z > -MaxVelocity)
                    Balls[prevIndex].velocity.z *= 1.20;
                increaseSpeedButton.pressed = true;
            }
            else
                increaseSpeedButton.pressed = false;
        }
        
        
        
       
        
        
        
        
        if(x > decreaseSpeedButton.xTopLeft && x < decreaseSpeedButton.xTopLeft + decreaseSpeedButton.width &&
           y < decreaseSpeedButton.yTopLeft && y > decreaseSpeedButton.yTopLeft - decreaseSpeedButton.height)
        {
            if(state == GLUT_DOWN)
            {
                Balls[prevIndex].velocity.x /= 1.20;
                Balls[prevIndex].velocity.y /= 1.20;
                Balls[prevIndex].velocity.z /= 1.20;
                decreaseSpeedButton.pressed = true;
            }
            else
                decreaseSpeedButton.pressed = false;
        }
        if(x > gravityButton.xTopLeft && x < gravityButton.xTopLeft + gravityButton.width && y < gravityButton.yTopLeft && y > gravityButton.yTopLeft - gravityButton.height)
        {
            if(state == GLUT_DOWN)
            {
                enable_gravity = !enable_gravity;
                gravityButton.pressed = true;
                if (enable_gravity == true)
                {
                    char s[100] = "Disable Gravity";
                    gravityButton.setText(s);
                }
                else
                {
                    char s[100] = "Enable Gravity";
                    gravityButton.setText(s);
                }
            }
            else
                gravityButton.pressed = false;
        }
        if(x > pauseButton.xTopLeft && x < pauseButton.xTopLeft + pauseButton.width && y < pauseButton.yTopLeft && y > pauseButton.yTopLeft - pauseButton.height)
        {
            if(state == GLUT_DOWN)
            {
                togglePause = !togglePause;
                pauseButton.pressed = true;
                pausefunction(togglePause);
                if (togglePause == true)
                {
                    char s[100] = "Play";
                    pauseButton.setText(s);
                }
                else
                {
                    char s[100] = "Pause";
                    pauseButton.setText(s);
                }
            }
            else
                pauseButton.pressed = false;
        }

    }
    x = (((float)a - (old_width/2))/(old_width/2))*1000;
    y = -(((float)b - (old_height/2))/(old_height/2))*1000;
    float cosX = cos(xrotate*PI/180.0),cosY = cos(yrotate*PI/180.0),cosZ = cos(zrotate*PI/180.0);
    float sinX = sin(xrotate*PI/180.0),sinY = sin(yrotate*PI/180.0),sinZ = sin(zrotate*PI/180.0);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        for (int i = 0; i < numBalls; i++)
        {
            float x1 = Balls[i].centre.x*cosY*cosZ + Balls[i].centre.y*sinX*sinY*cosZ + Balls[i].centre.z*cosX*sinY*cosZ - Balls[i].centre.y*cosX*sinZ +Balls[i].centre.z*sinX*sinZ;
            float y1 = Balls[i].centre.x*cosY*sinZ + Balls[i].centre.y*sinX*sinY*sinZ + Balls[i].centre.z*cosX*sinY*sinZ + Balls[i].centre.y*cosX*cosZ - Balls[i].centre.z*sinX*cosZ;
            float d = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1));
            if(d < Balls[i].radius)
            {
                if(prevIndex < numBalls)
                {
                    Balls[prevIndex].red =  prevRed;
                    Balls[prevIndex].green = prevGreen;
                    Balls[prevIndex].blue = prevBlue;
                }
                prevIndex = i;
                prevRed = Balls[i].red;
                prevGreen = Balls[i].green;
                prevBlue = Balls[i].blue;
                Balls[i].red = Balls[i].green = Balls[i].blue = 1.0;
                #ifdef DEBUG
					cout<<x1<<" "<<y1<<"\n";
				#endif
            }
        }
    }
    glutPostRedisplay();
}



void dimensionWarp(bool is2D)
{
    if (is2D)
    {
        for (int i = 0; i < numBalls; i++)
        {
            float tmp = Balls[i].velocity.z;
            Balls[i].velocity.z = 0;
            Balls[i].centre.z = 0;
            old_z_coordinates[i] = tmp;
            
        }
    }
    else
    {
        for (int i =0; i < numBalls; ++i)
        {
            Balls[i].velocity.z = old_z_coordinates[i];
            old_z_coordinates[i] = 0.0;
        }
    }
    
   
}

//! handles keyboard inputs and is passed to glutKeyboardFunc

void keyboard(unsigned char c, int x, int y)
{
    if(prevIndex < numBalls)
    {
        if(c == 'w')
        {
            if(Balls[prevIndex].velocity.x < MaxVelocity && Balls[prevIndex].velocity.x > -MaxVelocity)
                Balls[prevIndex].velocity.x *= 1.20;
            if(Balls[prevIndex].velocity.y < MaxVelocity && Balls[prevIndex].velocity.y > -MaxVelocity)
                Balls[prevIndex].velocity.y *= 1.20;
            if(Balls[prevIndex].velocity.z < MaxVelocity && Balls[prevIndex].velocity.z > -MaxVelocity)
                Balls[prevIndex].velocity.z *= 1.20;
        }
        else if(c == 's')
        {
            Balls[prevIndex].velocity.x /= 1.20;
            Balls[prevIndex].velocity.y /= 1.20;
            Balls[prevIndex].velocity.z /= 1.20;
        }
        else if(c == 'd')
        {
            Balls[prevIndex].red =  prevRed;
            Balls[prevIndex].green = prevGreen;
            Balls[prevIndex].blue = prevBlue;
            prevIndex = prevIndex + 1;
            if(prevIndex == numBalls)
                prevIndex = 0;
            prevRed = Balls[prevIndex].red;
            prevGreen = Balls[prevIndex].green;
            prevBlue = Balls[prevIndex].blue;
            Balls[prevIndex].red = Balls[prevIndex].green = Balls[prevIndex].blue = 1.0;
        }
        else if(c == 'a')
        {
            Balls[prevIndex].red =  prevRed;
            Balls[prevIndex].green = prevGreen;
            Balls[prevIndex].blue = prevBlue;
            prevIndex = prevIndex - 1;
            if(prevIndex < 0)
                prevIndex = numBalls - 1;
            prevRed = Balls[prevIndex].red;
            prevGreen = Balls[prevIndex].green;
            prevBlue = Balls[prevIndex].blue;
            Balls[prevIndex].red = Balls[prevIndex].green = Balls[prevIndex].blue = 1.0;
        }
    }
    
    if (c == ' ')
    {
        togglePause = !togglePause;
        if (togglePause == true)
        {
            char s[100] = "Play";
            pauseButton.setText(s);
        }
        else
        {
            char s[100] = "Pause";
            pauseButton.setText(s);
        }
        pausefunction(togglePause);
    }
    if(c == 'g')
    {
        enable_gravity = !enable_gravity;
        if (enable_gravity == true)
        {
            char s[100] = "Disable Gravity";
            gravityButton.setText(s);
        }
        else
        {
            char s[100] = "Enable Gravity";
            gravityButton.setText(s);
        }
    }
    
    
    if (c == '2')
    {
        is2D = !is2D;
        dimensionWarp(is2D);
        if (is2D)
            xrotate = 0.0,yrotate = 0.0,zrotate = 0.0;
        
            
    }
    glutPostRedisplay();
}



//! routine for handling rotation of the cube
void rotateBoardKeyboardInput(int key, int x, int y)
{
    if (is2D) return;
    switch(key)
    {
        case GLUT_KEY_UP:
            xrotate += 3.0;
            break;
        case GLUT_KEY_DOWN:
            xrotate -= 3.0;
            break;
        case GLUT_KEY_LEFT:
            yrotate -= 3.0;
            break;
        case GLUT_KEY_RIGHT:
            yrotate +=3.0;
            break;
    }
    glutPostRedisplay();
}

float old_ratio = 1;

//! routine for handling reshaping of the window,and passed to glutReshapeFunc

void reshape (int w, int h)
{
    float ratio = float(w*h)/(old_height*old_width);
    if(ratio == old_ratio) return;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    for(int i=0;i<numBalls;i++)
        Balls[i].scale(ratio);
    old_ratio = ratio;
    old_height = h;
    old_width  = w;
}

int main(int argc, char **argv) {
    if(argc > 1)
    {
        numBalls = atoi(argv[1]);
        numThreads = numBalls;
    }
    if(argc > 2)
        numThreads = atoi(argv[2]);
    if(argc > 3)
        Cr = atof(argv[3]);
     if(Cr > 1.0) Cr = 1.0; 
     if(numThreads>numBalls)
     {
		numThreads = numBalls;
	 }
    startThreadComp.resize(numThreads, false);
    old_speed.resize(numBalls);
    glutInit(&argc, argv);
    glutInitWindowSize(650, 650);
    //initialisations to barrier, conditionals and mutexes
    vector<pthread_t> ballControlThreads(numThreads);
    childConditional.resize(numThreads);
    childCondMutex.resize(numThreads);
    messageQueues.resize(numThreads);
    for(int i = 0; i < numThreads; i++)
    {
        pthread_mutex_init(&childCondMutex[i], NULL);
        pthread_cond_init(&childConditional[i], NULL);
    }
    for (int i = 0; i < numThreads; i++)
    {
        int m = i;
        pthread_create(&ballControlThreads[i], NULL, ballControl, (void*) m);
    }
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Colliding Balls Animation");
    graphics();
    glutDisplayFunc(display);
    glutTimerFunc(timingInterval, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutSpecialFunc(rotateBoardKeyboardInput);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
