all: main.o centre.o inscription.o
	gcc -Wall -o gestion main.o centre.o inscription.o

main.o: main.c centre.h inscription.h
	gcc -c main.c

centre.o: centre.c centre.h
	gcc -c centre.c

inscription.o: inscription.c inscription.h
	gcc -c inscription.c

clean:
	rm *.o gestion
