#ifndef EXO2_H
#define EXO2_H

#include "entree_sortie.h"

typedef struct cell cell_t;
typedef struct tableHachage  tableHachage_t;

struct cell{
	
	int clef;

    /* Données utiles */
	
	int num;
	char *auteur;
	char *titre;

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

/* fonction non demandée : affiche la structure tableHachage_t */

void afficher_tableHachage_t( tableHachage_t *Tab);




/************************************************** LES FONCTIONS DE LA STRUCTURE cell_t *****************************************************************/




/* créer une structure cell_t */

cell_t* creer_cell_t( char *auteur, char *titre, int m);

/* fonction non demandée : affiche la structure cell_t */

void afficher_cell_t(cell_t * C);

/* Fonction non demandée : elle fait une copie de la meme cellule avec le meme numéro d'enregistrement. Cette fontion est utilisée dans la fonction rechercher_cell_meme_auteur.....  */

cell_t* cloner( cell_t * Acloner);

/* fonction non demandée : elle insère cell_t dans une liste de type cell_t */

void ajouter_cell_t(cell_t** liste, cell_t* C);


/********************************************************* LES FONCTIONS DE HACHAGE *************************************************************************/



/* la fonction qui retourne la clef */

int fonctionClef(char *auteur, int m);


/* la fonction qui transforme a clé en une valeur entière utilisable et permet d'eviter au maximum des collisions */

int fonctionHachage(int clef, int m);



/************************************************** LES FONCTIONS DE LA STRUCTURE LES DEUX STRUCTURES *************************************************************/




/* lis n entées d'un fichier.txt et les stocke dans la table de Hachage */

void lecture_n_entrees(char *nomfic, int n, tableHachage_t **Tab);


/* la fonction qui insère un cell_t dans la table de Hachage */

void inserer_cell_t(tableHachage_t **Tab, cell_t *C);

/* La recherche d'un ouvrage par son numéro. */

cell_t* rechercher_cell_t_num(tableHachage_t *Tab, int num);


/* La recherche d'un ouvrage par son titre. Deux livres peuvent avoir le même titre mais des auteurs différents. */

cell_t* rechercher_cell_t_meme_titre(tableHachage_t *Tab, char *titre);

/* La recherche de tous les livres d'un même auteur */

cell_t* rechercher_cell_t_meme_auteur(tableHachage_t *Tab, char *auteur);

/* Supprimer un cell_t du tableau de Hachage */

void supprimer_cell_t(tableHachage_t **Tab, int num);

/* recherche tous les livres douublons ou plus  */

cell_t* rechercher_doublons_cell_t(tableHachage_t *Tab);





#endif
