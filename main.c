#include <stdio.h>
#include <string.h>
#include "centre.h"
#include "inscription.h"

int main() {
    Centre c;
    Inscription i;
    int choix, idCentre;
    char ville[30];

    do {
        printf("\n--- Menu Gestion des Centres ---\n");
        printf("1. Ajouter un centre\n");
        printf("2. Modifier un centre\n");
        printf("3. Supprimer un centre\n");
        printf("4. Rechercher un centre\n");
        printf("5. Statistiques filtrées\n");
        printf("6. Inscription entraîneur (avec affichage des centres)\n");
        printf("7. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix); getchar();

        switch (choix) {
            case 1:
                printf("ID : "); scanf("%d", &c.id); getchar();
                printf("Nom : "); fgets(c.nom, 50, stdin); strtok(c.nom, "\n");
                printf("Adresse : "); fgets(c.adresse, 50, stdin); strtok(c.adresse, "\n");
                printf("Ville : "); fgets(c.ville, 30, stdin); strtok(c.ville, "\n");
                printf("Téléphone : "); fgets(c.telephone, 20, stdin); strtok(c.telephone, "\n");
                printf("Email : "); fgets(c.email, 50, stdin); strtok(c.email, "\n");
                printf("Capacité : "); scanf("%d", &c.capacite);
                printf("Ouvert le weekend (1/0) : "); scanf("%d", &c.ouvert_weekend);
                printf("Parking disponible (1/0) : "); scanf("%d", &c.parking_disponible);
                printf("Type (0=Privé, 1=Public) : "); scanf("%d", &c.type);
                ajouterCentre(c);
                break;

            case 2:
                printf("ID du centre à modifier : "); scanf("%d", &c.id); getchar();
                printf("Nom : "); fgets(c.nom, 50, stdin); strtok(c.nom, "\n");
                printf("Adresse : "); fgets(c.adresse, 50, stdin); strtok(c.adresse, "\n");
                printf("Ville : "); fgets(c.ville, 30, stdin); strtok(c.ville, "\n");
                printf("Téléphone : "); fgets(c.telephone, 20, stdin); strtok(c.telephone, "\n");
                printf("Email : "); fgets(c.email, 50, stdin); strtok(c.email, "\n");
                printf("Capacité : "); scanf("%d", &c.capacite);
                printf("Ouvert le weekend (1/0) : "); scanf("%d", &c.ouvert_weekend);
                printf("Parking disponible (1/0) : "); scanf("%d", &c.parking_disponible);
                printf("Type (0=Privé, 1=Public) : "); scanf("%d", &c.type);
                modifierCentre(c);
                break;

            case 3:
                printf("ID du centre à supprimer : "); scanf("%d", &idCentre);
                supprimerCentre(idCentre);
                break;

            case 4:
                printf("ID du centre à rechercher : "); scanf("%d", &idCentre);
                c = rechercherCentre(idCentre);
                if (c.id != -1) {
                    FILE *f = fopen("resultat_recherche.txt", "w");
                    if (f != NULL) {
                        fprintf(f, "Nom;%s\nAdresse;%s\nVille;%s\nTéléphone;%s\nEmail;%s\nCapacité;%d\nType;%s\n",
                            c.nom, c.adresse, c.ville, c.telephone, c.email, c.capacite,
                            c.type == 0 ? "Privé" : "Public");
                        fclose(f);
                    }
                }
                break;

            case 5:
                printf("Ville : "); fgets(ville, 30, stdin); strtok(ville, "\n");
                statistiquesFiltres(ville, -1, 0, 1000, -1, -1);
                break;

            case 6:
                printf("Ville : "); fgets(ville, 30, stdin); strtok(ville, "\n");
                afficherCentresParVille(ville);
                printf("ID du centre : "); scanf("%d", &i.idCentre); getchar();
                printf("Nom de l'entraîneur : "); fgets(i.nomEntraineur, 50, stdin); strtok(i.nomEntraineur, "\n");
                printf("Email : "); fgets(i.email, 50, stdin); strtok(i.email, "\n");
                inscrireEntraineur(i);
                break;

            default:
                break;
        }
    } while (choix != 7);

    return 0;
}
