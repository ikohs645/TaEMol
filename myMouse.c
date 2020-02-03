#include<math.h>
#include "./myGLUT.h"
#include "myGLUT.h"

static int startx = 0;
static int starty = 0;
static int endx = 0;
static int endy = 0;
static int pressedButton = -1;
static int shift=0;

void myMouse(int button, int state, int x, int y){
#ifdef MOUSE_FUNCTION
  switch(state) {
  case  GLUT_DOWN: { 
			pressedButton = button;
			startx = x;
			starty = y;
			switch(button) {
			case GLUT_LEFT_BUTTON:{
			  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT){
			    shift=1;
			  }
			  break;
				}	
			case GLUT_RIGHT_BUTTON:{
			  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT){
			    shift=1;
			  }			  
			  break;
				}
			case GLUT_MIDDLE_BUTTON:{
			  break;
			}	
			}
			break;
  }
  case GLUT_UP: { 
    endx = x;
    endy = y;
			pressedButton = -1;
			switch(button) {
			case GLUT_LEFT_BUTTON: {

			  shift=0;		  

			  break;
			}	
			case GLUT_RIGHT_BUTTON: {
			  if(glutGetModifiers() & GLUT_ACTIVE_SHIFT){
			    shift=0;
			  }			  
			  break;
			}
			case GLUT_MIDDLE_BUTTON: {
			  break;
			}	
			}
			break;
  }
  }
  
#endif	

	glutPostRedisplay();
}


void myMouseMotion(int x, int y){
#ifdef MOTION_FUNCTION
  int delx, dely;
  
  delx = x - startx;
  dely = y - starty;
  
  switch(pressedButton) {
  case GLUT_MIDDLE_BUTTON: {		
    myCameraTranslateX(delx/20.0);
    myCameraTranslateY(dely/20.0);
    startx =  x;
    starty =  y;
    break;
  }
  case GLUT_LEFT_BUTTON: {      
    if(shift==1){
      Zoom(dely*1.0);
    }
    else{
    myCameraRotateY(-delx/M_PI/100.0);	
    myCameraRotateX(-dely/M_PI/100.0);	
    }
    startx =  x;
    starty =  y;
    break;
  }
  case GLUT_RIGHT_BUTTON: {
    if(shift==1){
    myCameraRotateZ(delx/M_PI/100.0);
    }
    startx = x;
    starty = y;
    break;
  }
  }
  
  
#endif
  
  glutPostRedisplay();
}


void
myMousePassiveMotion(int x, int y)
{

	glutPostRedisplay();
}
