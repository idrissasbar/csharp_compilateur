#ifndef TABLE_SYMB_H
#define TABLE_SYMB_H

#include "types.h"


// auteur Karim Baïna, ENSIAS, Décembre 2010

// select *
extern void afficherTS();

// prédicat de recherche
extern boolean inTS(char * varname, int* rangvar);  

// constructeur d'une nouvelle variable
extern void ajouter_nouvelle_variable_a_TS(varvalueType newvar);

extern void incrementer_nombre_declarations(int rangvar);
extern char* name(int rang);
extern int line(int rang);
extern Type typevar(int rang);
extern double valinit(int rang);
extern void set_valinit(int rang, double val);
extern int nombre_variables();

// additional support functions
/* reverse: reverse string s in place */
extern void reverse(char s[]);

/* itoa: convert n to characters in s */
extern char * itoa(int);

/* RAZ de la TS */
extern void reinitialiserTS();

#endif
