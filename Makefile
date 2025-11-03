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

