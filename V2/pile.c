// auteur Karim Baïna, ENSIAS, Décembre 2010

#include "pile.h"
#include <stdlib.h>
#include <stdio.h>


Pile * creer_pile(){
	Pile * pile = (Pile *) malloc(sizeof (Pile));

	pile->taille = -1;

	return pile;
}

boolean pile_vide(Pile  *p){
	return (p->taille == -1);
}

void empiler(Pile * p, Element e){
	p->elements[p->taille + 1] = e;
	p->taille ++;
}

// pré-condition : pile_vide(p) = false
Element depiler(Pile * p){
	return p->elements[p->taille--];
}

// affiche l'état de la pile (pour débugguer)
void etat_pile(Pile *p){
	int i = 0;
	printf(" [ ");
	for(i = 0; i<= p->taille; i++)	printf("%lf", p->elements[ i ]);
	printf(" ] ");
}

/* int main(){
	Pile *p = creer_pile();

	if (pile_vide(p) != true){
		printf("erreur 1");
	}else {
		empiler(p, 1.0);
		Element e = depiler(p);
		if (e != 1.0) printf("erreur 2");
		empiler(p, 1.0);
		empiler(p, 2.0);
		empiler(p, 3.0);
		empiler(p, 4.0);
		e = depiler(p); printf("=1=>%lf\n", e);
		if (e != 4.0) printf("erreur 3");

		e = depiler(p); printf("=2=>%lf\n", e);
		if (e != 3.0) printf("erreur 4");
	
		e = depiler(p); printf("=3=>%lf\n", e);
		if (e != 2.0) printf("erreur 5");

		e = depiler(p); printf("=4=>%lf\n", e);
		if (e != 1.0) printf("erreur 6");
	}
} */
