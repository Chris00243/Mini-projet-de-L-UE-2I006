#ifndef EXO1_C
#define EXO1_C

#include "exo1.h"
#define taille_max 100 
#define NUM 100 


#endif


unsigned static int cpt =1;


/******************************************************* LES FONCTIONS DE LA STRUCTURE Biblio ***********************************************************************/



/* Initialise la bibliothèque */

Biblio* initialise_biblio()
{
	Biblio *nouveau = (Biblio*) malloc(sizeof(Biblio));

	nouveau->L = NULL;
	nouveau->nbliv = 0;
}

/* fonction non demandée : elle affiche la strucure Biblio */

void afficher_biblio(Biblio *B)
{	
	if( B != NULL){

		printf("\n Biliothèque : \n\n ");

		s_livre *tmp = B->L;
	
		printf("La liste chainée des livres : \n\n");	

		while(tmp){
			printf("[%d %s %s]", tmp->num, tmp->auteur, tmp->titre);
			printf(" ==> ");
			tmp= tmp->next;
		}
		printf("\n\n Nombre de  livres : %d \n\n ", B->nbliv);
	}
}


			
/***************************************************** LES FONCTIONS DE LA STRUCTURE s_livre *******************************************************************/



/* créer un livre */

s_livre* creer_livre(char * auteur, char * titre)
{
	s_livre *nouveau = (s_livre*) malloc(sizeof(s_livre));
	
	nouveau->titre = strdup(titre);
	nouveau->auteur = strdup(auteur);
	nouveau->num = cpt+100000;
	cpt++;
	nouveau->next == NULL;
	return nouveau;
}

/* fonction non demandée : elle affiche la strucure s_livre */

void afficher_livre(s_livre *L)
{
	if(L != NULL){ 
		printf("\n Livre : ");	
		printf("[ num = %d  auteur : %s titre : %s ]\n", L->num, L->auteur, L->titre);
	}
}

/* Fonction non demandée : elle fait une copie du meme livre avec le meme numéro d'enregistrement. Cette fontion est utilisée dans la fonction rechercher_livres_meme_auteur.....  */

s_livre* clone ( s_livre *Acloner)
{
	s_livre *copie = (s_livre*) malloc(sizeof(s_livre)); 

	copie->auteur = Acloner->auteur;
	copie->titre = Acloner->titre;
	copie->num = Acloner->num;
	copie->next = NULL;

	return copie;

}



/***************************************************** LES FONCTIONS GERANT LES DEUX STRUCTURES ******************************************************************/



/* lis n entées d'un fichier.txt et les stocke dans la Bibliothèque */

void lecture_n_entree(char *nomfic, int n, Biblio **B)
{	
	int i;
	char s1[taille_max];
	char s2[taille_max];
	
	
	
	if(B != NULL && n >0 ){   /* Si L est vide ou n est inférieur ou égale à zéro, rien à faire */
		
		FILE *f = fopen(nomfic, "r+"); /* ouverture du fichier en mode lectuer et écriture */
		
		if(f != NULL){  /* si l'ouverture échoue, rien à faire */

			for(i=0; i<n; i++){
				
				s_livre *nouveau = (s_livre*) malloc(sizeof(s_livre));
				
				nouveau->num = GetEntier(f);
				GetChaine(f,taille_max, s1);		
				GetChaine(f,taille_max, s2);

				nouveau->titre = strdup(s2);
				nouveau->auteur = strdup(s1);
				
				nouveau->next = NULL;

				inserer_livre(B, nouveau);
			}
			
						
			fclose(f);
			
		}
	}
}


/* Insère un livre dans la bibliothèque. l'insertion se fait en tête. */

void inserer_livre(Biblio **B, s_livre *nouveau)
{

	if( B==NULL && nouveau ==NULL) return;
	if( *B==NULL){ /* Bibliothèque encore vide */

		(*B)->L = nouveau;
		(*B)->nbliv += 1;
      		return;
	 }
	
	nouveau->next = (*B)->L;
	(*B)->L = nouveau;
	(*B)->nbliv += 1;
	return;
}


/* La recherche d'un ouvrage par son numéro. */

s_livre* rechercher_livre_num(Biblio *B, int num)
{
	if(B==NULL || num <0){
		printf("B est vide ou num négatif");		
		return NULL;
	}

	s_livre *tmp = B->L;

	while(tmp != NULL && tmp->num != num){
		
		tmp = tmp->next;
	}

	if(tmp !=NULL) return tmp;
	else{		 
	
		printf(" aucun livre avec numéro = %d\n", num);
		return NULL;		
	  }			
}

