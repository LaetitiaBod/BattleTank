Consignes avant de lancer le programme :

---> Mettre en plein écran (f11) sinon risque de décalage
---> Préférez un dual boot et un ordi reposé plutôt qu'une VM et un ordi chauffé
---> Installer la bibliothèque pour les émoticones (cf sujet pour les commandes)
---> Ne pas hésiter à relancer le jeu pour éviter des erreurs de segmentation qui surviennent au cours du jeu (1 fois sur 5 environ)
---> Préférez un casque ou des écouteurs pour le son (il n'est pas très fort en haut parleur)


Pour lancer le programme --->
$ sudo apt install make
$ sudo apt install gcc
$ sudo apt-get install sox
$ sudo apt-get install libsox-fmt-all
$ cd c-files/
$ make

Pour quitter le programme --->
une fois le jeu lançé, appuyer sur p


Bugs non résolus :

	* Le spawn en haut à droite ne fonctionne pas très bien sur la détection du vide

	* Erreur de segmentation qui surviennent (aléatoirement ?)

	* Canon de tank qui s'effacent de façon temporaire

	* Certaines briques se cassent de façon inapropriée

	* Possibilité de bugs d'affichage
