#ifndef EXO1_C
#define EXO1_C

#include "exo1.h"
 



#endif


unsigned static int cpt =0;


/******************************************************* LES FONCTIONS DE LA STRUCTURE Biblio ***********************************************************************/



/* Initialise la bibliothèque */

void initialise_biblio(Biblio **B)
{
	(*B) = (Biblio*) malloc(sizeof(Biblio));

	(*B)->L = NULL;
	(*B)->nbliv = 0;
}

/* fonction non demandée : elle affiche la strucure Biblio */

void afficher_biblio(Biblio *B)
{	
	if( B != NULL){

		printf("\n Biliothèque : \n\n ");

		s_livre *tmp = B->L;
	
		printf("La liste chainée des livres : \n\n");	

		while(tmp){

			printf(" ==> [%d %s %s] ==>", tmp->num, tmp->auteur, tmp->titre);
			tmp= tmp->next;
		}
		printf("NULL");
		printf("\n\n Nombre de  livres : %d \n\n ", B->nbliv);
	}
}


			
/***************************************************** LES FONCTIONS DE LA STRUCTURE s_livre *******************************************************************/



/* créer un livre */

s_livre* creer_livre(char * auteur, char * titre)
{
	if(auteur!=NULL && titre !=NULL){

		s_livre *nouveau = (s_livre*) malloc(sizeof(s_livre));
		if(nouveau == NULL) return NULL;

		nouveau->titre = strdup(titre);
		nouveau->auteur = strdup(auteur);
		nouveau->num = cpt+100000;
		cpt++;
		nouveau->next == NULL;
		return nouveau;
	}
	
	return NULL;
}

/* fonction non demandée : elle affiche la strucure s_livre */

void afficher_livre(s_livre *L)
{
	printf("\n Livre : ");

	if(L != NULL){ 
			
		printf("[ num = %d  auteur : %s titre : %s ] ", L->num, L->auteur, L->titre);
	}

	printf("==> NULL\n");
}

/* Fonction non demandée : elle fait une copie du meme livre avec le meme numéro d'enregistrement. Cette fontion est utilisée dans la fonction rechercher_livres_meme_auteur.....  */

s_livre* clone ( s_livre *Acloner)
{
	s_livre *copie = (s_livre*) malloc(sizeof(s_livre)); 
	if(copie == NULL){ 
		puts("echec clonage"); 
		return NULL;
	}

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
	char s1[taille_maxi];
	char s2[taille_maxi];
	
	
	
	if(B != NULL && n >0){   /* Si L est vide ou n est inférieur ou égale à zéro, rien à faire */
		
		FILE *f = fopen(nomfic, "r+"); /* ouverture du fichier en mode lectuer et écriture */
		
		if(f != NULL){  /* si l'ouverture échoue, rien à faire */

			for(i=0; i<n; i++){
				
				s_livre *nouveau = (s_livre*) malloc(sizeof(s_livre));
				
				nouveau->num = GetEntier(f);
				GetChaine(f,taille_maxi, s1);		
				GetChaine(f,taille_maxi, s2);

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

	if( B==NULL || *B==NULL || nouveau ==NULL) return;
	if( (*B)->L==NULL){ /* Bibliothèque encore vide */

		(*B)->L = nouveau;
		(*B)->nbliv += 1;
      		return;
	 }
	
	nouveau->next = (*B)->L;
	(*B)->L = nouveau;
	(*B)->nbliv += 1;
	
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

	Biblio *B_doublons; 
	initialise_biblio(&B_doublons);

	s_livre *cour = B->L;

	while(cour){

		Biblio *B_meme_auteur; initialise_biblio(&B_meme_auteur);
		Biblio *B_meme_titre;  initialise_biblio(&B_meme_titre);		

		rechercher_livres_meme_auteur(B, cour->auteur, &B_meme_auteur);
		
		rechercher_livres_meme_titre(B_meme_auteur, cour->titre, &B_meme_titre);
		
		s_livre* tmp = (B_meme_titre)->L;
		
		s_livre* sauvegarde = cour->next;		
	
		while(tmp){
		
			if(tmp->num != cour->num){

				if(B_doublons->nbliv == 0){

					inserer_livre(&B_doublons, clone(cour));
						
				}else{
			
					Biblio *B_meme_auteur1;  initialise_biblio(&B_meme_auteur1);
					Biblio *B_meme_titre1;  initialise_biblio(&B_meme_titre1);

					rechercher_livres_meme_auteur(B_doublons, cour->auteur, &B_meme_auteur1);
		
					rechercher_livres_meme_titre(B_meme_auteur1, cour->titre, &B_meme_titre1);
		
					if(B_meme_titre1->nbliv == 0){

						inserer_livre(&B_doublons, clone(cour));
						
					}
				  }
				
			}
			
			tmp = tmp->next;
		}						

		cour = sauvegarde;
	}

	return B_doublons;		
}



