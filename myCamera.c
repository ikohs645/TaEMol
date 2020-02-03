#include <stdio.h>
#include <math.h>
#include "./myGLUT.h"
#include "./PDB.h"

/*カメラ情報*/
cameraInfo __camera = {
	30.0,             /* Fovy: 視野角 [degree]*/ 
	1.0,              /* Aspect: アスペクト比 */ 
	0.1,              /* ClipNear(目に近い側のクリッピング面) 目の位置からの奥行き(z軸負の向き)への距離 */
	300.0,            /* ClipFar(目から遠い側のクリッピング面) */
	{0.0, 0.0, 0.0}, /* Eye: 目の位置: (eyex, eyey, eyez) */
	{0.0,0.0,0.0},  /* Centre: 注視点: (centerx, centrey, centrez) */
	{0.0,1.0,0.0}	  /* Up:  目の上向き: (upx, upy, upz) */
};

cameraInfo* getMyCamera(){
  
	return &__camera;
}

void upCalc(){
	GLdouble* up     = __camera.Up;
	GLdouble norm;

	int i;



	norm = up[0]*up[0] + up[1]*up[1] + up[2]*up[2];
	if(0 == norm) { 
		up[0] = 0;	
		up[1] = 1;	
		up[2] = 0;	
	} else {
		norm = sqrt(norm);
		for(i=0; i<3; i++) {
			up[i] /= norm; 
		}
	}
}


void myCameraRotateX(GLdouble angle){
	GLdouble  dummy[3]; 					
	GLdouble  norm[3];
	GLfloat* light; 
	int i;
	double length;

	upCalc();

	dummy[0] = __camera.Eye[0]-(GLdouble)pdb.Center.x;
	dummy[1] = __camera.Eye[1]-(GLdouble)pdb.Center.y;
	dummy[2] = __camera.Eye[2]-(GLdouble)pdb.Center.z;

	norm[0] = __camera.Up[1]*dummy[2] - dummy[1]*__camera.Up[2];	
	norm[1] = __camera.Up[2]*dummy[0] - dummy[2]*__camera.Up[0];	
	norm[2] = __camera.Up[0]*dummy[1] - dummy[0]*__camera.Up[1];	
	
	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;
	
	__camera.Eye[0] = (GLdouble)pdb.Center.x  
	  + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        * dummy[0]
	  + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))* dummy[1]
       	  + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))* dummy[2];
	__camera.Eye[1] = (GLdouble)pdb.Center.y
	  + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))* dummy[0]
	  + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        * dummy[1]
	  + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))* dummy[2];
	__camera.Eye[2] = (GLdouble)pdb.Center.z
	  + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))* dummy[0]
	  + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))* dummy[1]
	  + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        * dummy[2];

	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];	
	dummy[2] = __camera.Up[2];
      	__camera.Up[0] =
	                +(norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]  
	                + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =
	                + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =
	                +(norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
	                + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];


	dummy[0] = __camera.Centre[0]-(GLdouble)pdb.Center.x;
	dummy[1] = __camera.Centre[1]-(GLdouble)pdb.Center.y;
	dummy[2] = __camera.Centre[2]-(GLdouble)pdb.Center.z;
	
	__camera.Centre[0] = (GLdouble)pdb.Center.x  
	  + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        * dummy[0]
	  + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))* dummy[1]
       	  + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))* dummy[2];
	__camera.Centre[1] = (GLdouble)pdb.Center.y
	  + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))* dummy[0]
	  + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        * dummy[1]
	  + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))* dummy[2];
	__camera.Centre[2] = (GLdouble)pdb.Center.z
	  + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))* dummy[0]
	  + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))* dummy[1]
	  + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        * dummy[2];
	
	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] = light[0] - (GLdouble)pdb.Center.x;
		dummy[1] = light[1] - (GLdouble)pdb.Center.y;
		dummy[2] = light[2] - (GLdouble)pdb.Center.z;

		light[0] = (GLdouble)pdb.Center.x
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = (GLdouble)pdb.Center.y
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = (GLdouble)pdb.Center.z
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	
	glFlush();
}


