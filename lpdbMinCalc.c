#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"PDB.h"
/*
int main(int argc,char *argv[]){
 
  FILE* fpi;
  FILE* fpo;
  PDB* pdb;
  
  pdb=(PDB*)malloc(sizeof(PDB));
  if(argc!=3){
    printf("***** open error ******\n");
    printf("ex: ./lpdbCenterCalc [PDB_file] [output_file]\n");
    exit(1);
  }
  
  if(NULL==(fpi=fopen(argv[1],"r"))){
    printf("fpi fopen error!\n");
    exit(1); 
  }
  if(NULL==(fpo=fopen(argv[2],"w"))){
    printf("fpo fopen error!\n");
    exit(1); 
  }
  
  pdbRead(fpi,pdb);
  lpdbMinCalc(pdb);
 
  fprintf(fpo,"***Data:%s***\nThe min of this molecule is x=%e y=%e z=%e.\n",argv[1],pdb->min.x,pdb->min.y,pdb->min.z);
  
  fclose(fpi);
  fclose(fpo);
  free(pdb);
  
  return 0;
}
*/


void lpdbMinCalc(PDB* pdb){

  recordPDB *p;

  p = pdb->top;

  pdb->min.x = p->atom.x;
  pdb->min.y = p->atom.y;
  pdb->min.z = p->atom.z;

  while(p != NULL){
    if(pdb->min.x > p->atom.x){
      pdb->min.x = p->atom.x;
    }
    if(pdb->min.y > p->atom.y){
      pdb->min.y = p->atom.y;
    }
    if(pdb->min.z > p->atom.z){
      pdb->min.z = p->atom.z;
    }
    p = p->nextAtom;
  }
}
