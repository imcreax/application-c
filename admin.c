#include "admin.h"

void ajouter_cours(Cours c) {
    FILE *f = fopen("cours.txt", "a");
    if (f) {
        fprintf(f, "%s|%s|%s|%s|%s|%d|%s|%s|%d|%.2f|%d\n",
                c.id, c.nom, c.entraineur, c.date, c.heure,
                c.duree, c.centre, c.niveau, c.capacite_max,
                c.tarif, c.inscrits);
        fclose(f);
    }
}

int modifier_cours(Cours c) {
    int trouve = 0;
    Cours temp;
    FILE *f = fopen("cours.txt", "r");
    FILE *ft = fopen("temp.txt", "w");
   
    if (!f || !ft) return 0;
   
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  temp.id, temp.nom, temp.entraineur, temp.date,
                  temp.heure, &temp.duree, temp.centre, temp.niveau,
                  &temp.capacite_max, &temp.tarif, &temp.inscrits) != EOF) {
        if (strcmp(temp.id, c.id) == 0) {
            fprintf(ft, "%s|%s|%s|%s|%s|%d|%s|%s|%d|%.2f|%d\n",
                    c.id, c.nom, c.entraineur, c.date, c.heure,
                    c.duree, c.centre, c.niveau, c.capacite_max,
                    c.tarif, c.inscrits);
            trouve = 1;
        } else {
            fprintf(ft, "%s|%s|%s|%s|%s|%d|%s|%s|%d|%.2f|%d\n",
                    temp.id, temp.nom, temp.entraineur, temp.date,
                    temp.heure, temp.duree, temp.centre, temp.niveau,
                    temp.capacite_max, temp.tarif, temp.inscrits);
        }
    }
   
    fclose(f);
    fclose(ft);
    remove("cours.txt");
    rename("temp.txt", "cours.txt");
    return trouve;
}

int supprimer_cours(char id[]) {
    int trouve = 0;
    Cours temp;
    FILE *f = fopen("cours.txt", "r");
    FILE *ft = fopen("temp.txt", "w");
   
    if (!f || !ft) return 0;
   
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  temp.id, temp.nom, temp.entraineur, temp.date,
                  temp.heure, &temp.duree, temp.centre, temp.niveau,
                  &temp.capacite_max, &temp.tarif, &temp.inscrits) != EOF) {
        if (strcmp(temp.id, id) == 0) {
            trouve = 1;
        } else {
            fprintf(ft, "%s|%s|%s|%s|%s|%d|%s|%s|%d|%.2f|%d\n",
                    temp.id, temp.nom, temp.entraineur, temp.date,
                    temp.heure, temp.duree, temp.centre, temp.niveau,
                    temp.capacite_max, temp.tarif, temp.inscrits);
        }
    }
   
    fclose(f);
    fclose(ft);
    remove("cours.txt");
    rename("temp.txt", "cours.txt");
    return trouve;
}

Cours* rechercher_cours(char id[]) {
    Cours *c = malloc(sizeof(Cours));
    FILE *f = fopen("cours.txt", "r");
   
    if (!f) {
        free(c);
        return NULL;
    }
   
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c->id, c->nom, c->entraineur, c->date,
                  c->heure, &c->duree, c->centre, c->niveau,
                  &c->capacite_max, &c->tarif, &c->inscrits) != EOF) {
        if (strcmp(c->id, id) == 0) {
            fclose(f);
            return c;
        }
    }
   
    fclose(f);
    free(c);
    return NULL;
}

int verifier_disponibilite(char id[]) {
    Cours *c = rechercher_cours(id);
    if (!c) return 0;
   
    int disponible = (c->inscrits < c->capacite_max);
    free(c);
    return disponible;
}

