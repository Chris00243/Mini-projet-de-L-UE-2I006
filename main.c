#ifndef MAIN_C
#define MAIN_C



#include "exo1.h"
#include "exo2.h"


#define presentation()  puts(" \n\n***********   Bonjour  ************* \n\n"); \
			puts(" 1. STRUCTURE BIBLIOTHEQUE \n "); \
	         	puts(" 2. STRUCTURE TABLE DE HACHAGE \n"); \
	        	puts(" 3. SORTIR DU PROGRAMME\n"); \



#define menu(choix) if(choix == 1){   puts(" \n\n***********  STRUCTURE BIBLIOTHEQUE   ************* \n\n"); \
		 puts(" 1. afficher la bibliothèque\n "); \
	         puts(" 2. supprimer un livre dans la bibliothèque\n"); \
	         puts(" 3. rechercher un livre dans la bibliothèque par son numéro\n"); \
	         puts(" 4. rechercher un ensemble de livres par un titre  dans la bibliothèque\n"); \
		 puts(" 5. rechercher un ensemble de livres d'un même auteur dans la bibliothèque\n"); \
		 puts(" 6.rechercher tous les livres en doublons ou plus dans la bibliothèque\n"); \
		 puts(" 7. créer, afficher et ajouter un livre dans la bibliothèque\n"); \
		 puts(" 8. sortir de la structure bibliothèque \n"); } else if(choix==2){   puts(" \n\n***********  STRUCTURE TABLE DE HACHAGE   ************* \n\n"); \
		 puts(" 1. afficher la table de Hachage\n "); \
	         puts(" 2. supprimer un livre dans la table de hachage\n"); \
	         puts(" 3. rechercher un livre dans la table de hachage par son numéro\n"); \
	         puts(" 4. rechercher un ensemble de livres par un titre  dans table de hachage\n"); \
		 puts(" 5. rechercher un ensemble de livres d'un même auteur dans la table de hachage\n"); \
		 puts(" 6.rechercher tous les livres en doublons ou plus dans la table de hachage\n"); \
		 puts(" 7. créer, afficher et ajouter un livre dans la table de hachage\n"); \
		 puts(" 8. sortir de la structure table de hachage \n");  } 
		
		
		 	
#endif





