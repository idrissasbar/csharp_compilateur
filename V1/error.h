#ifndef ERROR_H
#define ERROR_H

// Types nécessaires à la gestion des erreurs

// auteur Karim Baïna, ENSIAS, Décembre 2010

typedef enum {BeginExpected,
		} SyntacticErrorType;

typedef enum {NotDeclared,
               //NotDefined, // variable utilisee sans définition : difficilement gérable car il faut détecter malgré la non inialisaton que la variable n'a pas été affecté par la suite
	      AlreadyDeclared,
	      BadlyInitialised,
	      IncompatibleAssignType,
	      IncompatibleCompType,
	      IncompatibleOperationType} SemanticErrorType;

typedef struct {
  char *name;
  int line;
  SemanticErrorType errort;
} smerror;

typedef struct {
  int line;
  SyntacticErrorType errort;
} sxerror;

extern void creer_sx_erreur(SyntacticErrorType et, int line);

extern void afficher_sx_erreur(SyntacticErrorType et, int line);

extern void afficher_sx_erreurs();

extern int nombre_sx_erreurs();

extern smerror * creer_sm_erreur(SemanticErrorType et, int line, char * name);

extern void creer_sm_erreur_instruction(SemanticErrorType et, int line, char* name);

extern void creer_sm_erreur_declaration(SemanticErrorType et, int line, char* name);

extern void afficher_sm_erreur(SemanticErrorType et, int line, char* name);

extern void afficher_sm_erreurs();

extern int nombre_sm_erreurs();

#endif
