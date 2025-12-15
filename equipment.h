#ifndef DONATION_MANAGEMENT
#define DONATION_MANAGEMENT
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
typedef struct {
    int jj;
    int mm;
    int aa;
} Date;  // <- Ajoutez le point-virgule ici
typedef struct {

char idag[50];
char nom_ag[50];
char Disponible[10];
char etat[50];
Date Quantite;
}agent;
int ajoutequipment(agent a);
int modiferequipment(agent a);
int supprimerequipment(char idag[]);
agent* chercherequipment(char idag[]);
void afficherequipment(GtkTreeView *liste);


#endif 

