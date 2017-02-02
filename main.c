#ifndef MAIN_C
#define MAIN_C

#include "exo1.h"

#endif

int main(int argc, char argv[])
{
	Biblio *B = initialise_biblio();
	afficher_biblio(B);
	lecture_n_entree("GdeBiblio.txt", 5, &B);
	afficher_biblio(B);

	s_livre *L1, *L2, *L3, *L4, *L5, *L6, *L7, *L8;

	L1 = creer_livre("KASA", "savoir");
	L2 = creer_livre("CHRIS","physique");
	L3 = creer_livre("KASA", "savoir");
	L4 = creer_livre("KASA", "physique");
	L5 = creer_livre("CHRIS", "physique");
	L6 = creer_livre("KASA", "savoir");
	L7 = creer_livre("KASA", "physique");
	L8 = creer_livre("KASA", "savoir");

	afficher_livre(L1);
	afficher_livre(L2);
	afficher_livre(L3);
	afficher_livre(L4);

	inserer_livre(&B, L1);
	inserer_livre(&B, L2);
	inserer_livre(&B, L3);
	inserer_livre(&B, L4);
	inserer_livre(&B, L5);
	inserer_livre(&B, L6);
	inserer_livre(&B, L7);
	inserer_livre(&B, L8);

	afficher_biblio(B);

	s_livre *R1, *R2, *R3, *R4;
	Biblio *B1, *B2, *B3, *B4, *B6, *B7;
	
	B1 = initialise_biblio();
	B2 = initialise_biblio();
	B3 = initialise_biblio();	
	B4 = initialise_biblio();
	B6 = initialise_biblio();	
	B7 = initialise_biblio();	

	

	R1 = rechercher_livre_num(B, 1);
	afficher_livre(R1);

	R2 = rechercher_livre_num(B, 12);
	afficher_livre(R2);

	rechercher_livres_meme_titre(B,"savoir", &B6);
	afficher_biblio(B6);

	rechercher_livres_meme_titre(B,"reve", &B7);
	afficher_biblio(B7);

	

	rechercher_livres_meme_auteur(B,"KASA", &B3);
	afficher_biblio(B3);
	
	
	rechercher_livres_meme_auteur(B,"CHRIS", &B2);
	afficher_biblio(B2);

	rechercher_livres_meme_auteur(B,"TOTO", &B1);
	afficher_biblio(B1);
	
	supprimer_livre(&B, L7->num);

	B4 = rechercher_doublons_livre(B);
	afficher_biblio(B4);	

	afficher_biblio(B);
	

	return 0;

}
