#include "fonction.h"

void init_obus(TANK * montank)
{
	if(premiereCaseVide() < NbMaxObus) {

		pointeurOBUS unobus = malloc(sizeof(OBUS));	
		unobus->direction = montank->direction;
		unobus->tableau = 'o';
		unobus->frequence = 1;

		if(montank->type == 'm') {
			unobus->origine = 'm';
		} else if(montank->type == 'e') {
			
			if(montank->blindage == 0) { unobus->origine = '0';
			} else if(montank->blindage == 1) { unobus->origine = '1';
			} else if(montank->blindage == 2) { unobus->origine = '2';
			}
		}
	
		switch(unobus->direction)
		{
			case 'N' : unobus->posx = montank->posx-1; unobus->posy = montank->posy+4; break;
			
			case 'S' :unobus->posx = montank->posx+5; unobus->posy = montank->posy+4; break;

			case 'E' : unobus->posx = montank->posx+2; unobus->posy = montank->posy+9; break;

			case 'O' : unobus->posx = montank->posx+2; unobus->posy = montank->posy-1; break;
		}

		tabObus[premiereCaseVide()] = unobus;
	}
}


void afficher_obus(OBUS * obus) {

	int i, j, x = obus->posx+1, y = obus->posy+1;

	IMAGE2[obus->posx][obus->posy] = 'b'; //on crée l'obus
	printf("\033[%d;%dH", x,y); //on met le curseur en début de ligne
	couleur_obus(obus);
	printf("%c", obus->tableau); //on affiche la ligne
}

void supprimer_obus(OBUS * obus) {

	switch(obus->direction) {

		case 'N' :
		if(IMAGE2[obus->posx+1][obus->posy] != 'm' && IMAGE2[obus->posx+1][obus->posy] != 'e') { //pour ne pas effacer le canon
			IMAGE2[obus->posx+1][obus->posy] = ' '; //on supprime l'obus
			printf("\033[%d;%dH", obus->posx+2, obus->posy+1); //puis on l'efface
			printf(" ");
		}
		break;

		case 'S':
		if(IMAGE2[obus->posx-1][obus->posy] != 'm' && IMAGE2[obus->posx-1][obus->posy] != 'e') {
			IMAGE2[obus->posx-1][obus->posy] = ' '; //on supprime l'obus
			printf("\033[%d;%dH", obus->posx, obus->posy+1); //puis on l'efface
			printf(" ");
		}
		break;

		case 'E':
		if(IMAGE2[obus->posx][obus->posy-1] != 'm' && IMAGE2[obus->posx][obus->posy-1] != 'e') {
			IMAGE2[obus->posx][obus->posy-1] = ' '; //on supprime l'obus
			printf("\033[%d;%dH", obus->posx+1, obus->posy); //puis on l'efface
			printf(" ");
		}
		break;

		case 'O':
		if(IMAGE2[obus->posx][obus->posy+1] != 'm' && IMAGE2[obus->posx][obus->posy+1] != 'e') {
			IMAGE2[obus->posx][obus->posy+1] = ' '; //on supprime l'obus
			printf("\033[%d;%dH", obus->posx+1, obus->posy+2); //puis on l'efface
			printf(" ");
		}
		break;
	}
}

void couleur_obus(OBUS * obus) {

	if(obus->origine == 'm') {
		printf("\x1B[34m");
	}else if(obus->origine == '0') {
		printf("\x1B[32m");
	} else if(obus->origine == '1') {
		printf("\x1B[33m");
	} else if(obus->origine == '2') {
		printf("\x1B[31m");
	}
}

void deplacer_obus(OBUS * obus) {

	supprimer_obus(obus);
	afficher_obus(obus); //puis on l'affiche

	switch(obus->direction) { //on incrémente sa position
		case 'N': obus->posx--; break;
		case 'S': obus->posx++; break;
		case 'E': obus->posy++; break;
		case 'O': obus->posy--; break;
	}
	
}

