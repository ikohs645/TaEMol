#ifndef PDB_H
#define PDB_H

typedef struct Atom Atom;
struct Atom{
  float x;
  float y;
  float z;
  char resName[4];
  int resNumber;
  float tempFactor;
  float occupancy;
  char atomName[5];
  char element[3];
};

typedef struct recordPDB recordPDB;
struct recordPDB{
  Atom Center;
  Atom atom;
  recordPDB* nextAtom;
  recordPDB* nextCA;
};

typedef struct PDB PDB;
struct PDB{
  int numAtom;
  int numCA;
  float maxRadius;
  recordPDB* top;
  recordPDB* topCA;
  recordPDB* current;
  recordPDB* currentCA;
  Atom Center;
  Atom min;
  Atom max;
  Atom atom;
};

typedef struct Bond Bond;
struct Bond{
Atom start;
Atom end;
}; 

typedef struct arrayPDB arrayPDB;
struct arrayPDB{
  int numAtom;
  int numCAAtom;
  Atom *CA;
};

extern PDB pdb;
extern void bondDraw(FILE* fpt,float startx,float starty,float endx,float endy);
extern void bondDraw2(FILE* fpt, Bond l);
extern int bondCADraw(FILE* fpt,arrayPDB pdb,float originx,float originy,float scale);
extern int bondCADraw2(FILE* fpt,PDB* pdb,float originx,float originy,float scale);
extern int arrayPDBRead(FILE* fpt,arrayPDB* pdb);
extern int pdbRead(FILE* fpt,PDB* pdb);
extern void lpdbCenterCalc(PDB* pdb);
extern void lpdbSizeCalc(PDB* pdb);
extern void lpdbMinCalc(PDB* pdb);
extern void lpdbMaxCalc(PDB* pdb);
extern void lpdbInfoPrint(FILE* fpt,PDB* pdb);
#endif
