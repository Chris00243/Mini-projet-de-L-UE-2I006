#ifndef EXO1_H
#define EXO1_H

#include "entree_sortie.h"

typedef struct livre s_livre;
typedef struct Biblio Biblio;

struct livre {

	char *titre;    /* titre du livre */
	char *auteur;   /* nom de l'auteur du livre */
	int num;	/* numéro d'enregistrement du livre */
	s_livre *next;

};


struct Biblio {

	s_livre *L;  /* Liste chainée des livres */
	int nbliv;  /* Nombre de livres dans la liste chainée */

};



/******************************************************* LES FONCTIONS DE LA STRUCTURE Biblio ***********************************************************************/



/* Initialise la bibliothèque */

void initialise_biblio(Biblio **B);

/* fonction non demandée : elle affiche la strucure Biblio */

void afficher_biblio(Biblio *B);




/***************************************************** LES FONCTIONS DE LA STRUCTURE s_livre *******************************************************************/



/* créer un livre */

s_livre* creer_livre(char * auteur, char * titre);

/* fonction non demandée : elle affiche la strucure s_livre */

void afficher_livre(s_livre *L);

/* Fonction non demandée : elle fait une copie du meme livre avec le meme numéro d'enregistrement. Cette fontion est utilisée dans la fonction rechercher_livres_meme_auteur.....  */

s_livre* clone( s_livre *Acloner);



/***************************************************** LES FONCTIONS GERANT LES DEUX STRUCTURES ******************************************************************/



/* lis n entées d'un fichier.txt et les stocke dans la Bibliothèque */

void lecture_n_entree(char *nomfic, int n, Biblio **B);

/* Insère un livre dans la bibliothèque. l'insertion se fait en tête. */

void inserer_livre(Biblio **B, s_livre *nouveau);

/* La recherche d'un ouvrage par son numéro. */

s_livre* rechercher_livre_num(Biblio *B, int num);

/* La recherche d'un ouvrage par son titre. Deux livres peuvent avoir le même titre mais des auteurs différents. */

void rechercher_livres_meme_titre(Biblio *B, char *titre, Biblio **B_meme_titre);

/* La recherche de tous les livres d'un même auteur */

void rechercher_livres_meme_auteur(Biblio *B, char *auteur, Biblio **B_meme_auteur);

/* Suppression d'un livre. Un livre est reperé par son titre, le nom de son auteur et un numéro d'enregistrement. On peut avoir deux livres de même titre et de même auteur. Ce qui les différeniera sera le numéro d'enregistrement attribué a chacun d'eux. Ainsi, le numéro d'enregistrement est ici l'identifiant d'un livre. Pour supprimer un livre, on utilisera l'identifiant et pour connaitre le numéro d'enregistrement attribué à chaque livre d'une strucutre de données, il suffit d'afficher toutes les données de celle-ci en utilisant la fonction afficher_livre.   */

void supprimer_livre(Biblio **B, int num);

/* la fonction renvoie la liste des livres qui sont des doublons ou plus */

Biblio* rechercher_doublons_livre(Biblio* B);







#endif
