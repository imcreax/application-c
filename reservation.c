#include <stdio.h>
#include <string.h>
#include "reservation.h"
#include "equipement.h"

#define FICHIER_RES "data/reservations.txt"
#define FICHIER_EQUIPE "data/affichage_equipements.txt"

int verifier_disponibilite(int id, char date[], char creneau[], int quantite) {
    FILE *f = fopen(FICHIER_EQUIPE, "r");
    if (f == NULL) return 0;

    Equipement e;
    while (fscanf(f, "%d %49s %d %19s", &e.id, e.nom, &e.quantite, e.etat) == 4) {
        if (e.id == id && strcmp(e.etat, "disponible") == 0 && e.quantite >= quantite) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
void ajouter_reservation(Reservation r) {
    FILE *f = fopen(FICHIER_RES, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %s %s %d\n", r.id, r.nom, r.date, r.creneau, r.quantite);
        fclose(f);
    }
}

void supprimer_reservation(int id, char date[], char creneau[]) {
    FILE *f = fopen(FICHIER_RES, "r");
    FILE *tmp = fopen("data/tmp_res.txt", "w");
    Reservation r;

    if (f == NULL || tmp == NULL) return;

    while (fscanf(f, "%d %s %s %s %d", &r.id, r.nom, r.date, r.creneau, &r.quantite) != EOF) {
        if (!(r.id == id && strcmp(r.date, date) == 0 && strcmp(r.creneau, creneau) == 0)) {
            fprintf(tmp, "%d %s %s %s %d\n", r.id, r.nom, r.date, r.creneau, r.quantite);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(FICHIER_RES);
    rename("data/tmp_res.txt", FICHIER_RES);
}
