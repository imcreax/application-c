#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

typedef struct {
    int id;
    char nom[50];
    int quantite;
    char etat[20];
} Equipement;

void ajouter_equipement(Equipement e);
void afficher_equipements();
int rechercher_equipement(int id, Equipement *e);
void modifier_equipement(int id, Equipement nouv); 
void supprimer_equipement(int id);
int calculer_total_equipements();
int compter_equipements_disponibles();

#endif
