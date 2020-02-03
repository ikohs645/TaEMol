#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "PDB.h"

/*int main(int argc,char *argv[]){
  
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
  lpdbCenterCalc(pdb);

  fprintf(fpo,"***Data:%s***\nThe center of this molecule is x=%e y=%e z=%e.\n",argv[1],pdb->Center.x,pdb->Center.y,pdb->Center.z);
  
  fclose(fpi);
  fclose(fpo);
  free(pdb);
  
  return 0;
}
*/
void lpdbCenterCalc(PDB* pdb){

  recordPDB* p;
  float center_x=0;
  float center_y=0;
  float center_z=0;

  p=(recordPDB*)(malloc(sizeof(recordPDB)));
  p=pdb->top;

  while(p!=NULL){
    center_x+=p->atom.x;
    center_y+=p->atom.y;
    center_z+=p->atom.z;
    p=p->nextAtom;
      }

  pdb->Center.x=(center_x)/(pdb->numAtom);
  pdb->Center.y=(center_y)/(pdb->numAtom);
  pdb->Center.z=(center_z)/(pdb->numAtom);

  free(p);
}
