#ifndef CENTRE_H
#define CENTRE_H
#include <gtk/gtk.h>

enum {
    COL_ID,
    COL_NOM,
    COL_ADRESSE,
    COL_VILLE,
    COL_TELEPHONE,
    COL_EMAIL,
    COL_CAPACITE,
    COL_WEEKEND,
    COL_PARKING,
    COL_TYPE,
    NUM_COLS
};

typedef struct {
    int id;
    char nom[50];
    char adresse[100];
    char ville[30];
    char telephone[20];
    char email[50];
    int capacite;
    int ouvert_weekend;      // 0 = non, 1 = oui
    int parking_disponible;  // 0 = non, 1 = oui
    int type;                // 0 = privé, 1 = public
} Centre;

// Fonctions CRUD
int ajouter_centre(Centre c);
void modifier_centre(Centre c);
void supprimer_centre(int id);
int chercher_centre(int id, Centre *c);

// Fonctions d'affichage
void afficher_centre(GtkWidget *liste);
void vider_centre(GtkWidget *liste);

// Fonctions de validation
int valider_telephone(char *tel);
int valider_email(char *email);

// Fonctions statistiques
int calculer_total_centres(char *ville, int type, int capaciteMin, int capaciteMax, 
                          int parking, int weekend);
float calculer_moyenne_capacite(char *ville, int type, int capaciteMin, int capaciteMax, 
                               int parking, int weekend);
float calculer_pourcentage_parking(char *ville, int type, int capaciteMin, int capaciteMax, 
                                  int parking, int weekend);
float calculer_pourcentage_weekend(char *ville, int type, int capaciteMin, int capaciteMax, 
                                  int parking, int weekend);
void calculer_repartition_type(char *ville, int capaciteMin, int capaciteMax, 
                              int parking, int weekend, int *nb_prive, int *nb_public);

// Fonction pour afficher les centres par ville
void afficher_centres_par_ville(const char *ville, GtkWidget *treeview);

#endif