int main(int argc, char* argv[])
{
   /* argc est le nombre de mots de la ligne d e commmande
      argv est un tableau de chaines de caractères : une chaine par mot de la ligne de commande */	

	

	if(argc != 3){
		
		printf("Erreur format : %s ", argv[0]);
		return 1;
	
	}

	
	char *nomfic;

	int nlignes;

	

	nomfic = strdup(argv[1]); /* strdup alloue et copie une chaine de caractères */
	nlignes = atoi(argv[2]); /* atoi transforme une chaine de caractères en entier */

	

	char titre[taille_maxi];
	char auteur[taille_maxi];
	int num = 0;
	int taille= 0;

	int lecture;
	int choix;



	clock_t  temps_initial; /* Temps initial en micro-secondes */

	clock_t  temps_final; /* Temps final en micro-secondes */

	double temps_cpu; /* Temps total en secondes */

	temps_initial = clock();
	
	temps_final = clock();




	
	
	do{
		presentation()
		scanf("%d", &choix);
		
		switch(choix){

			case 1 : {
					Biblio *B;
					initialise_biblio(&B);
					lecture_n_entree(nomfic, nlignes, &B);

					do{

						menu(choix) /*  affiche le menu */
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

									s_livre *l = NULL;
								
									temps_initial = clock();		
									
									l = rechercher_livre_num(B, num);

									temps_final = clock();
				
									afficher_livre(l);

									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 3 : temps = %f\n\n", temps_cpu);

									break;
				
							}

							case 4 :{
					
									puts("entrer le titre du livre à chercher : ");
									scanf("%s",titre);

									Biblio *B_meme_titre;
									initialise_biblio(&B_meme_titre);
																					
									temps_initial = clock();

									rechercher_livres_meme_titre(B, titre, &B_meme_titre);

									temps_final = clock();

									afficher_biblio(B_meme_titre);

									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 4 : temps = %f\n\n", temps_cpu);
									break;

				
							}


							case 5 :{

								 	
									puts("entrer le nom de l'auteur des livres à chercher : ");
									scanf("%s",auteur);

									Biblio *B_meme_auteur;
									initialise_biblio(&B_meme_auteur);
														
									temps_initial = clock();

									rechercher_livres_meme_auteur(B, auteur, &B_meme_auteur);
							
									temps_final = clock();

									afficher_biblio(B_meme_auteur);
					
									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 5 : temps = %f\n\n", temps_cpu);
		

									break;
							}

							case 6 :{

									afficher_biblio( rechercher_doublons_livre(B) );
									break;
							}

							case 7 :{
									puts("entrez le nom de l'auteur de votre livre : ");
									scanf("%s", auteur);
					
									puts("entrez le titre de votre livre : ");
									scanf("%s", titre);

									s_livre *livre = creer_livre(auteur, titre);

									inserer_livre(&B, livre);
				
									afficher_livre(livre);

									break;
							}

							case 8 :{
									puts("\n\n Sortie de la structure Bibliothèque \n\n\n");
									break;
							}

							default : {
									puts(" \n\nje ne connais pas cette commande\n\n");
									break;

							}


						}

					}while(lecture!= 8);
				
				break;
			}

			case 2 :{
					printf("\n Entrez la taille de la table de Hachage : ");
					scanf("%d", &taille);

					tableHachage_t *Tab = initTableHachage(taille);				
					
					lecture_n_entrees(nomfic, nlignes, &Tab);					

					do{					
				
						menu(choix) /*  affiche le menu */
						scanf("%d", &lecture);

						switch(lecture){

							case 1 :{ 

									afficher_tableHachage_t(Tab);
									break;
							}

							case 2 :{
					
									puts("entrer le numéro du livre à supprimer : ");
									scanf("%d", &num);
									supprimer_cell_t(&Tab, num);
									break;
							}

							case 3 :{
					
									puts("entrer le numéro du livre à chercher : ");
									scanf("%d", &num);
									cell_t *c = NULL;
			
									temps_initial = clock();

									c = rechercher_cell_t_num(Tab, num);

									temps_final = clock();									
									
									afficher_cell_t(c);

									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 3 : temps = %f\n\n", temps_cpu);

									break;
				
							}

							case 4 :{
					
									puts("entrer le titre du livre à chercher : ");
									scanf("%s",titre);
									cell_t *l = NULL;

									temps_initial = clock();
									
									l = rechercher_cell_t_meme_titre(Tab, titre);
									
									temps_final = clock();	
									
									afficher_cell_t(l);

									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 4 : temps = %f\n\n", temps_cpu);


									break;

				
							}


							case 5 :{

								 	
									puts("entrer le nom de l'auteur des livres à chercher : ");
									scanf("%s",auteur);
									cell_t *l = NULL;

									temps_initial = clock();

									l = rechercher_cell_t_meme_auteur(Tab, auteur);

									temps_final = clock();	

									afficher_cell_t(l);

									temps_cpu = ( (double) ( temps_final - temps_initial) )/CLOCKS_PER_SEC;

									printf(" \n\nfonction 5 : temps = %f\n\n", temps_cpu);
		
								
									break;
							}

							case 6 :{

									afficher_cell_t( rechercher_doublons_cell_t(Tab) );
									break;
							}

							case 7 :{
									puts("entrez le nom de l'auteur de votre livre : ");
									scanf("%s", auteur);
					
									puts("entrez le titre de votre livre : ");
									scanf("%s", titre);

									inserer_cell_t(&Tab, creer_cell_t(auteur, titre, taille));
				
									

									break;
							}

							case 8 :{
									puts("\n\n Sortie de la structure Table Hachage \n\n\n");
									break;
							}

							default : {
									puts("\n\n je ne connais pas cette commande\n\n");
									break;

							}

						}

					}while(lecture!= 8);
				
				break;

			}

			case 3 :{

				puts("\n\n  au revoir, à plus.  Fin du programme \n\n\n");
				break;				
				
			}

			default : {

				puts("\n\n je ne connais pas cette commande\n\n");
				break;

			}
		
		}

	}while(choix!=3);
		

	return 0;

}
