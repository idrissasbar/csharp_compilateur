#ifndef AST_H
#define AST_H

#include "pseudocode.h"
#include "analyseur_csharp.h"

// auteur Karim Baïna, ENSIAS, Décembre 2010

typedef enum {NB=0, _IDF = 1, BOOLEAN = 2, OP=3} Type_Exp ; // IDF is also a token !!

typedef enum {Int, Bool, Double} Type;

typedef enum {plus, moins, mult, _div, mod, _or , _and} Type_Op; // div est un mot réservé


struct Exp ; /* pré déclaration de la structure de stockage d'une expression */

typedef struct Exp * AST;

typedef union {
  double nombre ;
  char *idf;
  boolean bool; //cas spécial de la feuille TRUE / FALSE
  char *string;
  struct {
    Type_Op top;
    AST expression_gauche ;
    AST expression_droite ;
  } op;
} ExpValueTypeNode;

typedef struct Exp {
  Type_Exp typeexp ; // NB ou IDF ou OP
  Type     typename; // Int ou Bool ou Double
  ExpValueTypeNode noeud ;
}expvalueType;

double value(char *idf);

// précondition : a<> NULL and est_feuille(a) == false
AST arbre_gauche(AST a);

// précondition : a<> NULL and est_feuille(a) == false
AST arbre_droit(AST a);

// précondition : a<> NULL and est_feuille(a) == false
Type_Op top(AST a);

// précondition : a<> NULL
Type     type(AST a);

// précondition : a<> NULL 
boolean est_feuille(AST a);


AST creer_feuille_booleen(boolean b);

AST creer_feuille_nombre(double n, Type type);

AST creer_feuille_idf(char *idf, Type type);

AST creer_noeud_operation(char op, AST arbre_g, AST arbre_d, Type type);

// affichage par parcours infixé de l'arbre abstrait
// précondition : ast<> NULL 
void afficher_infixe_arbre (AST ast);

// affichage par parcours postfixé de l'arbre abstrait
// précondition : ast<> NULL 
void afficher_postfixe_arbre (AST ast);

// évalation par parcours postfixé de l'arbre abstrait
// précondition : ast<> NULL 
double evaluer (AST ast);

// génère le pseudo-code relatif à l'AST
// précondition ast <> NULL

pseudocode generer_pseudo_code_ast(AST ast);
#endif