int inscription_cours(char id_cours[], char id_membre[]) {
    // Vérifier si le membre existe déjà dans membres.txt
    int membre_existe = 0;
    FILE *fm = fopen("membres.txt", "r");
    if (fm) {
        char id[20];
        while (fscanf(fm, "%s\n", id) != EOF) {
            if (strcmp(id, id_membre) == 0) {
                membre_existe = 1;
                break;
            }
        }
        fclose(fm);
    }
   
    // Si le membre n'existe pas, le créer
    if (!membre_existe) {
        fm = fopen("membres.txt", "a");
        if (fm) {
            fprintf(fm, "%s\n", id_membre);
            fclose(fm);
        }
    }
   
    Cours *c = rechercher_cours(id_cours);
    if (!c) return 0;
   
    if (c->inscrits >= c->capacite_max) {
        free(c);
        return 0; // Cours complet
    }
   
    // Vérifier si le membre est déjà inscrit à ce cours
    FILE *fi = fopen("inscriptions.txt", "r");
    if (fi) {
        char id_c[20], id_m[20];
        while (fscanf(fi, "%[^|]|%[^\n]\n", id_c, id_m) != EOF) {
            if (strcmp(id_c, id_cours) == 0 && strcmp(id_m, id_membre) == 0) {
                fclose(fi);
                free(c);
                return 0; // Déjà inscrit
            }
        }
        fclose(fi);
    }
   
    // Incrémenter le nombre d'inscrits
    c->inscrits++;
   
    // Sauvegarder les modifications
    modifier_cours(*c);
   
    // Ajouter l'inscription
    FILE *f = fopen("inscriptions.txt", "a");
    if (f) {
        fprintf(f, "%s|%s\n", id_cours, id_membre);
        fclose(f);
    }
   
    free(c);
    return 1;
}

int get_nombre_inscrits(char id_cours[]) {
    Cours *c = rechercher_cours(id_cours);
    if (!c) return -1;
   
    int inscrits = c->inscrits;
    free(c);
    return inscrits;
}

int get_capacite_max(char id_cours[]) {
    Cours *c = rechercher_cours(id_cours);
    if (!c) return -1;
   
    int capacite = c->capacite_max;
    free(c);
    return capacite;
}

int get_cours_disponibles_par_centre(char centre[]) {
    int count = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    Cours c;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date,
                  c.heure, &c.duree, c.centre, c.niveau,
                  &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
        if (strcmp(c.centre, centre) == 0 && c.inscrits < c.capacite_max) {
            count++;
        }
    }
   
    fclose(f);
    return count;
}

int get_places_disponibles_par_entraineur(char entraineur[]) {
    int places = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    Cours c;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date,
                  c.heure, &c.duree, c.centre, c.niveau,
                  &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
        if (strcmp(c.entraineur, entraineur) == 0) {
            places += (c.capacite_max - c.inscrits);
        }
    }
   
    fclose(f);
    return places;
}

int get_total_cours() {
    int count = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        count++;
    }
   
    fclose(f);
    return count;
}

int get_cours_disponibles() {
    int count = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    Cours c;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date,
                  c.heure, &c.duree, c.centre, c.niveau,
                  &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
        if (c.inscrits < c.capacite_max) {
            count++;
        }
    }
   
    fclose(f);
    return count;
}

int get_cours_complets() {
    int count = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    Cours c;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date,
                  c.heure, &c.duree, c.centre, c.niveau,
                  &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
        if (c.inscrits >= c.capacite_max) {
            count++;
        }
    }
   
    fclose(f);
    return count;
}

int get_total_inscrits() {
    int total = 0;
    FILE *f = fopen("cours.txt", "r");
    if (!f) return 0;
   
    Cours c;
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date,
                  c.heure, &c.duree, c.centre, c.niveau,
                  &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
        total += c.inscrits;
    }
   
    fclose(f);
    return total;
}

float get_taux_occupation() {
    int total_cours = get_total_cours();
    int total_inscrits = get_total_inscrits();
   
    if (total_cours == 0) return 0.0;
   
    // Calculer la capacité totale estimée (moyenne de 30 par cours)
    int capacite_totale = total_cours * 30;
   
    if (capacite_totale == 0) return 0.0;
   
    return (float)total_inscrits / capacite_totale * 100.0;
}
