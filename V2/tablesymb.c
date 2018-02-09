//#ifndef TABLE_SYMB_H
//#define TABLE_SYMB_H
#include "tablesymb.h"
//#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// auteur Karim Baïna, ENSIAS, Décembre 2010

#define NBS 100
static varvalueType TS[NBS];  

static int NBVAR = 0;

void incrementer_nombre_declarations(int rangvar){
 TS[rangvar].nbdecl++; 
}  

void ajouter_nouvelle_variable_a_TS(varvalueType newvar){
//printf("T1\n");
  TS[NBVAR].nbdecl = newvar.nbdecl;
//printf("T2\n");
  TS[NBVAR].name = (char *)malloc(strlen(newvar.name)+1);
//printf("T3\n");
  strcpy(TS[NBVAR].name,newvar.name);
//printf("T4\n");
  TS[NBVAR].line = newvar.line;
//printf("T5\n");
  TS[NBVAR].initialisation = newvar.initialisation;
//printf("T6\n");
  TS[NBVAR].typevar = newvar.typevar;
//printf("T7\n");
  TS[NBVAR].valinit = newvar.valinit;
//printf("T8\n");

  //  incrementer_nombre_variables incrementer_nombre_variables
  NBVAR++;
}

char* name(int rang){
  return TS[rang].name;
}

Type typevar(int rang){
  return TS[rang].typevar;
}

double valinit(int rang){
  return TS[rang].valinit;
}

int line(int rang){
  return TS[rang].line;
}

void set_valinit(int rang, double val){
  TS[rang].valinit = val;
}

void afficherTS(){
  int i=0;
  for (i=0; i<NBVAR; i++) {
    //printf("%f-->",    TS[i].valinit);
    printf("variable %d = %s, de type %s, initialisee a %s et declaree %d fois\n",i,TS[i].name,TS[i].typevar==Int?"int":(TS[i].typevar==Double?"double":"bool"),(TS[i].typevar==Bool?(TS[i].valinit==true?"true":"false"):itoa(TS[i].valinit)),TS[i].nbdecl);  
  }
}
// itoa ==> ftoa valinit est flottante !!

boolean inTS(char * varname, int * rangvar){
//printf("enter inTS(%s)\n", varname);
  int i =0;
  while ((i < NBVAR) && (strcmp(TS[i].name,varname) != 0)) i++;
  
//printf("out inTS\n");
  if (i == NBVAR) return false;
  else { *rangvar = i; return true;}
}

int nombre_variables(){
	return NBVAR;
}

/* RAZ de la TS */
void reinitialiserTS(){
	NBVAR = 0;
}


/* itoa: convert n to characters in s */
char * itoa(int n){
  int i = 0;
  char s[100];
  char * result;
  do { /* generate digits in reverse order */
    s[i++] = n % 10 + '0'; /* get next digit */
  } while ((n /= 10) > 0); /* delete it */
  s[i] = '\0';
  reverse(s);
  result = (char *) malloc(strlen(s) + 1);
  strcpy(result, s);
  return result;
}

/* reverse: reverse string s in place */
void reverse(char s[]){
  int c, i, j;
  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

