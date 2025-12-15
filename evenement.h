#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <gtk/gtk.h>

typedef struct {
    char id[30];
    char nom[50];
    int jour, mois, annee;
    char heure[30];
    int buffet_disponible; // 0 = non, 1 = oui
    char organisateur[100];
    char site_web[100];
} evenement;

int ajouter_evenement(evenement e);
void afficher_evenement(GtkWidget *liste);
void supprimer_evenement(char *id);
void modifier_evenement(char *old_id, evenement e); 
void vider_evenement(GtkWidget *lists);
int chercher_evenement(char *id, evenement *e);
float calculer_pourcentage_soir(void);
float calculer_pourcentage_jour(void);

#endif
