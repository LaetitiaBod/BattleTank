#include "fonction.h"


/*
couleurs : 
	printf("\033[33;01mx \033[00m");
	printf("\033[36;01mo \033[00m");
*/

	int ennemis;
	int simple;
	int blinde;
	int suprablinde;

void init_ennemi(TANK * ennemitank, char direction, int y, int blindage){

	int x = 1;
	int i, j;
	
	ennemitank -> direction = direction;//E pour un tank qui commence en haut à gauche //O pour un tank qui commence en haut à droite
	ennemitank -> posx = x;
	ennemitank -> posy = y;
	ennemitank -> blindage = blindage; //0: simple; 1: blindé; 2: suprablindé
	ennemitank -> blindage_orig = blindage;
	ennemitank -> touches = 0;
	ennemitank -> type = 'e';
	ennemitank -> etat = 1; //1: actif; 2: en destruction; 3: inactif
	ennemitank -> mise_a_jour = 0; //utile pour la suppression du tank e tenant compte d'un delay
	
	/*
	ce qui varie en fonction du type du tank ennemi :
	direction (pop gauche/droite 1/2)
	posy (pop 1/2 soit 3 soit 190)
	blindage (dépend du blindage_orig) //mode facile : 6 simple, 5 blindé, 4 suprablindé //mode difficile : 15 simples, 9 blindé, 6 ultrablindé 
	blindage_orig (quota de type de tank)
	*/
	
	completer_fakemap(ennemitank);
}

void creer_vague(TANK** tete_ref) {

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

	if(videG == 1 && ennemis != 0) { //si le spawn est vide et qu'il reste des ennemis à creer
		if(simple != 0) {
			ajoutEnTete(tete_ref, 'E', 2, 0); //soit un simple
			simple -= 1;
		}else if (blinde != 0) {
			ajoutEnTete(tete_ref, 'E', 2, 1); //soit un blinde
			blinde -= 1;
		} else if(suprablinde != 0) {
			ajoutEnTete(tete_ref, 'E', 2, 2); //soit un suprablinde
			suprablinde -= 1;
		}
		ennemis -= 1; //diminue le nb d'ennemis restants à faire spawn
	}

	if(videD == 1 && ennemis != 0) {
		if(simple != 0) {
			ajoutEnTete(tete_ref, 'O', 189, 0);
			simple -= 1;
		}else if (blinde != 0) {
			ajoutEnTete(tete_ref, 'O', 189, 1);
			blinde -= 1;
		} else if(suprablinde != 0) {
			ajoutEnTete(tete_ref, 'O', 189, 2);
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
}

char direction_aleatoire(TANK * tmp, int avancer) {

	char c;
	
	switch(avancer) {
		case 0 : c = 'z'; break;
		case 1 : c = 'q'; break;
		case 2 : c = 's'; break;
		case 3 : c = 'd'; break;
		case 4 : break;
		case 5 : c = 'o'; break;
	}
	return c;
}

void pop_ennemi(TANK * tmp) {

	char c;
	int avancer = 0;

	srand(time(NULL));

	while(tmp != NULL) {

		avancer = rand()%6;
		c = direction_aleatoire(tmp, avancer);
		
		for(int i=0; i<3; i++) {
			avancement_tank(tmp, c);
		}

		usleep(90000);
		tmp = tmp->next;
    }
}