#include "fonction.h"

void init_montank(TANK * montank)
{

	int x = 35;
	int y = 70;
	int i;
	int j;
	
	montank -> direction = 'N';
	montank -> posx = x;
	montank -> posy = y;
	montank -> blindage = 0;
	montank -> type = 'm';
	montank -> etat = 1; //nb de vies
	
	completer_fakemap(montank);
}

void completer_fakemap(TANK * tank) {

	for(int i = tank->posx; i< tank->posx+haut; i++)
	{
		for(int j = tank->posy; j <= tank->posy+8; j++)
		{
			if(tank->type == 'm') {
				IMAGE2[i][j] = 'm';
			} else if(tank->type == 'e') {
				IMAGE2[i][j] = 'e';
			}
		}
	}
}

void chargement_tank(TANK * tank, char * nom_fic) {

	int i, j; 
	char c;
	FILE * fic = fopen(nom_fic, "r");//r pour read

	for (i=0; i< haut; i++) {
	j=0;
		while((c = fgetc(fic)) != '\n' ){
			tank->carrosserie[i][j] = c;
			j++;
		}
		tank->carrosserie[i][j] = '\0';
	}
	fclose(fic);
}

void afficher_tank(TANK * tank) {

	int x = tank->posx+1, y = tank->posy+1;

	for(int i = 0; i < haut; i++) {
		printf("\033[%d;%dH", x,y); //on met le curseur en début de ligne
		couleur_tank(tank);
		printf("%s", tank->carrosserie[i]); //on affiche la ligne
		printf("\n");
		x++; //on passe a la ligne suivante
	}
	printf("\n");
}

void couleur_tank(TANK * tank) {

	if(tank->type == 'm') { //bleu
		printf("\x1B[34m"); 
	}else if(tank->type == 'e') {
		if(tank->blindage == 0) { //vert
			printf("\x1B[32m");
		} else if(tank->blindage == 1) { //jaune
			printf("\x1B[33m");
		} else if(tank->blindage == 2) { //rouge
			printf("\x1B[31m");
		}
	}
}

void deplacer_tank_bas(TANK * tank, int k) {

	int x = tank->posx, y = tank->posy;
	int continuer = 0;
	
	for(int i = k; i < 9; i++) { //i=1 pour les ennemis / i=0 pour les murs
		if(IMAGE2[x+5][y+i] == ' ') { //x+4/y-1+i pour les murs, x+5/y+i pour les ennemis
				continuer = 1;
		} else {
			continuer = 0;
			i = 9;
		}
	}

	if(continuer == 1) {
		for(int i = 0; i < 9; i++)
		{
			IMAGE2[x][y+i] = ' ';
			printf("\033[%d;%dH", x+1, y+1+i);
			printf(" \n");
		}
		tank->posx++;
		completer_fakemap(tank);
	}
	tank->direction = 'S';
	afficher_tank(tank);
}

void deplacer_tank_droite(TANK * tank, int k) {

	int x = tank->posx, y = tank->posy;
	int continuer = 0;

	for(int i = k; i < 5; i++) { //i=0 pour les murs / i=1 pour les ennemis
		if(IMAGE2[x+i][y+9] == ' ') { //x-1+i/y+8 pour les murs, x+i/y+9 pour les ennemis
			continuer = 1;
		} else {
		continuer = 0;
		i = 5;
		}	
	}

	if(continuer == 1) {
		for(int i = 0; i < 5; i++)
		{
			IMAGE2[x+i][y] = ' ';
			printf("\033[%d;%dH", x+1+i, y+1);
			printf(" \n");
		}
		tank->posy ++;
		completer_fakemap(tank);
	}
	tank->direction = 'E';
	afficher_tank(tank);
}

void deplacer_tank_gauche(TANK * tank, int k) {

	int x = tank->posx, y = tank->posy;
	int continuer = 0;
	
	for(int i = k; i < 5; i++) { 
		if(IMAGE2[x+i][y-1] == ' ') { 
			continuer = 1;
		} else {
		continuer = 0;
		i = 5;
		}	
	}

	if(continuer == 1) {
		
		for(int i = 0; i < 5; i++)
		{
			IMAGE2[x+i][y+8] = ' ';
			printf("\033[%d;%dH", x+1+i, y+9);
			printf(" \n");
		}
		tank->posy--;
		completer_fakemap(tank);
	}
	tank->direction = 'O';
	afficher_tank(tank);
}