void myCameraRotateY(GLdouble angle){
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
 
	upCalc();
	
	dummy[0] = __camera.Eye[0]-(GLdouble)pdb.Center.x;
	dummy[1] = __camera.Eye[1]-(GLdouble)pdb.Center.y;
	dummy[2] = __camera.Eye[2]-(GLdouble)pdb.Center.z;
 
	norm[0] = __camera.Up[0];	
	norm[1] = __camera.Up[1];	
	norm[2] = __camera.Up[2];
	
	__camera.Eye[0] = (GLdouble)pdb.Center.x
			+ (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Eye[1] = (GLdouble)pdb.Center.y
			+ (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Eye[2] = (GLdouble)pdb.Center.z
			+ (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	dummy[0] = __camera.Centre[0]-(GLdouble)pdb.Center.x;
	dummy[1] = __camera.Centre[1]-(GLdouble)pdb.Center.y;
	dummy[2] = __camera.Centre[2]-(GLdouble)pdb.Center.z;
	
	__camera.Centre[0] = (GLdouble)pdb.Center.x  
	  + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        * dummy[0]
	  + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))* dummy[1]
       	  + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))* dummy[2];
	__camera.Centre[1] = (GLdouble)pdb.Center.y
	  + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))* dummy[0]
	  + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        * dummy[1]
	  + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))* dummy[2];
	__camera.Centre[2] = (GLdouble)pdb.Center.z
	  + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))* dummy[0]
	  + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))* dummy[1]
	  + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        * dummy[2];
	
	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	
 
		dummy[0] = light[0] - (GLdouble)pdb.Center.x;
		dummy[1] = light[1] - (GLdouble)pdb.Center.y;
		dummy[2] = light[2] - (GLdouble)pdb.Center.z;
 
		light[0] = (GLdouble)pdb.Center.x
                        + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                        + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                        + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = (GLdouble)pdb.Center.y
                        + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                        + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                        + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = (GLdouble)pdb.Center.z
                        + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                        + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                        + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	
	glFlush();
}


void myCameraRotateZ(GLdouble angle){
	GLdouble  dummy[3];							
	GLdouble  norm[3];							
	GLfloat* light; 
	int i;
	double length;

	norm[0] = __camera.Eye[0]-(GLdouble)pdb.Center.x;
	norm[1] = __camera.Eye[1]-(GLdouble)pdb.Center.y;
	norm[2] = __camera.Eye[2]-(GLdouble)pdb.Center.z;
	length = sqrt(norm[0]*norm[0]+norm[1]*norm[1]+norm[2]*norm[2]);	
	norm[0] /= length;
	norm[1] /= length;
	norm[2] /= length;

	dummy[0] = __camera.Centre[0]-(GLdouble)pdb.Center.x;
	dummy[1] = __camera.Centre[1]-(GLdouble)pdb.Center.y;
	dummy[2] = __camera.Centre[2]-(GLdouble)pdb.Center.z;
	
	__camera.Centre[0] = (GLdouble)pdb.Center.x  
	  + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        * dummy[0]
	  + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))* dummy[1]
       	  + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))* dummy[2];
	__camera.Centre[1] = (GLdouble)pdb.Center.y
	  + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))* dummy[0]
	  + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        * dummy[1]
	  + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))* dummy[2];
	__camera.Centre[2] = (GLdouble)pdb.Center.z
	  + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))* dummy[0]
	  + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))* dummy[1]
	  + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        * dummy[2];
	
	dummy[0] = __camera.Up[0];
	dummy[1] = __camera.Up[1];
	dummy[2] = __camera.Up[2];

	__camera.Up[0] =  (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
			+ (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
			+ (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
	__camera.Up[1] =  (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
			+ (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
			+ (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
	__camera.Up[2] =  (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
			+ (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
			+ (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];

	length = sqrt(__camera.Up[0]*__camera.Up[0]+__camera.Up[1]*__camera.Up[1]+__camera.Up[2]*__camera.Up[2]);	
	__camera.Up[0] /= length;
	__camera.Up[1] /= length;
	__camera.Up[2] /= length;


	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] = light[0] - __camera.Centre[0];
		dummy[1] = light[1] - __camera.Centre[1];
		dummy[2] = light[2] - __camera.Centre[2];

		light[0] = (GLdouble)pdb.Center.x
                      + (norm[0]*norm[0]*(1-cos(angle))+cos(angle))        *dummy[0]
                      + (norm[0]*norm[1]*(1-cos(angle))-norm[2]*sin(angle))*dummy[1]
                      + (norm[0]*norm[2]*(1-cos(angle))+norm[1]*sin(angle))*dummy[2];
		light[1] = (GLdouble)pdb.Center.y
                      + (norm[1]*norm[0]*(1-cos(angle))+norm[2]*sin(angle))*dummy[0]
                      + (norm[1]*norm[1]*(1-cos(angle))+cos(angle))        *dummy[1]
                      + (norm[1]*norm[2]*(1-cos(angle))-norm[0]*sin(angle))*dummy[2];
		light[2] = (GLdouble)pdb.Center.z
                      + (norm[2]*norm[0]*(1-cos(angle))-norm[1]*sin(angle))*dummy[0]
                      + (norm[2]*norm[1]*(1-cos(angle))+norm[0]*sin(angle))*dummy[1]
                      + (norm[2]*norm[2]*(1-cos(angle))+cos(angle))        *dummy[2];
	}
	}
	glFlush();
}


void myCameraTranslateX(GLdouble pan){
  
  GLdouble F[3];
  GLdouble S[3];
  GLdouble length;
  int i;
  
  upCalc();
  for(i=0;i<3;++i){
    F[i]=(__camera.Centre[i]-__camera.Eye[i]);
  }
  
  S[0]=F[1]*__camera.Up[2]-F[2]*__camera.Up[1];
  S[1]=F[2]*__camera.Up[0]-F[0]*__camera.Up[2];
  S[2]=F[0]*__camera.Up[1]-F[1]*__camera.Up[0];

  length=sqrt(S[0]*S[0]+S[1]*S[1]+S[2]*S[2]);
  S[0]/=length;
  S[1]/=length;
  S[2]/=length;
  
  for(i=0;i<3;++i){
    __camera.Centre[i] -= pan*S[i];
    __camera.Eye[i] -= pan*S[i];
  }
  
  upCalc();
  
  glFlush();
}


void myCameraTranslateY(GLdouble pan){

  int i;

  upCalc();
  for(i=0;i<3;++i){
    __camera.Centre[i] += pan*__camera.Up[i];
    __camera.Eye[i] += pan*__camera.Up[i];
  }
	glFlush();
}


void Zoom(GLdouble dist){
  
  GLdouble F[3];
  GLdouble length;
  int i;
  
  upCalc();
  for(i=0;i<3;++i){
    F[i]=(__camera.Centre[i]-__camera.Eye[i]);
  }

  length=sqrt(F[0]*F[0]+F[1]*F[1]+F[2]*F[2]);
  if(length<(pdb.maxRadius/10.0)){
    if(dist>0){
      dist=0.0;
    }
  }
  F[0]/=length;
  F[1]/=length;
  F[2]/=length;

  if((__camera.ClipFar+dist)<__camera.ClipNear){
    dist=0;
  }

  for(i=0;i<3;++i){
    __camera.Centre[i] += dist*F[i];
    __camera.Eye[i] += dist*F[i];

  glFlush();
  }
}





void myCameraRotateXX(GLdouble angle){
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
      
	dummy[1] = (__camera.Eye[1]-__camera.Centre[1])*cos(angle) - (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = (__camera.Eye[1]-__camera.Centre[1])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[1] = dummy[1] + __camera.Centre[1];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];


	__camera.Up[1] = __camera.Up[1]*cos(angle) - __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = __camera.Up[1]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] =  light[0];
		dummy[1] =  (light[1]-__camera.Centre[1])*cos(angle) - (light[2]-__camera.Centre[2])*sin(angle);
		dummy[2] =  (light[1]-__camera.Centre[1])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0];
		light[1] = dummy[1]+__camera.Centre[1];
		light[2] = dummy[2]+__camera.Centre[2];
	}
	}
	glFlush();
}


