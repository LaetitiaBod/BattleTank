#include "fonction.h"

	//quotas de nombres d'ennemis
	int ennemis;
	int simple;
	int blinde;
	int suprablinde;
	int nbTanksTuesFacile;
	int nbTanksTuesDifficile;

void init_ennemi(TANK * ennemitank, char direction, int y, int blindage){

	int x = 1;
	int i, j;
	
	ennemitank -> direction = direction;//E pour un tank qui commence en haut à gauche //O pour un tank qui commence en haut à droite
	ennemitank -> posx = x;
	ennemitank -> posy = y;
	ennemitank -> blindage = blindage; //0: simple; 1: blindé; 2: suprablindé
	ennemitank -> type = 'e';
	ennemitank -> etat = 1; //utilie pour la destruction d'un ennemi (non implémenté)
	ennemitank -> tirer = 1; //utile pour la cadence de tirer d'un ennemi
	ennemitank -> deplacer = 1;
	
	/*
	ce qui varie en fonction du type du tank ennemi :
	direction (pop gauche/droite 1/2)
	posy (pop gauche/droite soit 2 soit 189)
	blindage //mode facile : 6 simple, 5 blindé, 4 suprablindé //mode difficile : 15 simples, 9 blindé, 6 ultrablindé 
	*/
	
	completer_fakemap(ennemitank);
}

void creer_vague(TANK** tete_liste) {

	int videG = 0;
	int videD = 0;

	for(int i=1; i<1+5; i++) { //spawn haut a droite
		for(int j = 189; j<189+9; j++) {
			if(IMAGE2[i][j] == ' ') {
				videD = 1;
			} else {
				videD = 0;
			}
		}
	}

	for(int i=1; i<1+5; i++) { //spawn haut à gauche
		for(int j = 2; j<2+9; j++) {
			if(IMAGE2[i][j] == ' ') { //est ce que le spawn est vide
				videG = 1; //oui
			} else {
				videG = 0; //non
			}
		}
	}

	srand(time(NULL));
	int pop = rand()%10;

	if(pop == 5) {

	pop = 0;
	if(videG == 1 && ennemis != 0) { //si le spawn est vide et qu'il reste des ennemis à creer
		if(simple != 0) {
			ajoutEnTete(tete_liste, 'E', 2, 0); //soit un simple
			simple -= 1;
		}else if (blinde != 0) {
			ajoutEnTete(tete_liste, 'E', 2, 1); //soit un blinde
			blinde -= 1;
		} else if(suprablinde != -(ennemis-(simple+blinde)-1)) {
			ajoutEnTete(tete_liste, 'E', 2, 2); //soit un suprablinde
			suprablinde -= 1;
		}
		ennemis -= 1; //diminue le nb d'ennemis restants à faire spawn
	}

	if(videD == 1 && ennemis != 0) {
		if(simple != 0) {
			ajoutEnTete(tete_liste, 'O', 189, 0);
			simple -= 1;
		}else if (blinde != 0) {
			ajoutEnTete(tete_liste, 'O', 189, 1);
			blinde -= 1;
		} else if(suprablinde != -(ennemis-(simple+blinde)-1)) { //probleme non résolu => on contourne le probleme
			ajoutEnTete(tete_liste, 'O', 189, 2);
			suprablinde -= 1;
		}
		ennemis -= 1;
	}

	}
}

void mode_facile() {

	//on enlève les deux premiers tanks simple
	ennemis = 13;
	simple = 4;
	blinde = 5;
	suprablinde = 4;
	nbTanksTuesFacile = 15; //évoluera de 15 à 0 => enclenche la victoire
}

void mode_difficile() {

	//on enlève les deux premiers tanks simple
	ennemis = 28;
	simple = 13;
	blinde = 9;
	suprablinde = 6;
	nbTanksTuesFacile = 100; //évoluera de 100 à 70 => n'interfère pas pour la fin du jeu
	nbTanksTuesDifficile = 30;
}

