#ifndef VM_H
#define VM_H

#include "pseudocode.h"

// auteur Karim Baïna, ENSIAS, Décembre 2010

// inintialise la machine abstraite
void inintialiser_machine_abstraite();

// interprete une pseudo insctruction
// le résultat est en tête de pile.
// si l'instruction est un JMP ou un JNE, le next_label_name est renseignée pour effectuer le branchement
void interpreter_pseudo_instruction(struct pseudoinstruction pi, char ** next_label_name);

// precondition pc <> NULL
// interprete un pseudocode
// le résultat est en tête de pile.
void interpreter_pseudo_code(pseudocode pc);

#endif

