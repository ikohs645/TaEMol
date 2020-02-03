#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "PDB.h"
 
/*int main(int argc,char *argv[]){
  
  FILE* fpi;
  FILE* fpo;
  PDB* pdb;
  
  pdb=(PDB*)malloc(sizeof(PDB));
  if(argc!=3){
    printf("error!\n");
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
  lpdbSizeCalc(pdb);
  fprintf(fpo,"Data:%s\n The maxRadius of this molecule is %e\n",argv[1],pdb->maxRadius);
  
  fclose(fpi);
  fclose(fpo);
  free(pdb);
  
  return 0;
}
*/
 
void lpdbSizeCalc(PDB* pdb){
  float temp=0;
  float R;
  pdb->current=pdb->top;
  
  while(pdb->current->nextAtom!=NULL){
    R=sqrt(pow(pdb->current->atom.x-pdb->Center.x,2.0)
	   +pow(pdb->current->atom.y-pdb->Center.y,2.0)
	   +pow(pdb->current->atom.z-pdb->Center.z,2.0));
      
      if(temp<R){
	temp=sqrt(pow(pdb->current->atom.x-pdb->Center.x,2.0)
		  +pow(pdb->current->atom.y-pdb->Center.y,2.0)
		  +pow(pdb->current->atom.z-pdb->Center.z,2.0));
      }
    pdb->current=pdb->current->nextAtom;
  }
  pdb->maxRadius=temp;

}
