#ifndef EXO2_C
#define EXO2_C

#include "exo2.h"

#endif



/************************************************** LES FONCTIONS DE LA STRUCTURE tableHachage_t *********************************************************/


/* Alloue de l'espace mémoire nécessaire à la table de Hachage de taille m et initialise aussi les données */

tableHachage_t* initTableHachage(int m)
{
	if(m<=0) return NULL;

	tableHachage_t *tab = (tableHachage*) malloc(sizeof(tableHachage_t));

	tab->nE =0;
	tab->m = m;

	tab->T = (cell_t*) malloc(m*sizeof(cell_t));

	return tab;

}

