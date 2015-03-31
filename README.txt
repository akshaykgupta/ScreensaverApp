%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Authors: Akshay Kumar Gupta	Barun Patra	J Shikhar Murty
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
INTRODUCTION:
The purpose of this application is to create an interactive screen saver, which simulates collisions in 2D and 3D, allowing users to increase/decrease speed, pause/resume and enable/disable effects gravity, using one to one thread communication.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
COMPILATION AND EXECUTION: 
Compiling the Documentation:
	“make Document” in the Final folder
Compiling the Project:
	“make -f makefile execute NUM_BALLS=n“ /*To run the project with number of Balls =n*/
	“make -f makefile execute NUM_BALLS=m nNUM_THREADS=n” /*num-threads =n and num_balls = m*/
	“make -f makefile execute NUM_BALLS=m nNUM_THREADS=n COR=s” /*num-threads =n and num_balls = m and elasticity =s*/
	“make -f makefile debug” /*To generate a gdb supported version of executable file in the EXE folder(DEBUG).*/
	“make -f makefile DEBUG” /*To debug ball with printf commands*/
	The default values of NUM_BALLS = 100,NUM_THREADS=50,COR=1.0
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
REQUIREMENTS:
	Libraries: 
	1. openGL
	2. glut or free glut
	3. glui
	4. pthread
	The version of g++ required to compile c++11
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
USER INTERFACE:
The GUI involves the following: 
KEYBOARD CONTROLS:
The following is a list of the KeyBoard functions available:
	• Increase/Decrease Speed: w and s allow the user to increase and decrease the speed of a selected Ball respectively.
	• Toggle Selection: a and d allow the user to toggle between selected Balls.
	• Enable/Disable Gravity: g allows the user to enable/disable the effects of gravity within the Box.
	• Pause/Play: Space Bar allows the user to pause the simulation, and resume the same, as per his convenience.
	• View Selection: The Up, Down, Left and Right arrow keys allow the user to change the view of the camera, allowing the user to view the Box, and the Balls from different angles,while facilitating the selection of Balls.
	• 3D-2D-3D: The 2 key is used to toggle between 2D and 3D modes. However, in the 2D mode, the rotation buttons are disabled.
MOUSE CONTROLS:
	• Selection: Clicking on a Ball would select the Ball. In case a ball to be selected is hidden behind another, rotating the box and then selecting the Ball would achieve the same.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ACKNOWLGEMENTS:
	I would like to thank Haroun Habeeb for his exceptionally complicated explanation of the OpenGL nuances, without whose help, either the project would have been made two weeks back or not at all. 
	I would also like to thank Kabir Chhabra and Harman Kumar, Kartikeya Gupta, Prateek Verma, Nikhil Chaturvedi and Noman Ahmed with various concepts.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
BIBLIOGRAPHY:
 	gamedev.net
	stackoverflow.net
	OpenGL documentation 
	bogotobogo.net/cplusplus/*
	OpenGL.sourceforge.net
	wolframalpha
	wikipedia
	 
