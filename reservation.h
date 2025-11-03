#ifndef RESERVATION_H
#define RESERVATION_H

typedef struct {
    int id;
    char nom[50];
    char date[20];
    char creneau[10];
    int quantite;
} Reservation;

void ajouter_reservation(Reservation r);
int verifier_disponibilite(int id, char date[], char creneau[], int quantite);
void supprimer_reservation(int id, char date[], char creneau[]);

#endif
