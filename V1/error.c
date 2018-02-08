//#ifndef ERROR_H
//#define ERROR_H
#include "error.h"
//#endif
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// auteur Karim Baïna, ENSIAS, Décembre 2010

#define NBERRMAX 100
static int NBERRDECL = 0;
static int NBERRINST = 0;

static smerror * ERDECL[NBERRMAX];
static smerror * ERINST[NBERRMAX];

static int NBERRSX = 0;
static sxerror * ERSX[NBERRMAX];

void afficher_sm_erreur(SemanticErrorType et, int line, char* name){
 
  printf("ligne %d : %s ", line,  name);
  switch (et){
  case NotDeclared: printf("variable non declaree\n"); break;
  // case NotDefined: printf("variable utilisee sans initialisation\n"); break;
  case IncompatibleAssignType:  printf("incompatible avec la valeur d'affectation\n"); break;
  case IncompatibleCompType: printf("incompatible avec la valeur de comparaison\n"); break;
  case IncompatibleOperationType:  printf("incompatible avec l'operation\n"); break;
  case BadlyInitialised:  printf("variable mal initialisee\n"); break;
  case AlreadyDeclared:  printf("variable deja declaree\n"); break;
  }
}

smerror * creer_sm_erreur(SemanticErrorType et, int line, char* name){
  smerror * e = (smerror*) malloc (sizeof (smerror) );
  e->name = (char *) malloc (strlen(name));
  strcpy(e->name, name);
  e->line = line;
  e->errort = et;

  return e;
}

void creer_sx_erreur(SyntacticErrorType et, int line){
    sxerror * e = (sxerror*) malloc (sizeof (sxerror) );
    e->line = line;
    e->errort = et;

    ERSX[NBERRSX++]= e;   
}


void afficher_sx_erreur(SyntacticErrorType et, int line){
  printf("ligne %d : ", line);
  switch (et){
 	 case BeginExpected : printf("begin attendu\n"); break;
  }
}

void afficher_sx_erreurs(){
int nberr = 0;
  while (nberr < NBERRSX) {
    afficher_sx_erreur(ERSX[nberr]->errort, ERSX[nberr]->line);
    nberr++;
  }
}

int nombre_sx_erreurs(){
 return NBERRSX;
}

void afficher_sm_erreurs(){
  int idecl = 0;
  int iinst = 0;
  while (idecl < NBERRDECL) {
    afficher_sm_erreur(ERDECL[idecl]->errort, ERDECL[idecl]->line, ERDECL[idecl]->name);
    idecl++;
  }

 while (iinst < NBERRINST) {
    afficher_sm_erreur(ERINST[iinst]->errort, ERINST[iinst]->line, ERINST[iinst]->name);
    iinst++;
  }
}

void creer_sm_erreur_instruction(SemanticErrorType et, int line, char* name){
    ERINST[NBERRINST++]= creer_sm_erreur(et, line, name);   
}

void creer_sm_erreur_declaration(SemanticErrorType et, int line, char* name){
   ERDECL[NBERRDECL++]= creer_sm_erreur(et, line, name); 
}

int nombre_sm_erreurs(){
  return  NBERRDECL + NBERRINST;
}
