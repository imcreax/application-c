#include <stdio.h>
#include <string.h>
#include "centre.h"
#include "inscription.h"

void inscrireEntraineur(Inscription i) {
    FILE *f = fopen("inscriptions.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s\n", i.idCentre, i.nomEntraineur, i.email);
        fclose(f);
    }
}

void afficherCentresParVille(char* ville) {
    FILE *f = fopen("centres.txt", "r");
    FILE *out = fopen("centres_par_ville.txt", "w");
    Centre c;
    char ligne[300];

    if (f == NULL || out == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        if (strcmp(c.ville, ville) == 0) {
            fprintf(out, "%d;%s;%s;%s;%s\n", c.id, c.nom, c.adresse, c.telephone, c.email);
        }
    }

    fclose(f);
    fclose(out);
}