void lancer_obus(pointeurOBUS newobus, TANK * montank, TANK** tete_liste)
{

	int hurt = 0; int hurted = 0;

	if(newobus->frequence%5000 == 0) { //frequence d'affichage des obus

	if(IMAGE2[newobus->posx][newobus->posy] == ' ') { //on teste si la case devant le canon est vide
		deplacer_obus(newobus); //on remplace cette case vide par un obus qui va se deplacer
	} else {
		
		switch(newobus->direction) {
			case 'N':
				IMAGE2[newobus->posx+1][newobus->posy] = ' ';
				printf("\033[%d;%dH", newobus->posx+2, newobus->posy+1);
				printf(" ");
			
			//situations
			for(int j = 0; j < 9; j++) {
				if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'R') {
					IMAGE2[newobus->posx][newobus->posy-4+j] = ' ';
					printf("\033[%d;%dH", newobus->posx+1, newobus->posy-3+j);
					printf(" ");
				} else if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'W' && newobus->origine == '2') {
					IMAGE2[newobus->posx-1][newobus->posy-4+j] = ' ';
					printf("\033[%d;%dH", newobus->posx, newobus->posy-3+j);
					printf(" ");
				} else if(IMAGE2[newobus->posx][newobus->posy] == 'm') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						hurt = 1;
					}
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'e'  && newobus->origine == 'm') {
					hurted = 1;
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'J') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						montank->etat = 0;
					}
				}
			}
			if(hurt == 1) montank->etat--; afficher_message_vies(montank); hurt = 0;
			if(hurted == 1) blesser_ennemi(newobus, tete_liste); hurted = 0;
			break;

			case 'S' :
				IMAGE2[newobus->posx-1][newobus->posy] = ' '; //on supprime le dernier obus
				printf("\033[%d;%dH", newobus->posx, newobus->posy+1);
				printf(" "); //et on l'efface
			
			//situations
			for(int j = 0; j < 9; j++) { //zone à casser	
				//brique rouge facilement cassables
				if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'R') { 
					IMAGE2[newobus->posx][newobus->posy-4+j] = ' '; //on supprime les briques
					printf("\033[%d;%dH", newobus->posx+1, newobus->posy-3+j); //on efface les briques
					printf(" ");
				}
				//un suprablinde qui casse une brique blanche
				else if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'W' && newobus->origine == '2') { 
					IMAGE2[newobus->posx][newobus->posy-4+j] = ' '; //on supprime les briques
					printf("\033[%d;%dH", newobus->posx+1, newobus->posy-3+j); //on efface les briques
					printf(" ");
				} 
				//je suis touché, je perd une vie (le tank a 3 vies)
				else if(IMAGE2[newobus->posx][newobus->posy] == 'm' ) {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						hurt = 1;
					}
				}
				//un ennemi est touché
				else if(IMAGE2[newobus->posx][newobus->posy] == 'e' && newobus->origine == 'm') {
					hurted = 1;
				}
				//le joker est touché, je perd
				else if(IMAGE2[newobus->posx][newobus->posy] == 'J') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						montank->etat = 0;
					}
				}
			}
			if(hurt == 1) montank->etat--; afficher_message_vies(montank); hurt = 0;
			if(hurted == 1) blesser_ennemi(newobus, tete_liste); hurted = 0;
			break;

			case 'E':
				IMAGE2[newobus->posx][newobus->posy-1] = ' ';
				printf("\033[%d;%dH", newobus->posx+1, newobus->posy);
				printf(" ");
			
			//situations
			for(int j = 0; j < 5; j++) {
				if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'R') 
				{
					for(int i = 0; i < 2; i++) { 
						IMAGE2[newobus->posx-2+j][newobus->posy+i] = ' '; 
						printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1+i); 
						printf(" ");
					}
				} else if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'W' && newobus->origine == '2') 
				{
					for(int i = 0; i < 2; i++) { 
						IMAGE2[newobus->posx-2+j][newobus->posy+i] = ' '; 
						printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1+i); 
						printf(" ");
					}
				} else if(IMAGE2[newobus->posx][newobus->posy] == 'm') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						hurt = 1;
					}
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'e' && newobus->origine == 'm') {
					hurted = 1;
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'J') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						montank->etat = 0;
					}
				}
			}
			if(hurt == 1) montank->etat--; afficher_message_vies(montank); hurt = 0;
			if(hurted == 1) blesser_ennemi(newobus, tete_liste); hurted = 0;
			break;

			case 'O': //fini
				IMAGE2[newobus->posx][newobus->posy+1] = ' ';
				printf("\033[%d;%dH", newobus->posx+1, newobus->posy+2);
				printf(" ");
			

			//situations
			for(int j = 0; j < 5; j++) {
				if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'R') 
				{
					for(int i = 0; i < 2; i++) {
						IMAGE2[newobus->posx-2+j][newobus->posy-i] = ' ';
						printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1-i);
						printf(" ");
					}	
				} else if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'W' && newobus->origine == '2') 
				{
					for(int i = 0; i < 2; i++) {
						IMAGE2[newobus->posx-2+j][newobus->posy-i] = ' ';
						printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1-i);
						printf(" ");
					}	
				} else if(IMAGE2[newobus->posx][newobus->posy] == 'm') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						hurt = 1;
					}
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'e' && newobus->origine == 'm') {
					hurted = 1;
				}
				else if(IMAGE2[newobus->posx][newobus->posy] == 'J') {
					if(newobus->origine == '0' || newobus->origine == '1' || newobus->origine == '2') {
						montank->etat = 0;
					}
				}
			}
			if(hurt == 1) montank->etat--; afficher_message_vies(montank); hurt = 0;
			if(hurted == 1) blesser_ennemi(newobus, tete_liste); hurted = 0;
			break;
		} //fin du switch
		delete_tab_obus(newobus);
	} //fin du if
		newobus->frequence = 0;
	} newobus->frequence++;
}

int premiereCaseVide() {

	int i = 0;

	while(i<NbMaxObus && tabObus[i] != NULL) {
		i++;
	}
	return i;
}

void avancement_obus(TANK * montank, TANK** tete_liste) {

	for(int i=0; i<NbMaxObus; i++) {
		if(tabObus[i] != NULL) {
			lancer_obus(tabObus[i], montank, tete_liste);
		} 
	}
}

void delete_tab_obus(pointeurOBUS obus) {

	int i = 0;

	while(i<NbMaxObus) {
		if(tabObus[i] == obus) {
			free(tabObus[i]);
			tabObus[i] = NULL;
		} i++;
	}
}