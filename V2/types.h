#ifndef TYPES_H
#define TYPES_H

#include "ast.h"
#include "pseudocode.h"

// auteur Karim Baïna, ENSIAS, Décembre 2010

#define NULL ((void *)0)
//typedef enum {false=0, true=1} boolean; //deja defini en AST.h

//typedef enum {Int, Bool} Type; //deja defini en AST.h

typedef enum {PrintIdf, PrintString, AssignArith, AssignBool, IfThenArith, IfThenElseArith, For} Type_INST ;

typedef struct {
  char *name;       //IDF.varattribute.name
  int  nbdecl;      //IDF.varattribute.nbdecl
  Type typevar;     //IDF.varattribute.typevar
  boolean initialisation;  //IDF.initialisation
  double valinit;      // IDF.valinit
  int line;  //IDF.line
} varvalueType;

typedef struct {
  Type typename;    // CONST_IB.typename
  double valinit;      // CONST_IB.valinit
} constvalueType;

typedef struct {
  int line;  //TOKEN.line
} tokenvalueType;

typedef struct {
  Type typename;    // TYPE.typename
} typevalueType;

struct INST; // pré déclaration de la structure de stockage d'une instruction

struct LIST_INST;// pré déclaration de la structure de stockage d'une liste d'instruction

typedef struct INST {
  Type_INST typeinst;
  union  {
    // PRINT idftoprint
    struct  {
      int rangvar; // indice de l'idf, à afficher, dans la table des symboles
    } printnode;
    // left := right
    struct  {
      int rangvar; // indice de l'idf, où il faut affecter, dans la table des symboles
      //int right0; // la valeur boolenne à affecter // a nettoyer
      AST right; // l'expression à affecter (arithmétique ou booléenne)
    } assignnode;
    // IF ... THEN 
    struct  {
      int rangvar; // indice de l'idf à comparer, dans la table des symbole
      //double right; // la valeur de comparaison
      AST right; // l'expression à comparer
      struct LIST_INST * thenlinst; // then list of instructions
      struct LIST_INST * elselinst; // else list of instructions
    } ifnode;
      // for (index:= exp_min..exp_max) loop list_inst end loop;
    struct {
      struct LIST_INST * forinitializerlist; // l'expression borne inf
      AST forcondition; // l'expression borne sup
      struct LIST_INST * foriteratorlist;//call, assign, decl, decri, incr, new objet
      struct LIST_INST * forbodylinst;// for body list of instructions
    } fornode;
      
    //while( idf ){ list_inst }
    struct {
      int rangvar;//// indice de l'idf à comparer dans la table des symboles
       AST right; // l'expression à comparer
      struct LIST_INST * whilebodylinst; // while body list of instructions  
    }whilenode;

  } node;
} instvalueType;

typedef struct LIST_INST {
  struct INST first;
  struct LIST_INST * next;
} listinstvalueType;

typedef union {
  varvalueType varattribute;            //IDF.varattribute
  constvalueType constattribute;        // CONST_IB.constattribute
  Type typename;                        // TYPE.typename
  instvalueType instattribute;          // INST.instattribute
  listinstvalueType listinstattribute;  // LIST_INST.listinstattribute
  //AST expattribute;                     // EXP.expattribute
} valueType;

#define YYSTYPE valueType

extern instvalueType* creer_instruction_print(int rangvar);
extern instvalueType* creer_instruction_affectation(int rangvar, AST * past);
//extern instvalueType* creer_instruction_if(int rangvar, constvalueType constattribute, listinstvalueType * plistthen, listinstvalueType * plistelse);
extern instvalueType* creer_instruction_if(int rangvar, AST * past, listinstvalueType * plistthen, listinstvalueType * plistelse);
extern instvalueType* creer_instruction_for(int rangvar, int borneinf, int bornesup, listinstvalueType *pplistfor);

extern void inserer_inst_en_queue(listinstvalueType * listinstattribute, instvalueType instattribute);

extern void inserer_inst_en_tete(listinstvalueType ** listinstattribute, instvalueType instattribute);

extern void afficher_inst(instvalueType instattribute);

extern void afficher_list_inst(listinstvalueType * plistinstattribute);

// extern void interpreter_inst(instvalueType instattribute);

// extern void interpreter_list_inst(listinstvalueType * listinstattribute);

extern pseudocode generer_pseudo_code_inst(instvalueType instattribute);
     
extern pseudocode generer_pseudo_code_list_inst(listinstvalueType * plistinstattribute);

extern pseudocode generer_pseudo_code(listinstvalueType * plistinstattribute);

#define debug false
#endif
