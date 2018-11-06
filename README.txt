Consigne avant de lancer le programme 

---> Mettre en plein écran (f11) sinon risque de décalage
---> Eviter les VMs (le jeu lag fortement)
---> Installer la bibliothèque pour les émoticones (cf sujet pour les commandes)

Pour lancer le programme ---> 
$ cd Projet\ C/c-files/
$ make

Pour quitter le programme --->
une fois le jeu lançé, appuyer sur p

Bugs non résolus :

	* Le spawn en haut à droite ne fonctionne pas sur la détection du vide

	
	* Un seul obus peut être lancé et par les ennemis et par le joueur !


	* La fonction lancer_obus crée un core dump sans en avoir modifié l'intérieur (les "case" buguent sauf "default")