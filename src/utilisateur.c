#include <stdio.h>
#include <string.h>
#include "utilisateur.h"

int authentifier_utilisateur(const char *identifiant, const char *mot_de_passe, char *type_out) {
    FILE *f = fopen("utilisateurs.txt", "r");
    Utilisateur u;
    char ligne[256];
    
    if (f == NULL) {
        // Si le fichier n'existe pas, créer un utilisateur admin par défaut
        f = fopen("utilisateurs.txt", "w");
        if (f != NULL) {
            fprintf(f, "admin;admin123;admin\n");
            fprintf(f, "entraineur;entraineur123;entraineur\n");
            fclose(f);
        }
        f = fopen("utilisateurs.txt", "r");
    }
    
    if (f == NULL) return 0;
    
    while (fgets(ligne, sizeof(ligne), f) != NULL) {
        int scan_result = sscanf(ligne, "%49[^;];%49[^;];%19[^\n]",
                                 u.identifiant, u.mot_de_passe, u.type);
        
        if (scan_result == 3) {
            if (strcmp(u.identifiant, identifiant) == 0 && 
                strcmp(u.mot_de_passe, mot_de_passe) == 0) {
                strcpy(type_out, u.type);
                fclose(f);
                return 1; // Authentification réussie
            }
        }
    }
    
    fclose(f);
    return 0; // Échec de l'authentification
}
