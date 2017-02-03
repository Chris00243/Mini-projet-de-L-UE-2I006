#ifndef MAIN_C
#define MAIN_C

#define taille_maxi 25

#include "exo1.h"

#define menu()   puts(" Bonjour \n\n"); \
	         puts(" 1. afficher la bibliothèque\n "); \
	         puts(" 2. supprimer un livre dans la bibliothèque\n"); \
	         puts(" 3. rechercher un livre dans la bibliothèque par son numéro\n"); \
	         puts(" 4. rechercher un ensemble de livres par un titre  dans la bibliothèquedans\n"); \
		 puts(" 5. rechercher un ensemble de livres d'un même auteur dans la bibliothèque\n"); \
		 puts(" 6.rechercher tous les livres en doublons ou plus dans la bibliothèque\n"); \
		 puts(" 7. créer, afficher et ajouter un livre dans la bibliothèque\n"); \
		 puts(" 8. sortir du programme \n");
		 	
#endif











int main(int argc, char* argv[])
{
   /* argc est le nombre de mots de la ligne d e commmande
      argv est un tableau de chaines de caractères : une chaine par mot de la ligne de commande */	

	int lecture;
	char *nomfic;

	int nlignes;

	Biblio *B;
	initialise_biblio(&B);

	if(argc != 3){
		
		printf("Erreur format : %s ", argv[0]);
	
	}

	nomfic = strdup(argv[1]); /* strdup alloue et copie une chaine de caractères */
	nlignes = atoi(argv[2]); /* atoi transforme une chaine de caractères en entier */

	printf("\\n LECTURE \n\n");
	lecture_n_entree(nomfic, nlignes, &B);

	char titre[taille_maxi];
	char auteur[taille_maxi];
	int num;

	s_livre *livre;	
	
	do{

		menu() /*  affiche le menu */
		scanf("%d", &lecture);

		switch(lecture){

			case 1 :{ 

				afficher_biblio(B);
				break;
			}

			case 2 :{
					
					puts("entrer le numéro du livre à supprimer : ");
					scanf("%d", &num);
					supprimer_livre(&B, num);
					break;
			}

			case 3 :{
					
					puts("entrer le numéro du livre à chercher : ");
					scanf("%d", &num);
					afficher_livre(rechercher_livre_num(B, num));
					break;
				
			}

			case 4 :{
					
					puts("entrer le titre du livre à chercher : ");
					scanf("%s",titre);

					Biblio *B_meme_titre;
					initialise_biblio(&B_meme_titre);
					rechercher_livres_meme_titre(B, titre, &B_meme_titre);
					afficher_biblio(B_meme_titre);
					break;

				
			}


			case 5 :{

				 	
					puts("entrer le nom de l'auteur des livres à chercher : ");
					scanf("%s",auteur);

					Biblio *B_meme_auteur;
					initialise_biblio(&B_meme_auteur);
					rechercher_livres_meme_auteur(B, titre, &B_meme_auteur);
					afficher_biblio(B_meme_auteur);
					break;
			}

			case 6 :{

					rechercher_doublons_livre(B);
					break;
			}

			case 7 :{
					puts("entrez le nom de l'auteur de votre livre : ");
					scanf("%s", auteur);
					
					puts("entrez le titre de votre livre : ");
					scanf("%s", titre);

					livre = creer_livre(auteur, titre);

					inserer_livre(&B, livre);
				
					afficher_livre(livre);

					break;
			}

			case 8 :{
					puts("\nau revoir, à plus\n\n\n");
					break;
			}

			default : {
					puts("je ne connais pas cette commande\n\n");
					break;

			}


		}

	}while(lecture!= 8);
		

	return 0;

}
