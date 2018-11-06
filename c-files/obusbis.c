#include "fonction.h"


void init_obus(TANK * montank){

	if(est_vide() < NbMaxObus) {

	OBUS * obus = malloc(sizeof(OBUS));
	
	obus->tableau = 'o';
	obus->direction = montank->direction;
	
	switch(montank->direction)
	{
		case 'N' :
		obus->posx = montank->posx-1;
		obus->posy = montank->posy+4;
		break;
		
		case 'S' :
		obus->posx = montank->posx+5;
		obus->posy = montank->posy+4;
		break;

		case 'E' :
		obus->posx = montank->posx+2;
		obus->posy = montank->posy+9;
		break;

		case 'O' :
		obus->posx = montank->posx+2;
		obus->posy = montank->posy-1;
		break;

		default :
		break;
	}
	
	//IMAGE1[obus->posx][obus->posy] = 'b';
	tabObus[est_vide()] = obus;
	}
}

void afficher_obus(OBUS * unobus) {

	int i, j, x = unobus->posx, y = unobus->posy;

		printf("\033[%d;%dH", x,y); //on met le curseur en début de ligne
		printf("%c", unobus->tableau); //on affiche la ligne

	printf("\n");
}


void deplacer_obus_bas(OBUS * obus) {

	afficher_obus(obus);
	mysleep(100000);

	int i, x = obus->posx, y = obus->posy;
		
		printf("\033[%d;%dH", x, y);
		printf(" \n");
	obus->posx++;
}

void deplacer_obus_droite(OBUS * obus) {

	afficher_obus(obus);
	mysleep(50000);

	int i, x = obus->posx, y = obus->posy;
	
		printf("\033[%d;%dH", x, y);
		printf(" \n");
	obus->posy++;
}

void deplacer_obus_gauche(OBUS * obus) {

	afficher_obus(obus);
	mysleep(50000);

	int i, x = obus->posx, y = obus->posy;
		printf("\033[%d;%dH", x, y);
		printf(" \n");
	obus->posy--;

}

void deplacer_obus_haut(OBUS * obus) {

	afficher_obus(obus);
	mysleep(100000);

	int i, x = obus->posx, y = obus->posy;

		printf("\033[%d;%dH", x, y);
		printf(" \n");
	obus->posx--;
}

void lancer_obus(OBUS * newobus)
{
	
		switch(newobus->direction)
		{
		case 'N':
		if(newobus->posy <= LARGEUR && newobus->posy >= 0 && newobus->posx < HAUTEUR-1 && newobus->posx > 0 && IMAGE2[newobus->posx-1][newobus->posy-1] == ' ') {
			afficher_obus(newobus);
			fflush(stdout);
			IMAGE2[newobus->posx-1][newobus->posy-1] = 'o';
		} else {
			for(int j = 0; j < 9; j++) {
				if(IMAGE2[newobus->posx-1][newobus->posy-5+j] == 'R')
				{
					IMAGE2[newobus->posx-1][newobus->posy-5+j] = ' ';
					printf("\033[%d;%dH", newobus->posx, newobus->posy-4+j);
					printf(" ");
				}
			}
			supprimer_obus(newobus);
		}
		break;
	
		case 'S':
		if(newobus->posy <= LARGEUR && newobus->posy >= 0 && newobus->posx < HAUTEUR-1 && newobus->posx > 0 && IMAGE2[newobus->posx-1][newobus->posy-1] == ' ') {
			afficher_obus(newobus);
			fflush(stdout);
			IMAGE2[newobus->posx-1][newobus->posy-1] = 'o';
		} else {
			for(int j = 0; j < 9; j++) {
				if(IMAGE2[newobus->posx-1][newobus->posy-5+j] == 'R') 
				{
					IMAGE2[newobus->posx-1][newobus->posy-5+j] = ' ';
					printf("\033[%d;%dH", newobus->posx, newobus->posy-4+j);
					printf(" ");
				}
			}
			supprimer_obus(newobus);
		}
		break;
	
		case 'E':
		if(newobus->posy <= LARGEUR && newobus->posy >= 0 && newobus->posx < HAUTEUR-1 && newobus->posx > 0 && IMAGE2[newobus->posx-1][newobus->posy-1] == ' ') {
			afficher_obus(newobus);
			fflush(stdout);
			IMAGE2[newobus->posx-1][newobus->posy-1] = 'o';
		} else {
			for(int j = 0; j < 5; j++) {
				if(IMAGE2[newobus->posx-3+j][newobus->posy-1] == 'R') 
				{
					for(int i = 0; i < 2; i++) {
						IMAGE2[newobus->posx-3+j][newobus->posy-1+i] = ' ';
						printf("\033[%d;%dH", newobus->posx-2+j, newobus->posy);
						printf(" ");
					}
				}
			}
			supprimer_obus(newobus);
		}
		break;
	
		case 'O':
		if(newobus->posy <= LARGEUR && newobus->posy >= 0 && newobus->posx < HAUTEUR-1 && newobus->posx > 0 && IMAGE2[newobus->posx-1][newobus->posy-1] == ' ') {
			afficher_obus(newobus);
			fflush(stdout);
			IMAGE2[newobus->posx-1][newobus->posy-1] = 'o';
		} else {
			supprimer_obus(newobus);
			for(int j = 0; j < 5; j++) {
				if(IMAGE2[newobus->posx-3+j][newobus->posy-1] == 'R') 
				{
					for(int i = 0; i < 2; i++) {
						IMAGE2[newobus->posx-3+j][newobus->posy-1-i] = ' ';
						printf("\033[%d;%dH", newobus->posx-2+j, newobus->posy);
						printf(" ");
					}
				}
			}
			supprimer_obus(newobus);
		 }
		break;
		}
}

int est_vide() {

	int i = 0;

	while(i < NbMaxObus && tabObus[i] != NULL) {
		i++;
		return i;
	}
}

void supprimer_obus(OBUS * obus) {

	int i = 0;
	while(i < NbMaxObus) {
		if(tabObus[i] == obus) {
			free(tabObus[i]);
			tabObus[i] = NULL;
		}
		i++;
	}
}

void avancement_obus() {

	for(int i=0; i<NbMaxObus; i++) {
		if(tabObus[i] != NULL) {
			//lancer_obus(tabObus[i]);
		}
	}

	mysleep(75000);

	for(int i=0; i<NbMaxObus; i++) {
		if(tabObus[i] != NULL) {

			printf("\033[%d;%dH", tabObus[i]->posx, tabObus[i]->posy);
			printf(" ");
			IMAGE2[tabObus[i]->posx][tabObus[i]->posy] = ' ';

			switch(tabObus[i]->direction){
			case 'N':
				tabObus[i]->posx--; break;

			case 'O': 
				tabObus[i]->posy--; break;
			
			case 'S': 
				tabObus[i]->posx++; break;
			
			case 'E': 
				tabObus[i]->posy++; break;
			}
		}
	}
}