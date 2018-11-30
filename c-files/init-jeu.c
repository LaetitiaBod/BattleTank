#include "fonction.h"

char key_pressed()
{
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;
	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl(STDIN_FILENO, F_SETFL, oldfd);
	if (c != EOF) {ungetc(c, stdin); result = getchar();}
	return result;
}

void mysleep(int NbSecondes)
{
    int i = 0; 
    int j = 0;
	
	while(i <= NbSecondes){
		j = rand()%10;		
		if (j == 5) {
			i++;
		}
	}
}

void menu() {

	char choix;

	//on cache la compilation
	system("setterm -cursor off"); //clignement du curseur enlevé
	system("stty -echo"); //saisie cachée
	
	//on affiche le menu
	system("clear");
	system("cat ../menu-obus-carte-fin/menu.txt");

	//on réactive la saisie pour le choix de l'utilisateur
	system("stty echo");
	system("setterm -cursor on");
	
	//on demande à l'utilisateur le mode désiré
	printf("\033[%d;%dH", 33, 1);
	do { scanf("%c", &choix);
	} while (choix !='1' && choix !='2' && choix != 'p');

		if(choix == '1'){
			mode_facile();
		} else if(choix == '2'){
			mode_difficile(); 
		} else if(choix == 'p'){
			exit(0);
		}

	//on éteint de nouveau le curseur pour le bon déroulement du jeu
	system("setterm -cursor off"); 
	system("stty -echo");
	system("clear");
}


void chargement_carte(int hauteur, int largeur, char tab[hauteur][largeur], char * nom_fic) { //charge l'image

	int i, j;
	char c;
	FILE * fic = fopen(nom_fic, "r");//r pour read

	for (i=0; i< hauteur; i++) {
	j=0;
		while((c = fgetc(fic)) !='\n')
		{
			tab[i][j] = c;
			j++;
		}
		tab[i][j] = '\0';
	}
	fclose(fic);
}

void afficher_carte(int hauteur, int largeur, char tab[hauteur][largeur]) {

	int i, j;

	for(i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
            
			printf("%c", tab[i][j]); 
			
		} printf("\n");
	}
}

void victoire(char * nom_fic) {

	char c;

	system("clear");
	system("../audio/./son.sh ../audio/victoire.mp3");
	FILE  * fic = fopen(nom_fic, "r");
	
	printf("\x1B[34m"); //bleu
	while ((c=fgetc(fic)) != EOF) {
		printf("%c", c);
	}
	fclose (fic);
}

void defaite(char * nom_fic) {

	char c;

	system("clear");
	FILE  * fic = fopen(nom_fic, "r");
	
	printf("\x1B[32m"); //vert 
	while ((c=fgetc(fic)) != EOF) {
		printf("%c", c);
	}
	fclose (fic);
}