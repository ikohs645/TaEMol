#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "PDB.h"

int arrayPDBRead(FILE* fpt,arrayPDB* pdb){
  
  char* readline;
  char* str;
  int i=0;
  
  pdb->numAtom=0;
  pdb->numCAAtom=0;
  readline=(char*)malloc(sizeof(char)*80);
  
  while(fgets(readline,80,fpt)!=NULL){
    if(strncmp(readline,"ATOM  ",6)==0){
      ++pdb->numAtom;
      if(strncmp(readline+12," CA ",4)==0){
	++pdb->numCAAtom;
      }
    }    
  }
  
  
  pdb->CA=(Atom*)malloc(sizeof(Atom)*(pdb->numCAAtom));
  
  if(fseek(fpt,0,SEEK_SET)!=0){
    printf("Fail to return to head of the file!!\n");
    exit(1);
  }
  
  str=(char*)malloc(sizeof(char)*80);
  
  while(fgets(readline,80,fpt)!=NULL){
    if(strncmp(readline,"ATOM  ",6)==0){
      if(strncmp(readline+12," CA ",4)==0){
	pdb->CA[i].x=atof(strncpy(str,(readline+30),8));
	pdb->CA[i].y=atof(strncpy(str,(readline+38),8));
	pdb->CA[i].z=atof(strncpy(str,(readline+46),8));
	++i;
      }
    }
  }
  free(readline);
return 0;
}

int pdbRead(FILE* fpt,PDB* pdb){
  
  char* readline;
  char* str;
  int i=0;
  recordPDB* p=NULL;
  recordPDB* p_ca=NULL;
  
  
  pdb->numAtom=0;
  pdb->numCA=0;
  readline=(char*)malloc(sizeof(char)*80);
  str=(char*)malloc(sizeof(char)*80);
  pdb->top=(recordPDB*)malloc(sizeof(recordPDB));
  pdb->topCA=(recordPDB*)malloc(sizeof(recordPDB));
  p=(pdb->current=(recordPDB*)malloc(sizeof(recordPDB)));
  p_ca=(pdb->currentCA=(recordPDB*)malloc(sizeof(recordPDB)));
  p=pdb->top;
  p_ca=pdb->topCA;
  
  while(fgets(readline,80,fpt)!=NULL){
    if(strncmp(readline,"ATOM  ",6)==0){  // if "ATOM  "
      ++pdb->numAtom;
      p->atom.x=atof(strncpy(str,readline+30,8));//x
      p->atom.y=atof(strncpy(str,readline+38,8));//y
      p->atom.z=atof(strncpy(str,readline+46,8));//z
      p->nextCA=(recordPDB*)malloc(sizeof(recordPDB));
      //  p->nextCA=NULL;
      strncpy(p->atom.resName,readline+17,3);//resName
      strncpy(p->atom.atomName,readline+12,4);//atomName
      strncpy(p->atom.element,readline+77,3);//element
      p->atom.resNumber=atoi(strncpy(str,readline+25,4));//resNumber
      p->atom.tempFactor=atof(strncpy(str,readline+60,6));//tempFactor
      p->atom.occupancy=atof(strncpy(str,readline+54,6));//occupancy

   //         printf("%d: %s %s %s %d %e %e\n",pdb->numAtom,p->atom.resName,p->atom.atomName,p->atom.element,p->atom.resNumber,p->atom.occupancy,p->atom.tempFactor);//debug
      
      if(strncmp(readline+12," CA ",4)==0){ // first " CA "
	++pdb->numCA;
	p_ca->atom.x=atof(strncpy(str,readline+30,8));
	p_ca->atom.y=atof(strncpy(str,readline+38,8));
	p_ca->atom.z=atof(strncpy(str,readline+46,8));
	p_ca->nextAtom=(p_ca->nextCA=(recordPDB*)malloc(sizeof(recordPDB)));
	strncpy(p_ca->atom.resName,readline+17,3);//resName
	strncpy(p_ca->atom.atomName,readline+12,4);//atomName
	strncpy(p_ca->atom.element,readline+77,3);//element
	p_ca->atom.resNumber=atoi(strncpy(str,readline+25,4));//resNumber
	p_ca->atom.tempFactor=atof(strncpy(str,readline+60,6));//tempFactor
	p_ca->atom.occupancy=atof(strncpy(str,readline+54,6));//occupancy
	p_ca=p_ca->nextCA; //set next pointer_CA
      }
      p=(p->nextAtom=(recordPDB*)malloc(sizeof(recordPDB))); // set next pointer
    }
  }
  
  p=NULL; // at  final Atom, current(next) is NULL
  p_ca=NULL; // at final CA, currentCA(next) is NULL
  free(readline);
  return 0;
}


