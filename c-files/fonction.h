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
	#define NbMaxObus 200

	char IMAGE1[HAUTEUR][LARGEUR];
	char IMAGE2[HAUTEUR][LARGEURBIS];
	int GAGNER;

	typedef struct tank TANK;
	struct tank
	{
		char direction; //N-S-E-O
		int posx, posy; //position du coin haut gauche du tank sur la map
		int blindage; //simple 0 - blindé 1 - suprablindé 2
	
		char carrosserie[haut][larg]; //fichiers .txt

		char type; //e ennemi m ami
		int etat; //nb de vie du tank allié, useless pour les ennemis
		int tirer; //cadence de tir des ennemis, useless pour l'allié
		int deplacer;
	
		struct tank * next;
	};
	
	typedef struct obus OBUS;
	struct obus
	{
		char direction; //N-S-E-O
		int posx, posy; //position de l'obus sur la map
		char origine; //m allié, 0 simple ennemi, 1 blindé ennemi, 2 suprablindé ennemi
		char tableau; // <=> 'o'

		int frequence;
	};

	typedef OBUS * pointeurOBUS;
	
	//pointeur d'obus qui fait que les obus se déplacent tous en meme temps
	pointeurOBUS *tabObus;
	
	//fonctions d'initialisation du jeu
	char key_pressed();
	void mysleep(int NbSecondes);
	void menu();
	
	void chargement_carte(int hauteur, int largeur, char tab[hauteur][largeur], char * nom_fic);
	void afficher_carte(int hauteur, int largeur, char tab[hauteur][largeur]);

	//fin du jeu
	void victoire(char * nom_fic);
	void defaite(char * nom_fic);
	
	//fonctions pour les tanks
	void init_montank(TANK * montank);
	void completer_fakemap(TANK * tank);
	void chargement_tank(TANK * tank, char * nom_fic);
	void afficher_tank(TANK * tank);
	void couleur_tank(TANK * tank);

	void deplacer_tank_bas(TANK * tank, int k);
	void deplacer_tank_haut(TANK * tank, int k);
	void deplacer_tank_droite(TANK * tank, int k);
	void deplacer_tank_gauche(TANK * tank, int k);
	void avancement_tank(TANK * montank, char c);
	void destruction_tank(TANK * tank);

	void afficher_message_vies(TANK * tank);

	//fonctions pour les obus
	void init_obus(TANK * montank);
	void afficher_obus(OBUS * obus);
	void supprimer_obus(OBUS * obus);
	void couleur_obus(OBUS * obus);
	void deplacer_obus(OBUS * obus);
	void lancer_obus(OBUS * obus, TANK * montank, TANK** tete_liste);
	
	//fonctions pour le tableau d'obus
	int premiereCaseVide();
	void avancement_obus(TANK * montank, TANK** tete_liste);
	void delete_tab_obus(pointeurOBUS obus);

	//fonctions pour la liste chainée de tanks
	void ajoutEnTete(TANK** tete_ref, char direction, int y, int blindage);
	int estVide(TANK** liste);
	void supprimerTankEnnemi(TANK **tete_ref, int position);
	
	//fonctions pour le comportement des ennemis
	void init_ennemi(TANK * montank, char direction, int y, int blindage);
	void creer_vague(TANK** tete_ref);
	void mode_facile();
	void mode_difficile();
	char direction_aleatoire(int avancer);
	void pop_ennemi(TANK * tmp);
	void blesser_ennemi(pointeurOBUS obus, TANK** tete_liste);
	void afficher_message_ennemis();

	#endif