void myCameraRotateYY(GLdouble angle){
	GLdouble  dummy[3];							
	GLfloat* light; 
	int i;
		
	dummy[0] =  (__camera.Eye[0]-__camera.Centre[0])*cos(angle) + (__camera.Eye[2]-__camera.Centre[2])*sin(angle) ; 
	dummy[2] = -(__camera.Eye[0]-__camera.Centre[0])*sin(angle) + (__camera.Eye[2]-__camera.Centre[2])*cos(angle) ; 

	__camera.Eye[0] = dummy[0] + __camera.Centre[0];
	__camera.Eye[2] = dummy[2] + __camera.Centre[2];

	__camera.Up[0] =  __camera.Up[0]*cos(angle) + __camera.Up[2]*sin(angle) ; 
	__camera.Up[2] = -__camera.Up[0]*sin(angle) + __camera.Up[2]*cos(angle) ; 

	upCalc();

	
	if(lightControl) {
	for(i=0; i<2; i++) {
		light = getMyLightPos(i);	

		dummy[0] =  (light[0]-__camera.Centre[0])*cos(angle) + (light[2]-__camera.Centre[2])*sin(angle);
		dummy[1] =  (light[1]-__camera.Centre[1]);
		dummy[2] = -(light[0]-__camera.Centre[0])*sin(angle) + (light[2]-__camera.Centre[2])*cos(angle);

		light[0] = dummy[0] + __camera.Centre[0];
		light[1] = dummy[1] + __camera.Centre[1];
		light[2] = dummy[2] + __camera.Centre[2];
	}
	}
	glFlush();
}

