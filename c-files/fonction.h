#ifndef DEF_FONCTION
#define DEF_FONCTION

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

	#define HAUTEUR 49
	#define LARGEUR 300
	#define LARGEURBIS 200
	#define haut 5
	#define larg 28
	#define h 1
	#define l 1
	
	int NbMaxObus;
	char IMAGE1[HAUTEUR][LARGEUR];
	char IMAGE2[HAUTEUR][LARGEURBIS];

	typedef struct tank TANK;
	struct tank
	{
		char direction;
		int posx, posy;
		int blindage;
	
		int blindage_orig;
		int touches;
		char carrosserie[haut][larg];

		char type;
		int etat;
	
		int mise_a_jour;
	
		struct tank * next;
	};
	
	typedef struct obus OBUS;
	struct obus
	{
		char direction;
		int posx, posy;
		char origine;
		char tableau;
	};

	typedef OBUS * pointeurOBUS;
	
	pointeurOBUS *tabObus;
	
	char key_pressed();
	void mysleep(int NbSecondes);
	void menu();
	
	void chargement_carte(int hauteur, int largeur, char tab[hauteur][largeur], char * nom_fic);
	void afficher_carte(int hauteur, int largeur, char tab[hauteur][largeur]);
	
	void init_montank(TANK * montank);
	void chargement_tank(TANK * tank, char * nom_fic);
	void afficher_tank(TANK * tank);

	void deplacer_tank_bas(TANK * tank, int k);
	void deplacer_tank_haut(TANK * tank, int k);
	void deplacer_tank_droite(TANK * tank, int k);
	void deplacer_tank_gauche(TANK * tank, int k);
	void avancement_tank(TANK * montank, char c);

	void init_obus(TANK * montank);
	//pointeurOBUS init_obus(TANK * montank);
	void afficher_obus(OBUS * unobus);
	void completer_fakemap(TANK * tank);
	void vider_fakemap(TANK * tank);
	
	void deplacer_obus_bas(OBUS * obus);
	void deplacer_obus_haut(OBUS * obus);
	void deplacer_obus_droite(OBUS * obus);
	void deplacer_obus_gauche(OBUS * obus);
	
	void lancer_obus(OBUS * obus);
	int premiereCaseVide();
	void avancement_obus();

	void ajoutEnTete(TANK** tete_ref, char direction, int y, int blindage);
	int estVide(TANK** liste);
	void supprimerTankEnnemi(TANK **tete_ref, int position);
	
	void init_ennemi(TANK * montank, char direction, int y, int blindage);
	void creer_vague(TANK** tete_ref);
	void mode_facile();
	char direction_aleatoire(TANK * tmp, int avancer);
	void pop_ennemi(TANK * tmp);

	#endif