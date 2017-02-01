
All : projet

entree_sortie.o : entree_sortie.c entree_sortie.h
	gcc -c -o entree_sortie.o entree_sortie.c

exo1.o : exo1.c exo1.h
	gcc -c -o exo1.o exo1.c

main.o : main.c exo1.h
	gcc -c -o main.o main.c

projet : main.o exo1.o entree_sortie.o
	gcc -o projet main.o exo1.o entree_sortie.o

clean : 
	rm -f *.o projet
