#ifndef INSCRIPTION_H
#define INSCRIPTION_H

typedef struct {
    int idCentre;
    char nomEntraineur[50];
    char email[50];
} Inscription;

void inscrireEntraineur(Inscription i);
void afficherCentresParVille(char* ville);

#endif
