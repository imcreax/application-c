#include <stdio.h>
#include <string.h>
#include "equipement.h"

#define FICHIER "data/affichage_equipements.txt"

void ajouter_equipement(Equipement e) {
    FILE *f = fopen(FICHIER, "a");
    if (f != NULL) {
        fprintf(f, "%d %s %d %s\n", e.id, e.nom, e.quantite, e.etat);
       fflush(f);                                                                                                                      fclose(f);
    }
}

int rechercher_equipement(int id, Equipement *e) {
    FILE *f = fopen(FICHIER, "r");
    if (f == NULL) return 0;
    while (fscanf(f, "%d %s %d %s", &e->id, e->nom, &e->quantite, e->etat) != EOF) {
        if (e->id == id) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void modifier_equipement(int id, Equipement nouv) {
    FILE *f = fopen(FICHIER, "r");
    FILE *tmp = fopen("data/tmp.txt", "w");
    Equipement e;

    if (f == NULL || tmp == NULL) return;

    while (fscanf(f, "%d %s %d %s", &e.id, e.nom, &e.quantite, e.etat) != EOF) {
        if (e.id == id) {
            fprintf(tmp, "%d %s %d %s\n", nouv.id, nouv.nom, nouv.quantite, nouv.etat);
        } else {
            fprintf(tmp, "%d %s %d %s\n", e.id, e.nom, e.quantite, e.etat);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(FICHIER);
    rename("data/tmp.txt", FICHIER);
}

void supprimer_equipement(int id) {
    FILE *f = fopen(FICHIER, "r");
    FILE *tmp = fopen("data/tmp.txt", "w");
    Equipement e;

    if (f == NULL || tmp == NULL) return;

    while (fscanf(f, "%d %s %d %s", &e.id, e.nom, &e.quantite, e.etat) != EOF) {
        if (e.id != id) {
            fprintf(tmp, "%d %s %d %s\n", e.id, e.nom, e.quantite, e.etat);
        }
    }
    fclose(f);
    fclose(tmp);
    remove(FICHIER);
    rename("data/tmp.txt", FICHIER);
}

int calculer_total_equipements() {
    FILE *f = fopen(FICHIER, "r");
    Equipement e;
    int total = 0;
    if (f == NULL) return 0;
    while (fscanf(f, "%d %s %d %s", &e.id, e.nom, &e.quantite, e.etat) != EOF) {
        total += e.quantite;
    }
    fclose(f);
    return total;
}                                                                                                                                              int compter_equipements_disponibles() {
    FILE *f = fopen(FICHIER, "r");
    Equipement e;
    int dispo = 0;
    if (f == NULL) return 0;
    while (fscanf(f, "%d %s %d %s", &e.id, e.nom, &e.quantite, e.etat) == 4) { 
        if (strcmp(e.etat, "disponible") == 0)
            dispo += e.quantite;
    }
    fclose(f);
    return dispo;
}                                                                                                                                            void afficher_equipements() {
    FILE *out = fopen("data/affichage_equipements.txt", "w");
    FILE *f = fopen(FICHIER, "r");
    Equipement e;

    if (out == NULL) return;
    if (f == NULL) {
        fprintf(out, "Aucun équipement.\n");
        fclose(out);
        return;
    }

    while (fscanf(f, "%d %s %d %s", &e.id, e.nom, &e.quantite, e.etat) == 4) {
        fprintf(out, "%d %s %d %s\n", e.id, e.nom, e.quantite, e.etat);
    }
    fclose(f);
    fclose(out);
}
