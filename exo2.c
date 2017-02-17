#ifndef EXO2_C
#define EXO2_C

#include "exo2.h"

 /* la taille du tableau de Hachage, on choisit un nombre loin de puissance de 2 */

#define A 0.618033989

#endif

unsigned static int cpt =0;

/************************************************** LES FONCTIONS DE LA STRUCTURE tableHachage_t *********************************************************/




/* Alloue de l'espace mémoire nécessaire à la table de Hachage de taille m et initialise aussi les données */

tableHachage_t* initTableHachage(int m)
{
	if(m<=0) return NULL;

	tableHachage_t *Tab = (tableHachage_t*) malloc(sizeof(tableHachage_t));
	if(Tab == NULL) return NULL;
		
	Tab->nE =0;
	Tab->m = m;

	Tab->T = (cell_t**) malloc(m*sizeof(cell_t*));
	if(Tab->T == NULL) return NULL;
	
	int i;

	for(i=0; i<m; i++){

		Tab->T[i] = NULL;
	}

	return Tab;

}

/* fonction non demandée : affiche la structure tableHachage_t */

void afficher_tableHachage_t( tableHachage_t *Tab)
{
	if(Tab!=NULL){
		
		printf(" Table de Hachage :\n\n");
		printf(" [ nombre d'éléments = %d taille de la table = %d ] \n\n", Tab->nE, Tab->m);

		cell_t *tmp = NULL;
		int i;

		for(i=0; i<Tab->m; i++){
	
			tmp = Tab->T[i];
			printf("T[%d] : ==>", i);
			while(tmp){
				
				printf("[ clef = %d, ( num = %d  auteur : %s titre : %s ) ] ==> ",tmp->clef, tmp->num, tmp->auteur, tmp->titre);
			
				tmp = tmp->next;					
			}
			
			printf("NULL\n");		
		}
	
	}
	
}




/************************************************** LES FONCTIONS DE LA STRUCTURE cell_t *****************************************************************/




/* créer une structure cell_t */

cell_t* creer_cell_t( char *auteur, char *titre, int m)
{
	

		cell_t *C = (cell_t*) malloc(sizeof(cell_t));
		if(C==NULL) return NULL;

			

		C->auteur = strdup(auteur);
		C->titre = strdup(titre);
	
		C->num = cpt+100000;
		cpt++;
		
		C->next = NULL;

		C->clef = fonctionClef(C->auteur, m);
		
		return C;
	
}

/* fonction non demandée : affiche la structure cell_t */

void afficher_cell_t(cell_t * C)
{
	printf("\n cellule : ");

	while(C!=NULL){
	
		printf("[ clef = %d, ( num = %d  auteur : %s titre : %s ) ] ",C->clef, C->num, C->auteur, C->titre);

		C = C->next;
	}
	
	printf("==> NULL\n");
}

/* Fonction non demandée : elle fait une copie de la meme cellule avec le meme numéro d'enregistrement. Cette fontion est utilisée dans la fonction rechercher_cell_meme_auteur.....  */

cell_t* cloner( cell_t * Acloner)
{
	cell_t *C = (cell_t*) malloc(sizeof(cell_t));

	C->clef = Acloner->clef;

	C->auteur = Acloner->auteur;
	C->titre = Acloner->titre;
	
	C->num = Acloner->num;
	
	C->next = NULL;
	
}

/* fonction non demandée : elle insère cell_t dans une liste de type cell_t */

void ajouter_cell_t(cell_t** liste, cell_t* C)
{
	C->next = (*liste);
	(*liste) = C;

}


/************************************************************ LES FONCTIONS DE HACHAGE ************************************************************************/




/* la fonction qui retourne la clef */

int fonctionClef(char *auteur, int m)
{
	int i =0;
	unsigned int clef;

	while(auteur[i] !='\0'){
		
		clef += (int)(auteur[i]);
		i++;	
	}

	return fonctionHachage(clef, m);	
}

/* la fonction qui transforme a clé en une valeur entière utilisable et permet d'eviter au maximum des collisions */

int fonctionHachage(int clef, int m)
{
	return (int)( m*( (clef*A)-(int)(clef*A) ) );
}




/************************************************** LES FONCTIONS DE LA STRUCTURE LES DEUX STRUCTURES *************************************************************/





/* lis n entées d'un fichier.txt et les stocke dans la table de Hachage */

void lecture_n_entrees(char *nomfic, int n, tableHachage_t **Tab)
{
	int i;
	char s1[taille_maxi];
	char s2[taille_maxi];
	
	
	
	if(Tab != NULL && n >0){   /* Si L est vide ou n est inférieur ou égale à zéro, rien à faire */
		
		FILE *f = fopen(nomfic, "r+"); /* ouverture du fichier en mode lectuer et écriture */
		
		if(f != NULL){  /* si l'ouverture échoue, rien à faire */

			for(i=0; i<n; i++){
				
				cell_t *nouveau = (cell_t*) malloc(sizeof(cell_t));
				
				nouveau->num = GetEntier(f);
				GetChaine(f,taille_maxi, s1);		
				GetChaine(f,taille_maxi, s2);
			
				nouveau->titre = strdup(s2);
				nouveau->auteur = strdup(s1);
				
				nouveau->next = NULL;

				nouveau->clef = fonctionClef(nouveau->auteur, (*Tab)->m);

				inserer_cell_t(Tab, nouveau);
			}
			
						
			fclose(f);
			
		}
	}
}


