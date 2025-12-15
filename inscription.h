#ifndef INSCRIPTION_H
#define INSCRIPTION_H

typedef struct {
    int idCentre;
    char nomEntraineur[50];
    char emailEntraineur[50];
} Inscription;

int ajouter_inscription(Inscription i);
void afficher_centres_par_ville(const char *ville, GtkWidget *treeview);

#endif
