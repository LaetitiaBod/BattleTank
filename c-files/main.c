#include "fonction.h"
	
int main () {

	//menu();
	
	char c;
	system("stty -echo"); //saisie cachée
	system("clear");
	
	chargement_carte(HAUTEUR, LARGEUR, IMAGE1, "../menu-obus-carte-fin/cartebis.txt");
	chargement_carte(HAUTEUR, LARGEURBIS, IMAGE2, "../menu-obus-carte-fin/fakemap.txt");
	afficher_carte(HAUTEUR, LARGEUR, IMAGE1);
	
	NbMaxObus = 70;
	TANK * montank = malloc(sizeof(TANK));
	OBUS * unobus;
	TANK * tete_liste = NULL;
	TANK * tmp = tete_liste;
	tabObus = malloc(NbMaxObus * sizeof(pointeurOBUS));

	init_montank(montank);
	chargement_tank(montank, "../tanks/tankH.txt");
	afficher_tank(montank); // premier affichage

	ajoutEnTete(&tete_liste, 'E', 2, 0);
	ajoutEnTete(&tete_liste, 'O', 189, 0);
	mode_facile();

	while ((c = key_pressed()) != 'p') {

		//effacer_obus();

		if(c == 'z' || c == 'q' || c == 's' || c == 'd') {
			avancement_tank(montank, c);
		}
		else if(c == ' ') {
			init_obus(montank);
		}

		creer_vague(&tete_liste);
		pop_ennemi(tmp);
      	tmp = tete_liste;
      	avancement_obus();

      	usleep(26000);
	}

	system("stty echo");
	return 0;
}

