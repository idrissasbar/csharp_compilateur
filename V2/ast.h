#ifndef AST_H
#define AST_H

#include "pseudocode.h"
#include "analyseur_csharp.h"

// auteur Karim Ba�na, ENSIAS, D�cembre 2010

typedef enum {NB=0, _IDF = 1, BOOLEAN = 2, OP=3} Type_Exp ; // IDF is also a token !!

typedef enum {Int, Bool, Double} Type;

typedef enum {plus, moins, mult, _div, mod, _or , _and} Type_Op; // div est un mot r�serv�


struct Exp ; /* pr� d�claration de la structure de stockage d'une expression */

typedef struct Exp * AST;

typedef union {
  double nombre ;
  char *idf;
  boolean bool; //cas sp�cial de la feuille TRUE / FALSE
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

// pr�condition : a<> NULL and est_feuille(a) == false
AST arbre_gauche(AST a);

// pr�condition : a<> NULL and est_feuille(a) == false
AST arbre_droit(AST a);

// pr�condition : a<> NULL and est_feuille(a) == false
Type_Op top(AST a);

// pr�condition : a<> NULL
Type     type(AST a);

// pr�condition : a<> NULL 
boolean est_feuille(AST a);


AST creer_feuille_booleen(boolean b);

AST creer_feuille_nombre(double n, Type type);

AST creer_feuille_idf(char *idf, Type type);

AST creer_noeud_operation(char op, AST arbre_g, AST arbre_d, Type type);

// affichage par parcours infix� de l'arbre abstrait
// pr�condition : ast<> NULL 
void afficher_infixe_arbre (AST ast);

// affichage par parcours postfix� de l'arbre abstrait
// pr�condition : ast<> NULL 
void afficher_postfixe_arbre (AST ast);

// �valation par parcours postfix� de l'arbre abstrait
// pr�condition : ast<> NULL 
double evaluer (AST ast);

// g�n�re le pseudo-code relatif � l'AST
// pr�condition ast <> NULL

pseudocode generer_pseudo_code_ast(AST ast);
#endif