/* la fonction qui insère un cell_t dans la table de Hachage. l'insertion se fait en tête */

void inserer_cell_t(tableHachage_t **Tab, cell_t *C)
{
	if(Tab ==NULL || C ==NULL) return;

	int i = C->clef;
	cell_t **cour = &( (*Tab)->T[i] );

	if( cour == NULL){ /* le tableau de Hachage à l'indice clef est encore vide */
		
		*cour = C; 
		(*Tab)->nE += 1;
		return;
	}

	C->next = *cour;
	*cour = C; 
	(*Tab)->nE += 1;
}


/* La recherche d'un ouvrage par son numéro. */

cell_t* rechercher_cell_t_num(tableHachage_t *Tab, int num)
{
	if(Tab==NULL || Tab->nE == 0 || num <0){
		printf("Table de Hachage est vide ou num négatif");		
		return NULL;
	}

	int i =0;

	while(i < Tab->m){
	
		cell_t *tmp = Tab->T[i];

		while(tmp != NULL ){

			if(tmp->num == num){
				return tmp;
			}

			tmp = tmp->next;
		}
	
		i++;
	}

	printf(" aucun livre avec numéro = %d\n", num);
	return NULL;					
}

/* La recherche d'un ouvrage par son titre. Deux livres peuvent avoir le même titre mais des auteurs différents. */

cell_t* rechercher_cell_t_meme_titre(tableHachage_t *Tab, char *titre)
{
	if(Tab==NULL || titre == NULL){

		printf("Table de Hachage vide ou titre NULL ou echec de passage des paramètres \n");			
		return NULL;
	}

	cell_t* liste = NULL;

	int i =0;

	while(i<Tab->m){
	
		cell_t *tmp = Tab->T[i];

		while(tmp != NULL ){

			if( strcmp(tmp->titre, titre) == 0){

				ajouter_cell_t(&liste, cloner(tmp));
			}

			tmp = tmp->next;
		}
	
		i++;
	}

	return liste;			
}

/* La recherche de tous les livres d'un même auteur */

cell_t* rechercher_cell_t_meme_auteur(tableHachage_t *Tab, char *auteur)
{
	int clef = fonctionClef(auteur, Tab->m);
		
	cell_t* liste = NULL;
	cell_t *tmp = Tab->T[clef];

	while(tmp){
	
		if( strcmp(tmp->auteur, auteur) == 0){

			ajouter_cell_t(&liste, cloner(tmp));
		}
		
		tmp = tmp->next;
	}

	return liste;
}

/* Supprimer un cell_t du tableau de Hachage */

void supprimer_cell_t(tableHachage_t **Tab, int num)
{
	if( (*Tab)->nE >0 && num >=0){

		int i=0;
		

		while(i < (*Tab)->m){
	
			cell_t **cour = &( (*Tab)->T[i] );
				
	
			if( (*cour) != NULL && ( (*cour)->num == num) ){
				
				cell_t *Asupprimer = (*cour);
				(*cour) = (*cour)->next;

				

				free( (Asupprimer)->auteur);
				free( (Asupprimer)->titre);
				free( (Asupprimer) );

				(*Tab)->nE -= 1;				

				break;
			}

			cell_t **prec = cour;
			cour = &( (*cour)->next );
			

			while( (*cour) !=NULL && (*cour)->num != num){
				
				prec = cour;
				cour = &( (*cour)->next );
			}

			if( (*cour) != NULL ){
								
				cell_t *Asupprimer = *cour;

				(*prec)->next = (*cour)->next;
				
				free( Asupprimer->auteur);
				free( Asupprimer->titre);
				free( Asupprimer );

				(*Tab)->nE -= 1;

				break;
			}
			
			i++;
			
		}
		
	} 

}

/* recherche tous les livres douublons ou plus  */

cell_t* rechercher_doublons_cell_t(tableHachage_t *Tab)
{
	int i;
	cell_t *L_doublons = NULL;

	for(i=0; i < Tab->m; i++){

		cell_t *cour = Tab->T[i];
		

		while(cour != NULL){

			
				cell_t *L = rechercher_cell_t_meme_auteur(Tab, cour->auteur);

				cell_t *tmp = L;

				while(tmp){
					if ( strcmp( tmp->titre, cour->titre ) == 0 && ( tmp->num != cour->num ) ){
						ajouter_cell_t(&(L_doublons), cloner(cour));
						break;
					}

					tmp = tmp->next;
				}
			
			 
						
			cour = cour->next;
		} 

	}

	return L_doublons;
}

