#ifndef ADMIN_H
#define ADMIN_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char nom[50];
    char entraineur[50];
    char date[20];
    char heure[10];
    int duree; // 1=30min, 2=1h, 3=90min
    char centre[50];
    char niveau[50]; // "débutant", "intermédiaire", "avancé" ou combinaison
    int capacite_max;
    float tarif;
    int inscrits;
} Cours;

// Fonctions pour cours
void ajouter_cours(Cours c);
int modifier_cours(Cours c);
int supprimer_cours(char id[]);
Cours* rechercher_cours(char id[]);
int verifier_disponibilite(char id[]);
int inscription_cours(char id_cours[], char id_membre[]);
int get_nombre_inscrits(char id_cours[]);
int get_capacite_max(char id_cours[]);
int get_cours_disponibles_par_centre(char centre[]);
int get_places_disponibles_par_entraineur(char entraineur[]);

// Fonctions pour statistiques
int get_total_cours();
int get_cours_disponibles();
int get_cours_complets();
int get_total_inscrits();
float get_taux_occupation();

#endif
