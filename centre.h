#ifndef CENTRE_H
#define CENTRE_H

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
void statistiquesFiltres(char* ville, int type, int capaciteMin, int capaciteMax, int parking, int weekend);

#endif
