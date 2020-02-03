#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "./myGLUT.h"
#include "./PDB.h"


static GLuint    displayList1          = 1;
static GLuint    displayList2          = 2;
static GLboolean needDisplayListMaking = GL_TRUE;

static GLfloat materialColor[4];
static GLfloat materialSpecular[4] = {0.2, 0.2, 0.2, 1.0 } ; /*ハイライトの強さ*/
static GLfloat materialAmbient[4] = {0.2, 0.2, 0.2, 1.0 } ; /*全体の明るさ*/

recordPDB* p;
recordPDB* p2;
recordPDB* p3;
static Coord* __points;
float scale=1.0;
float backColor[]={0.1,0.1,0.1};

GLfloat gray[]={0.5,0.5,0.5,1.0};
GLfloat red[]={1.0,0.0,0.0,1.0};
GLfloat blue[]={0.0,0.0,1.0,1.0};
GLfloat white[]={1.0,1.0,1.0,1.0};
GLfloat yellow[]={1.0,1.0,0.0,1.0};
GLfloat g_yellow[]={0.5,1.0,0.0,1.0};


void __getColorRGB(GLfloat color[3], GLdouble index, GLdouble min, GLdouble max){
	GLdouble half = (max+min)/2.0;

	if(index<half) {
	        color[0] = 0;
		color[1] = (index - min  )/(half-min);
		color[2] = (half  - index)/(half-min);
	} else {
		color[0] = (index - half )/(max - half);
		color[1] = (max   - index)/(max - half);
		color[2] = 0;
	}
}



void myDisplayListMake1(void){
	int i;
	GLfloat color[3]; 	
       	GLdouble radius=1.0;
	GLint    slices=20;      
	GLint    stacks=10;
	float dist;
	float temp_min=1000.0;
	float temp_Max=-1000.0;
	float occu_min=1000.0;
	float occu_Max=-1000.0;
	char last_res[3];
	int res_kinds=0;
	int res_index=0;
	__points=(Coord*)malloc(sizeof(Coord)*pdb.numAtom); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
       	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);     /* 物質の拡散光の色の設定  */
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
	materialColor[3] = 1.0;

       	p=(recordPDB*)malloc(sizeof(recordPDB));
	p=pdb.top;
	strncpy(last_res,p->atom.resName,3);
	
	for(i=0;i<pdb.numAtom;++i){
	  __points[i].x = (GLfloat)p->atom.x;
	  __points[i].y = (GLfloat)p->atom.y;
	  __points[i].z = (GLfloat)p->atom.z;
	  
	  if(temp_Max<p->atom.tempFactor){
	    temp_Max=p->atom.tempFactor;
	  }
	  if(temp_min>p->atom.tempFactor){
	    temp_min=p->atom.tempFactor;
	  }

	  if(occu_Max<p->atom.occupancy){
	    occu_Max=p->atom.occupancy;
	  }
	  if(occu_min>p->atom.occupancy){
	    occu_min=p->atom.occupancy;
	  }	  

	  if(strncmp(last_res,p->atom.resName,3)!=0){
	    ++res_kinds;	
	    strncpy(last_res,p->atom.resName,3);
	  }

	  p=p->nextAtom;
	}


	glNewList(displayList1, GL_COMPILE);
	
        	p=pdb.top;
		for(i=0; i<pdb.numAtom; i++) {

		  glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular); /* 物質の鏡面反射の色の設定 */
		  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);             /* 物質の鏡面指数 */
		  glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);   /* 物質の環境光の色の設定 */
		 
			if(strncmp(p->atom.element,"C ",3)==0){
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
			  radius=1.7;		 
			}
			else if(strncmp(p->atom.element,"O ",3)==0){
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			  radius=1.52;
			}
			else if(strncmp(p->atom.element,"N ",3)==0){
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
			  radius=1.55;
			}
			else if(strncmp(p->atom.element,"H ",3)==0){
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
			  radius=1.2;
			}
			else if(strncmp(p->atom.element,"P ",3)==0){
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
			  radius=1.8;    
			}
			else{
			  glMaterialfv(GL_FRONT, GL_DIFFUSE, g_yellow);
			  radius=1.4;
			}

		  if(colorFlag!=1){
		    if(colorFlag==2){
		      dist=sqrt(powf(p->atom.x-pdb.Center.x,2.0)
				+powf(p->atom.y-pdb.Center.y,2.0)
				+powf(p->atom.z-pdb.Center.z,2.0));
		      
		      __getColorRGB(color, dist, 0.0, pdb.maxRadius);
		    }
		    if(colorFlag==3){
		      __getColorRGB(color, p->atom.tempFactor, temp_min, temp_Max);
		    }	
		    if(colorFlag==4){
		      __getColorRGB(color, i, 0.0, pdb.numAtom-1); 		      
		    }
		    if(colorFlag==5){
		      __getColorRGB(color, p->atom.occupancy, occu_min, occu_Max);
		    }
		    if(colorFlag==6){
		      if(strncmp(last_res,p->atom.resName,3)!=0){
			__getColorRGB(color,res_kinds-res_index,0,res_kinds);
			strncpy(last_res,p->atom.resName,3);
			++res_index;
		      }
		    }
		  glColor3f(color[0], color[1], color[2]);              
			     	   materialColor[0] = color[0];
				   materialColor[1] = color[1];  
				   materialColor[2] = color[2];	
		  		   materialColor[3] = 1.0;
				   glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColor);
		  }			
			
			/* 球面の創出 */
			glPushMatrix();
			glTranslatef(__points[i].x, __points[i].y, __points[i].z); 		
			glutSolidSphere(radius*scale, slices, stacks);
			glPopMatrix();

			p=p->nextAtom;
			
		}

		
	glEndList();
	
}

