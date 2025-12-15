#ifndef CENTRE_H
#define CENTRE_H
#include <gtk/gtk.h>

enum {
    COL_NOM,
    COL_ADRESSE,
    COL_VILLE,
    COL_TELEPHONE,
    COL_EMAIL,
    COL_CAPACITE,
    COL_TYPE,
    NUM_COLS
};


typedef struct {
    int id;
    char nom[50];
    char adresse[50];
    char ville[30];
    char telephone[20];
    char email[50];
    int capacite;
    int ouvert_weekend;
    int parking_disponible;
    int type; // 0 = privé, 1 = public
} Centre;

void ajouterCentre(Centre c);
void modifierCentre(Centre c);
void supprimerCentre(int id);
Centre rechercherCentre(int id);
void afficher_centre_dans_treeview(GtkWidget *treeview, Centre c);
void statistiquesFiltres(char* ville, int type, int capaciteMin, int capaciteMax, int parking, int weekend);
void exporter_resultats_vers_fichier(GtkWidget *treeview);
void partager_resultats(GtkWidget *treeview);
// Fonctions TreeView
void vider_treeview(GtkWidget *treeview);
void afficher_tous_les_centres(GtkWidget *treeview);

int valider_telephone(char *tel);
int valider_email(char *email);



#endif
