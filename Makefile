<<<<<<< HEAD
all: main.o equipement.o reservation.o
	gcc -Wall -o salle_sport main.o equipement.o reservation.o

main.o: main.c equipement.h reservation.h
	gcc -c main.c

equipement.o: equipement.c equipement.h
	gcc -c equipement.c

reservation.o: reservation.c reservation.h
	gcc -c reservation.c

clean:
	rm -f *.o salle_sport

=======
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
>>>>>>> 905f79b4b307ebb2e2c4cd1b0d67d75839b74f9c
