
All : projet

entree_sortie.o : entree_sortie.c entree_sortie.h
	gcc -c -o entree_sortie.o entree_sortie.c

exo1.o : exo1.c exo1.h entree_sortie.h
	gcc -c -o exo1.o exo1.c

main.o : main.c exo1.h exo2.h
	gcc -c -o main.o main.c

exo2.o : exo2.c exo2.h entree_sortie.h
	gcc -c -o exo2.o exo2.c 

projet : main.o exo1.o entree_sortie.o exo2.o
	gcc -o projet main.o exo1.o entree_sortie.o exo2.o

clean : 
	rm -f *.o projet
