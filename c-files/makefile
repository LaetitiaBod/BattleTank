Executer : EXEC clear
	./EXEC
	@echo "Ca a réussi"

EXEC : main.o init-jeu.o tank.o obus.o liste.o ennemi.o
	gcc main.o init-jeu.o tank.o obus.o liste.o ennemi.o -o EXEC

main.o : main.c fonction.h
	gcc -c main.c

init-jeu.o : init-jeu.c fonction.h
	gcc -c init-jeu.c

tank.o : tank.c fonction.h
	gcc -c tank.c

obus.o : obus.c fonction.h
	gcc -c obus.c

liste.o : liste.c fonction.h
	gcc -c liste.c

ennemi.o : ennemi.c fonction.h
	gcc -c ennemi.c

clear : 
	rm *.o