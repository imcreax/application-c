#ifndef ENTRAINEUR_H_INCLUDED
#define ENTRAINEUR_H_INCLUDED

#include <gtk/gtk.h>

typedef struct {
    char nom[30];
    char prenom[30];
    char id[30];
    char specialite[30];
    char telephone[30];
    int experience;
    int jour, mois, annee;
    char sexe[10];
    char email[50];
    char adresse[100];
} entraineur;

int ajouter_entraineur(entraineur e);
void afficher_entraineur(GtkWidget *liste);
void supprimer_entraineur(char *id);
void modifier_entraineur(char *old_id, entraineur e);
void vider(GtkWidget *lists);
int chercher_entraineur(char *id, entraineur *e);

#endif
