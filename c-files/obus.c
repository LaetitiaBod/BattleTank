#include "fonction.h"

void init_obus(TANK * montank)
{
	if(premiereCaseVide() < NbMaxObus) {

		pointeurOBUS unobus = malloc(sizeof(OBUS));	
		unobus->direction = montank->direction;
		unobus->tableau = 'o';
	
		switch(unobus->direction)
		{
			case 'N' :
			unobus->posx = montank->posx-1;
			unobus->posy = montank->posy+4;
			break;
			
			case 'S' :
			unobus->posx = montank->posx+5;
			unobus->posy = montank->posy+4;
			break;

			case 'E' :
			unobus->posx = montank->posx+2;
			unobus->posy = montank->posy+9;
			break;

			case 'O' :
			unobus->posx = montank->posx+2;
			unobus->posy = montank->posy-1;
			break;
		}
		tabObus[premiereCaseVide()] = unobus;
	}
}


void afficher_obus(OBUS * unobus) {

	int i, j, x = unobus->posx+1, y = unobus->posy+1;

	printf("\033[%d;%dH", x,y); //on met le curseur en début de ligne
	printf("%c", unobus->tableau); //on affiche la ligne
}


void deplacer_obus_bas(OBUS * obus) {

	IMAGE2[obus->posx][obus->posy] = 'b'; 
	usleep(100000);
		
	printf("\033[%d;%dH", obus->posx+1, obus->posy+1);
	printf(" ");
	IMAGE2[obus->posx][obus->posy] = ' ';

	obus->posx++;
	afficher_obus(obus);
}

void deplacer_obus_droite(OBUS * obus) {
	
	IMAGE2[obus->posx][obus->posy] = 'b'; 
	usleep(50000);

	printf("\033[%d;%dH", obus->posx+1, obus->posy+1);
	printf(" ");
	IMAGE2[obus->posx][obus->posy] = ' ';
	
	obus->posy++;
	afficher_obus(obus);
}

void deplacer_obus_gauche(OBUS * obus) {

	IMAGE2[obus->posx][obus->posy] = 'b'; 
	usleep(50000);

	printf("\033[%d;%dH", obus->posx+1, obus->posy+1);
	printf(" ");
	IMAGE2[obus->posx][obus->posy] = ' ';

	obus->posy--;
	afficher_obus(obus);
}

void deplacer_obus_haut(OBUS * obus) {

	IMAGE2[obus->posx][obus->posy] = 'b';
	usleep(100000);

	printf("\033[%d;%dH", obus->posx+1, obus->posy+1);
	printf(" ");
	IMAGE2[obus->posx][obus->posy] = ' ';
	
	obus->posx--;
	afficher_obus(obus); 
}

void lancer_obus(pointeurOBUS newobus)
{
	switch(newobus->direction)
	{
	/*case 'N':
	if(IMAGE2[newobus->posx-1][newobus->posy] == ' ') {
		deplacer_obus_haut(newobus);
	} else {
		printf("\033[%d;%dH", newobus->posx+1, newobus->posy+1);
		printf(" ");
		for(int j = 0; j < 9; j++) {
			if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'R')
			{
				IMAGE2[newobus->posx][newobus->posy-4+j] = ' ';
				printf("\033[%d;%dH", newobus->posx+1, newobus->posy-3+j);
				printf(" ");
			} else if(IMAGE2[newobus->posx-1][newobus->posy-4+j] == 'R')
			{
				IMAGE2[newobus->posx-1][newobus->posy-4+j] = ' ';
				printf("\033[%d;%dH", newobus->posx, newobus->posy-3+j);
				printf(" ");
			}
		}
		free(newobus);
	}
	break;

	case 'S':
	if(IMAGE2[newobus->posx+1][newobus->posy] == ' ') {
		deplacer_obus_bas(newobus);
	} else {
		printf("\033[%d;%dH", newobus->posx+1, newobus->posy+1);
		printf(" ");
		for(int j = 0; j < 9; j++) {
			if(IMAGE2[newobus->posx][newobus->posy-4+j] == 'R') 
			{
				IMAGE2[newobus->posx][newobus->posy-4+j] = ' ';
				printf("\033[%d;%dH", newobus->posx+1, newobus->posy-3+j);
				printf(" ");
			} else if(IMAGE2[newobus->posx+1][newobus->posy-4+j] == 'R') 
			{
				IMAGE2[newobus->posx+1][newobus->posy-4+j] = ' ';
				printf("\033[%d;%dH", newobus->posx+2, newobus->posy-3+j);
				printf(" ");
			}
		}
		free(newobus);
	}
	break;

	case 'E': //fini
	if(IMAGE2[newobus->posx][newobus->posy+1] == ' ') {
		deplacer_obus_droite(newobus);
	} else {
		printf("\033[%d;%dH", newobus->posx+1, newobus->posy+1);
		printf(" ");
		for(int j = 0; j < 5; j++) {
			if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'R') 
			{
				for(int i = 0; i < 2; i++) { 
					IMAGE2[newobus->posx-2+j][newobus->posy+i] = ' '; 
					printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1+i); 
					printf(" ");
				}
			} else if(IMAGE2[newobus->posx-2+j][newobus->posy+1] == 'R') 
			{
				for(int i = 0; i < 2; i++) { 
					IMAGE2[newobus->posx-2+j][newobus->posy+1+i] = ' '; 
					printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+2+i); 
					printf(" ");
				}
			}
		}
		free(newobus);
	}
	break;

	case 'O': //fini
	if(IMAGE2[newobus->posx][newobus->posy-1] == ' ') {
		deplacer_obus_gauche(newobus);
	}else {
		printf("\033[%d;%dH", newobus->posx+1, newobus->posy+1);
		printf(" ");
		for(int j = 0; j < 5; j++) {
			if(IMAGE2[newobus->posx-2+j][newobus->posy] == 'R') 
			{
				for(int i = 0; i < 2; i++) {
					IMAGE2[newobus->posx-2+j][newobus->posy-i] = ' ';
					printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy+1-i);
					printf(" ");
				}	
			} else if(IMAGE2[newobus->posx-2+j][newobus->posy-1] == 'R') 
			{
				for(int i = 0; i < 2; i++) {
					IMAGE2[newobus->posx-2+j][newobus->posy-1-i] = ' ';
					printf("\033[%d;%dH", newobus->posx-1+j, newobus->posy-i);
					printf(" ");
				}	
			}
		}
		free(newobus);
	}
	break;*/
	case 'N' : break;
	default : break;
	}
}

int premiereCaseVide() {

	int i = 0;

	while(i<NbMaxObus && tabObus[i] != NULL) {
		i++;
	}
	return i;
}

void avancement_obus() {

	for(int i=0; i<NbMaxObus; i++) {
		if(tabObus[i] != NULL) {
			lancer_obus(tabObus[i]);
		}
	}

}

void effacer_obus() {

	for(int i=0; i<NbMaxObus; i++) {
		if(tabObus[i] != NULL) {
			printf("\033[%d;%dH", tabObus[i]->posx+1, tabObus[i]->posy+1);
			printf(" ");
			IMAGE2[tabObus[i]->posx][tabObus[i]->posy] = ' ';

			switch(tabObus[i]->direction) {

				case 'N': tabObus[i]->posx--; break;

				case 'S': tabObus[i]->posx++; break;

				case 'E': tabObus[i]->posy++; break;

				case 'O': tabObus[i]->posy--; break;
			}
		}
	}

}