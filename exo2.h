#ifndef EXO2_H
#define EXO2_H

#include "exo1.h"

typedef struct cell cell_t;
typedef struct  tableHachage_t;

struct cell{
	
	int clef;

	/* int num; ... Données utiles */

	cell_t *next;

};

struct tableHachage{

	int nE;  /* nombre d'éléments contenus dans la table de hachage */
	int m;  /* taille de la table de Hachage */
	
	cell_t **T; /* table de Hachage avec résolution des collisions par chainage */
	
};



/************************************************** LES FONCTIONS DE LA STRUCTURE tableHachage_t *********************************************************/



/* Alloue de l'espace mémoire nécessaire à la table de Hachage de taille m et initialise aussi les données */

tableHachage_t* initTableHachage(int m);






#endif
