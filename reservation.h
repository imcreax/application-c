#ifndef RESERVATION_H
#define RESERVATION_H

#include <gtk/gtk.h>
#include "equipment.h"

typedef struct {
    char id[50];
    char nom[50];
    int jour, mois, annee;
    char periode[20];
    int quantite;
} Reservation;

void afficher_disponibilite_date(GtkTreeView *treeview);
int reserver_equipement(Reservation r);

#endif