void myDisplayListMake2(void){
  int i;
  float temp_min=1000.0;
  float temp_Max=-1000.0;
  
  p2=(recordPDB*)malloc(sizeof(recordPDB));
  p2=pdb.topCA;
  
  for(i=0;i<pdb.numCA;++i){
    __points[i].x = (GLfloat)p2->atom.x;
    __points[i].y = (GLfloat)p2->atom.y;
    __points[i].z = (GLfloat)p2->atom.z;
    
    if(temp_Max<p->atom.tempFactor){
      temp_Max=p->atom.tempFactor;
    }
    if(temp_min>p->atom.tempFactor){
      temp_min=p->atom.tempFactor;
    }
    
    p2=p2->nextCA;
  }
  
  glNewList(displayList2, GL_COMPILE);
  
  glPushMatrix();
  glLineWidth(5);
  glBegin(GL_LINE_STRIP);
  
  p2=pdb.topCA;
  for(i=0; i<pdb.numCA-1; i++) {
    if(strncmp(p2->atom.resName,"ARG",3)==0 ||
       strncmp(p2->atom.resName,"HIS",3)==0 ||
       strncmp(p2->atom.resName,"LYS",3)==0){
      glColor3f(1.0,0.0,0.0);			  
    }
    else if(strncmp(p2->atom.resName,"ASP",3)==0 ||
	    strncmp(p2->atom.resName,"GLU",3)==0 ||
	    strncmp(p2->atom.resName,"TYR",3)==0 ||
	    strncmp(p2->atom.resName,"CYS",3)==0){
      glColor3f(0.0,0.0,1.0);
    }
    else if(strncmp(p2->atom.resName,"SER",3)==0 ||
	    strncmp(p2->atom.resName,"THR",3)==0 ||
	    strncmp(p2->atom.resName,"ASP",3)==0 ||
	    strncmp(p2->atom.resName,"GLN",3)==0){
      glColor3f(0.5,1.0,0.0);
    }
    else{
      glColor3f(0.5,0.5,0.5);
    }
    
    glLineWidth(10.0);
    glVertex3f(__points[i].x, __points[i].y, __points[i].z);
    glVertex3f(__points[i+1].x, __points[i+1].y, __points[i+1].z);
    
    p2=p2->nextCA;
  }
  
  glEnd();
  glPopMatrix();
  glEndList();
  
  
}

void myDisplayListMake(void){
  
  myDisplayListMake1();
  myDisplayListMake2();
}


void myDisplay(void){
  
  cameraInfo* camera;
  
  glClearColor(backColor[0],backColor[1],backColor[2],0.0);
  
  /* カメラ位置の設定 */
  camera = getMyCamera();
  glMatrixMode(GL_PROJECTION);            
  glLoadIdentity();                    
  myLightSet();
  
  //　カメラの視線の指定
  gluPerspective(camera->Fovy, camera->Aspect, camera->ClipNear, camera->ClipFar);   
    gluLookAt(camera->Eye[0], camera->Eye[1], camera->Eye[2],
	      camera->Centre[0], camera->Centre[1], camera->Centre[2],
	      camera->Up[0], camera->Up[1], camera->Up[2]);
    
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();                        
    myLightSet();
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(GL_TRUE == needDisplayListMaking) {
	  myDisplayListMake();
	}
	
	glPushMatrix();
	
	if(displayFlag==1){
	  glPushMatrix();
	  getMyLightPos(1);
	  glCallList(displayList1);
	  glEnable(GL_LIGHTING);
	  glPopMatrix();
	}
	if(displayFlag==2){
	  glPushMatrix();
	  glDisable(GL_LIGHTING);
	  glCallList(displayList2);
	  glEnable(GL_LIGHTING);
	  glPopMatrix();
	}
	
	glPopMatrix();
	
	glutSwapBuffers();
}

