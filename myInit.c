#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./myTest.h"
#include "./myGLUT.h"
#include "./PDB.h"

cameraInfo* camera;

void
myInit(void)
{
	myLightSet();
	
	glShadeModel(GL_FLAT); 
		/* シェーディングモデルを設定する： 
			GL_FLAT(フラットシェーディング) 
				or 
			GL_SMOOTH(スムーズシェーディング・グローシェーディング)
		*/
	glDepthFunc(GL_LEQUAL);
		/*  デプスを計算するための比較関数の定義
			GL_LEQUAL: Less than or equal	
		*/
	glEnable(GL_DEPTH_TEST); 
		/*  デプステストを有効にする。 */


	glEnable(GL_CULL_FACE);     	// カリングを有効にする	
	glEnable(GL_BACK);			// 裏側をカリング
	glCullFace(GL_BACK);
	
	backColor[0]=0.1;
	backColor[1]=0.1;
	backColor[2]=0.1;
	glClearColor(backColor[0],backColor[1],backColor[2],0.0); /* 背景色の初期化　*/
	
	/*分子全体が視 垂台に入るように*/
	camera=getMyCamera();
	
	camera->Up[0]=0.0;
	camera->Up[1]=1.0;
	camera->Up[2]=0.0;
	
       	camera->Eye[0]=(GLdouble)(pdb.Center.x);
	camera->Eye[1]=(GLdouble)(pdb.Center.y);
       	camera->Eye[2]=(GLdouble)(pdb.Center.z+pdb.maxRadius*4);
        camera->ClipFar=pdb.maxRadius+1000;
	/*最初は分子中心を注視*/
	camera->Centre[0]=(GLdouble)pdb.Center.x;
	camera->Centre[1]=(GLdouble)pdb.Center.y;
	camera->Centre[2]=(GLdouble)pdb.Center.z;
}
