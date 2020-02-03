#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include"PDB.h"

void lpdbMaxCalc(PDB* pdb){

  recordPDB *p;

  p = pdb->top;

  pdb->max.x = p->atom.x;
  pdb->max.y = p->atom.y;
  pdb->max.z = p->atom.z;

  while(p != NULL){    
    if(pdb->max.x < p->atom.x){
      pdb->max.x = p->atom.x;
    }
    if(pdb->max.y < p->atom.y){
      pdb->max.y = p->atom.y;
    }
    if(pdb->max.z < p->atom.z){
      pdb->max.z = p->atom.z;
    }
    p = p->nextAtom;
  }
}