char direction_aleatoire(int avancer) {

	char c;
	
	switch(avancer) {
		case 0 : c = 'z'; break;
		case 1 : c = 'q'; break;
		case 2 : c = 's'; break;
		case 3 : c = 'd'; break;
		case 4 : break;
	}
	return c;
}

void pop_ennemi(TANK * tmp) {

	char c;
	int avancer = 0, i = 0;

	srand(time(NULL));

	while(tmp != NULL) {

		if(tmp->deplacer%5000 == 0 && tmp->deplacer != 0) { //cette ligne provoque parfois des erreurs de segmentation à la fin du jeu
			avancer = (rand()%5+i)%5;
			c = direction_aleatoire(avancer);
			avancement_tank(tmp, c);
			tmp->deplacer = 0;
		}

		if(tmp->tirer%50000 == 0) { //le chiffre est la cadence de tir
			init_obus(tmp);
			tmp->tirer = 0;
		}

		tmp->tirer++;
		tmp->deplacer++;
		i++;
		tmp = tmp->next;
    }
}

void blesser_ennemi(pointeurOBUS obus, TANK** tete_liste) {

	int positionx = 0, positiony = 0, continuer = 0;
	GAGNER = 0;

	//on place un marqueur invisible à la position [positionx/positiony] (environ au milieu d'un tank)
	switch(obus->direction) {
		case 'N':
			positionx = obus->posx-1;
			positiony = obus->posy+1;
		break;

		case 'S':
			positionx = obus->posx+3;
			positiony = obus->posy+1;
		break;

		case 'E':
			positionx = obus->posx+1;
			positiony = obus->posy+5;
		break;

		case 'O':
			positionx = obus->posx+1;
			positiony = obus->posy-4;
		break;
	}
	//le tank à la position positionx/positiony a été touché

	TANK * tmp = *tete_liste;
	int position = 0;

	if(nbTanksTuesDifficile != 0 || nbTanksTuesFacile != 0) {
	//on parcourt la liste de tanks pour trouver celui qui est à la position indiquée
	while (tmp != NULL) 
    { 
    	for(int i=0; i<6; i++) {
    		for(int j=0; j<10; j++) {
    			if(tmp->posx+i == positionx && tmp->posy+j == positiony) { //si on trouve que les positions correspondent
    				continuer = 1; //on continue
		    	}
    		}
    	}

		if(continuer == 1) { //on a trouvé un tank avec un marqueur invisible
    		switch(tmp->blindage) {
    			case 0:
    				system("../audio/./son.sh ../audio/tankmort.mp3");
    				tmp->etat = 0;
    				
    				destruction_tank(tmp);
	    			supprimerTankEnnemi(tete_liste, position); //on supprime le tank qui a etat = 0 à l'index 'position' de la liste
	    			nbTanksTuesFacile--;
	    			nbTanksTuesDifficile--;
	    			afficher_message_ennemis();
				break;

    			default:
    			//on diminue le blindage du tank s'il n'a pas un blindage simple
    				tmp->blindage--;
    				for(int i=0; i<5; i++) {
	    				for(int j=0; j<9; j++) {
	    					printf("\033[%d;%dH", tmp->posx+1+i, tmp->posy+1+j); //on efface le tank visuellement
	    					printf(" ");
	    				}
	    			}
	    			afficher_tank(tmp);
    			break;
    		}
    		break;
    	}
   		tmp = tmp->next; 
   		position++;
	}
	}
	if(nbTanksTuesDifficile == 0 || nbTanksTuesFacile == 0) {
		GAGNER = 1;
	}
}

void afficher_message_ennemis() {

	printf("\x1B[31m");
	
	if(nbTanksTuesFacile < 30) {
		printf("\033[%d;%dH", 51, 20);
		printf("%d X 😈", nbTanksTuesFacile);
	} else {
		printf("\033[%d;%dH", 51, 20);
		printf("%d X 😈", nbTanksTuesDifficile);
	}
}