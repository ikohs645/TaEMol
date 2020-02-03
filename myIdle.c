#include <stdio.h>
#include <math.h>
#include "./myGLUT.h"
#include "myGUI.h"

GLdouble theta=0.0;
GLdouble turn=1.0;

void myIdle(void){

  
  if(animationFlag==1){
      if(theta==0.0){
	turn=1.0;
      }
      else if(theta==30.0){
	turn=-1.0;
      }
	myCameraRotateY(turn*M_PI/180.0);
	glutPostRedisplay();
	theta+=turn/2.0;
    }
  }