void deplacer_tank_haut(TANK * tank, int k) {

	int j, x = tank->posx, y = tank->posy;
	int continuer = 0;
	
	for(int i = k; i < 9; i++) { // i=0 pour les murs / i=1 pour les ennemis
		if(IMAGE2[x-1][y+i] == ' ') { //x-2/y-1+i pour les murs, x-1/y+i pour les ennemis
			continuer = 1;
		} else {
		continuer = 0;
		i = 9;
		}	
	}
	
	if(continuer == 1) {
		for(int i = 0; i < 9; i++)
		{
			IMAGE2[x+4][y+i] = ' ';
			printf("\033[%d;%dH", x+5, y+1+i);
			printf(" \n");
		}
		tank->posx--;
		completer_fakemap(tank);
	}
	tank->direction = 'N';
	afficher_tank(tank); //affichage de la nouvelle position
}

void avancement_tank(TANK * montank, char c)
{

	system("stty -echo"); //saisie cachée

	int k = 0; // k = 0 collision avec les murs. k = 1 pour les collisions avec les tanks ennemis

	switch(c)
	{

	case 'z': //deplacement
	if(montank->direction != 'N') {	//pas dans la bonne direction ?
		switch(montank->blindage) {
			case 0 :chargement_tank(montank, "../tanks/tankH.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(montank, "../tanks/tankblindeH.txt");break;
			case 2 :chargement_tank(montank, "../tanks/tankultrablindeH.txt");break;
		}
		afficher_tank(montank);
	}
		deplacer_tank_haut(montank, k); //obstacle ? non -> on déplace (effacer/incrémenter/afficher)
	break;

	case 'q':
	if(montank->direction != 'O') {
		switch(montank->blindage) {
			case 0 :chargement_tank(montank, "../tanks/tankG.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(montank, "../tanks/tankblindeG.txt");break;
			case 2 :chargement_tank(montank, "../tanks/tankultrablindeG.txt");break;
		}
		afficher_tank(montank);
	}
		deplacer_tank_gauche(montank, k);
	break;
		
	case 's':
	if(montank->direction != 'S') {
		switch(montank->blindage) {
			case 0 :chargement_tank(montank, "../tanks/tankB.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(montank, "../tanks/tankblindeB.txt");break;
			case 2 :chargement_tank(montank, "../tanks/tankultrablindeB.txt");break;
		}
		afficher_tank(montank);
	}
		deplacer_tank_bas(montank, k);
	break;
	
	case 'd':
	if(montank->direction != 'E') {
		switch(montank->blindage) {
			case 0 :chargement_tank(montank, "../tanks/tankD.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(montank, "../tanks/tankblindeD.txt");break;
			case 2 :chargement_tank(montank, "../tanks/tankultrablindeD.txt");break;
		}
		afficher_tank(montank);
	}
		deplacer_tank_droite(montank, k);
	break;
	
	default: break;
	}
}

void destruction_tank(TANK * tank) {
	
	int enDestruction = 0;

	//on affiche le tank en destruction
    while(enDestruction <= 1000) {
    	for(int i=0; i<5; i++) {
			for(int j=0; j<9; j++) {
				printf("\033[%d;%dH", tank->posx+1+i, tank->posy+1+j); //on efface le tank visuellement
				couleur_tank(tank);
	    		printf("x");
	    	}
	    } 
	    enDestruction++;
	}

	//puis on supprime/efface le tank de la map
	for(int i=0; i<5; i++) {
		for(int j=0; j<9; j++) {
	   		IMAGE2[tank->posx+i][tank->posy+j] = ' '; //on efface le tank de la fausse carte
	    	printf("\033[%d;%dH", tank->posx+1+i, tank->posy+1+j); //on efface le tank visuellement
	    	printf(" ");
	   	}
	}
}

void afficher_message_vies(TANK * tank) {

	printf("\033[%d;%dH", 51, 10);
	printf("\x1B[33m");
	printf("%d X 💛", tank->etat);
}