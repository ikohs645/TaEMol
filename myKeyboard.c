#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "./myGLUT.h"


static int keyx = 0;
static int keyy = 0;
int animationFlag = 0;
int displayFlag = 1;
int colorFlag=1;
char command[20];
int command_loop=1;

void myKeyboard(unsigned char key, int x, int y){
#ifdef KEYBOARD_FUNCTION 
	keyx = x;
	keyy = y;	
	myKeyboard0(key, x, y);
#endif
	
	glutPostRedisplay();	
}


void myKeyboard0(unsigned char key, int x, int y){
  
  switch(key) {
    
  case 'q': {
    exit(EXIT_FAILURE);
    break;
  }
  case 'Q': {
    exit(EXIT_FAILURE);
    break;
  }
  case 's':{
    animationFlag=animationFlag*-1+1;
    break;
  }      
  case 'x': {
    myCameraRotateX(1.0/M_PI);
    operationModeSet(xrotation);			
    break;
  }
  case 'y': {
    myCameraRotateY(1.0/M_PI);
    operationModeSet(yrotation);			
    break;
  }
  case 'z': {
    myCameraRotateZ(1.0/M_PI);
    operationModeSet(zrotation);			
    break;
  }
  case 'r': {
    myInit();
    myDisplay();
    break;
  }
  case 'a': {
    fprintf(stdout,"Comannd mode... ('help' shows you command list)\n->");
    command_loop=1;
    
    while(command_loop==1){
      fscanf(stdin,"%s",command);
      
      if(strncmp(command,"size",4)==0){
	fprintf(stdout,"Change size scale:");
	scanf("%e",&scale);
	fprintf(stdout,"->");
      }
      else if(strncmp(command,"backcolor",9)==0){
	fprintf(stdout,"Parameters(0.0~1.0)...\nRed:");
	scanf("%e",&backColor[0]);
	fprintf(stdout,"Geeen:");
	scanf("%e",&backColor[1]);
	fprintf(stdout,"Blue:");
	scanf("%e",&backColor[2]);
	fprintf(stdout,"->");
      }
      else if(strncmp(command,"help",4)==0){
	fprintf(stdout,"\n***Command list***\n");
	fprintf(stdout,"[size]: Change the sizes of all atoms by scale\n");
	fprintf(stdout,"[backcolor]: Chage backcolor. Set color parameters(RGB).\n");
	fprintf(stdout,"[quit]: Quit command mode.\n");
	fprintf(stdout,"[help]: Show you command list.\n\n->");
      }
      else if(strncmp(command,"quit",4)==0){
	command_loop=0;
	break;
      }
      else{
	fprintf(stdout,"Your order dose not exsist!\n");
	fprintf(stdout,"->");
      }
      myDisplay();      
    }
    fprintf(stdout,"\nFinished command mode. Please return to TaEMol.\n\n");
    break;
  }    
  case '1':{
    displayFlag=1;
    myDisplay();
    break;
  }
  case '2':{
    displayFlag=2;
    myDisplay();
    break;
  }
  case '3':{
    colorFlag=1;
    myDisplay();
    break;
  }
  case '4':{
    colorFlag=2;
    myDisplay();
    break;
  }
  case '5':{
    colorFlag=3;
    myDisplay();
    break;
  }
  case '6':{
    colorFlag=4;
    myDisplay();
    break;
  }
  case '7':{
    colorFlag=5;
    myDisplay();
    break;
  }
  case '8':{
    colorFlag=6;
    myDisplay();
    break;
  }    
  default: {
    break;
  }
  }	
  
}
