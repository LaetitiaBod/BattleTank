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
/*
void mysleep(int NbSecondes)
{
    int i = 0, 
    int j = 0;
	
	while(i <= NbSecondes){
		j = rand()%10;		
		if (n == 5) {
			i++;
		}
	}
}
*/
void menu() {

	int choix;
	char c;

	system("clear");
	FILE  * fic = fopen("../menu-obus-carte-fin/menu.txt", "r");
	
	while ((c=fgetc(fic)) != EOF) {
		printf("%c", c);
	}

	fclose (fic);

	do { scanf("%d", &choix); 
	} while (choix !=1 && choix !=2 && choix !=3 && choix!=4);	

	if(choix == 1){
		//chargement_carte("cartebis.txt");  
	} else if(choix == 2){
		//chargement_carte("cartebis.txt");  
	} else if(choix == 3){
		//chargement_carte("cartebis.txt");   
	}
}


void chargement_carte(int hauteur, int largeur, char tab[hauteur][largeur], char * nom_fic) { //charge l'image

	int i, j;
	char c;
	FILE * fic = fopen(nom_fic, "r");//r pour read

	for (i=0; i< HAUTEUR; i++) {
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