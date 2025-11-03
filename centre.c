#include <stdio.h>
#include <string.h>
#include "centre.h"

void ajouterCentre(Centre c) {
    FILE *f = fopen("centres.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
            c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
        fclose(f);
    }
}

void modifierCentre(Centre c) {
    FILE *f = fopen("centres.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    Centre temp;
    char ligne[300];

    if (f == NULL || tmp == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &temp.id, temp.nom, temp.adresse, temp.ville, temp.telephone, temp.email,
            &temp.capacite, &temp.ouvert_weekend, &temp.parking_disponible, &temp.type);

        if (temp.id == c.id) {
            fprintf(tmp, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
        } else {
            fputs(ligne, tmp);
        }
    }

    fclose(f);
    fclose(tmp);
    remove("centres.txt");
    rename("temp.txt", "centres.txt");
}

void supprimerCentre(int id) {
    FILE *f = fopen("centres.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    Centre c;
    char ligne[300];

    if (f == NULL || tmp == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        if (c.id != id) {
            fputs(ligne, tmp);
        }
    }

    fclose(f);
    fclose(tmp);
    remove("centres.txt");
    rename("temp.txt", "centres.txt");
}

Centre rechercherCentre(int id) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    char ligne[300];

    if (f == NULL) {
        c.id = -1;
        return c;
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        if (c.id == id) {
            fclose(f);
            return c;
        }
    }

    fclose(f);
    c.id = -1;
    return c;
}

void statistiquesFiltres(char* ville, int type, int capaciteMin, int capaciteMax, int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    FILE *out = fopen("stats.txt", "w");
    FILE *graph = fopen("graph.txt", "w");
    Centre c;
    char ligne[300];
    int total = 0, prive = 0, public = 0;
    int capaciteTotale = 0, avecParking = 0, ouvertWeekend = 0;

    if (f == NULL || out == NULL || graph == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;

        if (match) {
            fprintf(out, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);

            total++;
            capaciteTotale += c.capacite;
            if (c.type == 0) prive++;
            else public++;
            if (c.parking_disponible == 1) avecParking++;
            if (c.ouvert_weekend == 1) ouvertWeekend++;
        }
    }

    float moyenneCapacite = total > 0 ? (float)capaciteTotale / total : 0;
    float pourcentageParking = total > 0 ? (float)avecParking * 100 / total : 0;
    float pourcentageWeekend = total > 0 ? (float)ouvertWeekend * 100 / total : 0;

    fprintf(graph, "Total:%d\nPrivé:%d\nPublic:%d\n", total, prive, public);
    fprintf(graph, "Moyenne capacité:%.2f\n", moyenneCapacite);
    fprintf(graph, "%% avec parking:%.2f\n", pourcentageParking);
    fprintf(graph, "%% ouverts le weekend:%.2f\n", pourcentageWeekend);

    fclose(f);
    fclose(out);
    fclose(graph);

    FILE *villeOut = fopen("villes_filtrees.txt", "w");
    if (villeOut != NULL) {
        FILE *in = fopen("stats.txt", "r");
        if (in != NULL) {
            typedef struct { char nom[30]; int count; } VilleStat;
            VilleStat villes[100];
            int n = 0;

            while (fgets(ligne, sizeof(ligne), in)) {
                sscanf(ligne, "%*d;%*[^;];%*[^;];%[^;];", c.ville);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    if (strcmp(villes[i].nom, c.ville) == 0) {
                        villes[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(villes[n].nom, c.ville);
                    villes[n].count = 1;
                    n++;
                }
            }

            for (int i = 0; i < n; i++) {
                fprintf(villeOut, "%s;%d\n", villes[i].nom, villes[i].count);
            }

            fclose(in);
        }
        fclose(villeOut);
    }
}
