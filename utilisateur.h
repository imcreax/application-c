#ifndef UTILISATEUR_H
#define UTILISATEUR_H

typedef struct {
    char identifiant[50];
    char mot_de_passe[50];
    char type[20];  // "admin" ou "entraineur"
} Utilisateur;

// Fonction d'authentification
int authentifier_utilisateur(const char *identifiant, const char *mot_de_passe, char *type_out);

#endif
