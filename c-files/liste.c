#include "fonction.h"

void ajoutEnTete(TANK** tete_ref, char direction, int y, int blindage){

	TANK * new_ennemi = (TANK*)malloc(sizeof(TANK));

	init_ennemi(new_ennemi, direction, y, blindage);

	switch(direction)
	{

	case 'N': //deplacement
		switch(blindage) {
			case 0 :chargement_tank(new_ennemi, "../tanks/tankH.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(new_ennemi, "../tanks/tankblindeH.txt");break;
			case 2 :chargement_tank(new_ennemi, "../tanks/tankultrablindeH.txt");break;
		}
		afficher_tank(new_ennemi);
	break;

	case 'O':
		switch(blindage) {
			case 0 :chargement_tank(new_ennemi, "../tanks/tankG.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(new_ennemi, "../tanks/tankblindeG.txt");break;
			case 2 :chargement_tank(new_ennemi, "../tanks/tankultrablindeG.txt");break;
		}
		afficher_tank(new_ennemi);
	break;
		
	case 'S':
		switch(blindage) {
			case 0 :chargement_tank(new_ennemi, "../tanks/tankB.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(new_ennemi, "../tanks/tankblindeB.txt");break;
			case 2 :chargement_tank(new_ennemi, "../tanks/tankultrablindeB.txt");break;
		}
		afficher_tank(new_ennemi);
	break;
	
	case 'E':
		switch(blindage) {
			case 0 :chargement_tank(new_ennemi, "../tanks/tankD.txt"); break;//alors on pivote le tank
			case 1 :chargement_tank(new_ennemi, "../tanks/tankblindeD.txt");break;
			case 2 :chargement_tank(new_ennemi, "../tanks/tankultrablindeD.txt");break;
		}
		afficher_tank(new_ennemi);
	break;
	}

	new_ennemi->next = (*tete_ref);
	(*tete_ref) = new_ennemi;
}

int estVide(TANK** liste) {

	if(*liste == NULL) {
		return 1;
	} else {
		return 0;
	}
}

void supprimerTankEnnemi(TANK **tete_ref, int position) {

	//etat = 3 pour inactif

	if(*tete_ref == NULL) {
		return;
	}

	TANK * tmp = *tete_ref;

	if(position == 0) {
		*tete_ref = tmp->next;
		free(tmp);
		return;
	}

	for(int i=0; tmp!=NULL && i<position-1; i++) {
		tmp = tmp->next;
	}

	if(tmp == NULL || tmp->next == NULL) {
		return;
	}

	TANK *next = tmp->next->next;

	free(tmp->next);

	tmp->next = next;
}