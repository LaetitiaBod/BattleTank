#include "fonction.h"
	
int main () {
	
	menu();

	//musique de fond
	system("../audio/./sonEnBoucle.sh ../audio/musiquedefond.mp3");

	//initialisation des variables
	char c;
	tabObus = malloc(NbMaxObus * sizeof(pointeurOBUS));
	tabObus[NbMaxObus] = NULL;
	TANK * montank = malloc(sizeof(TANK));
	TANK * tete_liste = NULL;
	TANK * tmp = tete_liste;

	//fonctions pour démarrer la carte
	chargement_carte(HAUTEUR, LARGEUR, IMAGE1, "../menu-obus-carte-fin/cartebis.txt");
	chargement_carte(HAUTEUR, LARGEURBIS, IMAGE2, "../menu-obus-carte-fin/fakemap.txt");
	afficher_carte(HAUTEUR, LARGEUR, IMAGE1);
	
	//fonctions du tank allié
	init_montank(montank);
	chargement_tank(montank, "../tanks/tankH.txt");
	afficher_tank(montank); // premier affichage
	
	//afficher messages utiles au joueur
	afficher_message_vies(montank);
	afficher_message_ennemis();

	//les premiers ennemis par défaut
	ajoutEnTete(&tete_liste, 'E', 2, 0);
	ajoutEnTete(&tete_liste, 'O', 189, 0);
	

	//la partie est lancé, on la quitte si le joueur appuie sur p ou si le joueur meurt (joker ou nb de vies) ou si le joueur gagne
	while ((c = key_pressed()) != 'p' && montank->etat > 0 && GAGNER != 1) {

		//deplacements du tank allié
		if(c == 'z' || c == 'q' || c == 's' || c == 'd') {
			avancement_tank(montank, c);
		}
		//création des obus alliés
		else if(c == ' ') {
			init_obus(montank);
		}

		//on avance tous les obus pas à-coups
		avancement_obus(montank, &tete_liste);

		//création des ennemis au fur et à mesure
		creer_vague(&tete_liste);

		//comportement aléatoire des ennemis
		pop_ennemi(tmp);

      	tmp = tete_liste;
	}
	
	//on réactive les fonctionnalités du terminal
	system("clear");
	system("killall play");
	system("stty echo");
	//system("setterm -cursor on"); sauf celui-là parce que c'est moche

	//écran de fin
	if(montank->etat == 0) {
		destruction_tank(montank); //le tank du joueur se détruit
		defaite("../menu-obus-carte-fin/defaite.txt");
		
	} else {
		victoire("../menu-obus-carte-fin/victoire.txt");
	}

	while(c = key_pressed() != 'p') {}
	
	return 0;
}