/* La recherche d'un ouvrage par son titre. Deux livres peuvent avoir le même titre mais des auteurs différents. */

void rechercher_livres_meme_titre(Biblio *B, char *titre, Biblio **B_meme_titre)
{
	if(B==NULL || titre == NULL || B_meme_titre == NULL){

		printf(" Bibliothèque vide ou titre NULL ou echec de passage des paramètres \n");			
		return;
	}

	s_livre *tmp = B->L;
	s_livre *cour = NULL;

	while(tmp){
		
		cour = tmp;
		
		if(strcmp(cour->titre, titre) == 0){
		
			inserer_livre(B_meme_titre, clone(cour));
		}
		
		tmp = tmp->next;
	}
}

/* La recherche de tous les livres d'un même auteur */

void rechercher_livres_meme_auteur(Biblio *B, char *auteur, Biblio **B_meme_auteur)
{
	if(B==NULL || auteur==NULL || B_meme_auteur == NULL){

		printf("\n echec de passage des paramètres ou auteur NULL ou Bibliothèque vide\n");		
		return;
	}

	
	s_livre *tmp =B->L;
	s_livre *cour =NULL;

	while(tmp){
		
		cour = tmp;		

		if( strcmp(cour->auteur, auteur) == 0){ 
			
			inserer_livre(B_meme_auteur, clone(cour));
		}
		
		tmp = tmp->next;
	}

}


/* Suppression d'un livre. Un livre est reperé par son titre, le nom de son auteur et un numéro d'enregistrement. On peut avoir deux livres de même titre et de même auteur. Ce qui les différeniera sera le numéro d'enregistrement attribué a chacun d'eux. Ainsi, le numéro d'enregistrement est ici l'identifiant d'un livre. Pour supprimer un livre, on utilisera l'identifiant et pour connaitre le numéro d'enregistrement attribué à chaque livre d'une strucutre de données, il suffit d'afficher toutes les données de celle-ci en utilisant la fonction afficher_livre.   */

void supprimer_livre(Biblio **B, int num)
{	
	
	s_livre **prec;	
	
	if(B!=NULL){  /* si L est vide, rien à faire */
		
		s_livre **cour = &( (*B)->L);

		if( (*cour)->num == num ){ /* si le livre à supprimer se trouve au debut de la chaine */
			
			s_livre *Asupprimer = *cour;

			(*cour) = (*cour)->next;

			free( (Asupprimer)->titre );           /* désallocation */
			free( (Asupprimer)->auteur );
			free( (Asupprimer) );

			(*B)->nbliv -=1;
			
		} 
		
		else{		/* le livre à supprimer se trouve autre place que le debut de la chaine */
			
			prec = cour;
			cour = &( (*cour)->next );
			
			while( (*cour) !=NULL && (*cour)->num !=num){
				
				prec = cour;
				cour = &( (*cour)->next );
		    	}
		    

			if( (*cour) != NULL){ /* Si L est vide, rien à faire */
				
				s_livre *Asupprimer = *cour;				

				(*prec)->next = (*cour)->next;
  
				free( Asupprimer->titre );         /* désallocation */
				free( Asupprimer->auteur );
				free( Asupprimer ); 

				(*B)->nbliv -=1;
			}

		  }
	
	}
}

/* la fonction renvoie la liste des livres qui sont des doublons ou plus */

Biblio* rechercher_doublons_livre(Biblio* B)
{
	if(B==NULL){

		printf("Bibliothèque vide");
		return NULL;	
	}

	Biblio *B_doublons = initialise_biblio();

	s_livre *cour = B->L;

	while(cour){

		Biblio *B_meme_auteur = initialise_biblio();
		Biblio *B_meme_titre = initialise_biblio();		

		rechercher_livres_meme_auteur(B, cour->auteur, &B_meme_auteur);
		
		rechercher_livres_meme_titre(B_meme_auteur, cour->titre, &B_meme_titre);
		
		s_livre* tmp = (B_meme_titre)->L;
		
		while(tmp){
		
			if(tmp->num != cour->num){

				inserer_livre(&B_doublons, clone(cour));
				(B_doublons)->nbliv += 1;
				
				s_livre *tmp1 = (B_meme_titre)->L;

				while(tmp1){
			
					supprimer_livre(&B, tmp1->num);		
					tmp1 = tmp1->next;

				}
		
				break;
			}
			
			tmp = tmp->next;
		}						

		cour = cour->next;
	}

	return B_doublons;		
}



