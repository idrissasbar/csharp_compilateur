#ifndef PSEUDO_CODE_H
#define PSEUDO_CODE_H

// auteur Karim Ba�na, ENSIAS, D�cembre 2010

typedef enum {DATA, ADD, _DIV, DUPL, JMP, JNE, JG, LABEL, LOAD, _MULT, POP, PRNT, PUSH, SUB, STORE, SWAP} CODOP; // MULT existe d�ja comme token

typedef struct pseudocodenode * pseudocode;

struct namevalue {
	char * name;
	double value;
};

typedef union {
  char * var;
  double _const;
  char * label_name;
  struct namevalue nv; // stockage de la data
} Param;



struct pseudoinstruction{
  CODOP codop;
  Param param;
};

struct pseudocodenode{
  struct pseudoinstruction first;
  struct pseudocodenode * next;
};

// precondition pc1 <> NULL et pc2 <> NULL
// insere pc2 en queue de pc1
void inserer_code_en_queue(pseudocode pc1, pseudocode pc2);

// affiche une pseudo insctruction
void afficher_pseudo_instruction(struct pseudoinstruction pi);

// precondition pc <> NULL
// afiche un pseudocode
void afficher_pseudo_code(pseudocode pc);


#endif
