#ifndef MEMBRE_H
#define MEMBRE_H
#include <gtk/gtk.h>

typedef struct {
    char id[20];
    char nom[50];
    char prenom[50];
    int  age;
    char telephone[20];
    char email[100];
    char sexe[10];
    char type_abonnement[20];
} Membre;

void ajouter_membre(Membre *m);
void supprimer_membre(char *id);
Membre* rechercher_membre(char *id);
void modifier_membre(char *id, Membre *nouveau);
void charger_membres_depuis_fichier(void);
void sauvegarder_membres_dans_fichier(void);
void afficher_membres_dans_treeview(GtkTreeView *treeview);
void filtrer_membres_par_sexe(GtkTreeView *treeview, char *sexe);
void trier_membres_par_age(GtkTreeView *treeview, int ordre_croissant);
void exporter_membres_csv(const char *filename, GtkTreeView *treeview);

char* generer_statistiques_membres(void);

#endif
