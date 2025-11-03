#include <stdio.h>
<<<<<<< HEAD
#include "point.h"
#include "equipement.h"
#include "reservation.h"

void menu_administrateur();
void menu_entraineur();

int main() {
    int choix;
    do {
        printf("\n========== SALLE DE SPORT ==========\n");
        printf("1. Administrateur\n");
        printf("2. Entraîneur\n");
        printf("0. Quitter\n");
        printf("===================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: menu_administrateur(); break;
            case 2: menu_entraineur(); break;
            case 0: printf("Au revoir !\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choix != 0);
    return 0;
}                                                                                                                                            void menu_administrateur() {
    int choix, id;
    Equipement e, nouv;
    do {
        printf("\n===== MENU ADMIN =====\n");
        printf("1. Ajouter\n2. Modifier\n3. Supprimer\n4. Rechercher\n5. Statistiques\n0. Retour\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("ID : "); scanf("%d", &e.id);
                printf("Nom : "); scanf("%s", e.nom);
                printf("Quantité : "); scanf("%d", &e.quantite);
                printf("État : "); scanf("%s", e.etat);
                ajouter_equipement(e);
                break;

            case 2:
                printf("ID à modifier : "); scanf("%d", &id);
                printf("Nouveau ID : "); scanf("%d", &nouv.id);
                printf("Nom : "); scanf("%s", nouv.nom);
                printf("Quantité : "); scanf("%d", &nouv.quantite);
                printf("État : "); scanf("%s", nouv.etat);
                modifier_equipement(id, nouv);
                break;

            case 3:
                printf("ID à supprimer : "); scanf("%d", &id);
                supprimer_equipement(id);
                break;

            case 4:
                printf("ID à rechercher : "); scanf("%d", &id);
                if (rechercher_equipement(id, &e)) {
                    FILE *out = fopen("data/resultat_recherche.txt", "w");
                    if (out) {
                        fprintf(out, "Trouvé : %d %s %d %s\n", e.id, e.nom, e.quantite, e.etat);
                        fclose(out);
                    }
                } else {
                    FILE *out = fopen("data/resultat_recherche.txt", "w");
                    if (out) {
                        fprintf(out, "Non trouvé.\n");
                        fclose(out);
=======
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
>>>>>>> 905f79b4b307ebb2e2c4cd1b0d67d75839b74f9c
                    }
                }
                break;

<<<<<<< HEAD
           

            case 5: {
    FILE *stats = fopen("data/statistiques.txt", "w");
    if (stats) {
        int total = calculer_total_equipements();
        int dispo = compter_equipements_disponibles();
        int en_panne = total - dispo;
        fprintf(stats, "===== STATISTIQUES =====\n");
        fprintf(stats, "Total des équipements : %d\n", total);
        fprintf(stats, "Équipements disponibles : %d\n", dispo);
        fprintf(stats, "Équipements en panne : %d\n", en_panne);
        fclose(stats);
    }
    break;
}
        }
    } while (choix != 0);                                                                                            
 }                                                                                                                                          void menu_entraineur() {
    int choix;
    Reservation r;
    int dispo;
    char date_supp[20], creneau_supp[10];
    int id_supp;

    do {
        printf("\n===== MENU ENTRAINEUR =====\n");
        printf("1. Réserver\n2. Supprimer réservation\n0. Retour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("ID équipement : "); scanf("%d", &r.id);
                printf("Nom : "); scanf("%s", r.nom);
                printf("Date (jj/mm/aaaa) : "); scanf("%s", r.date);
                printf("Créneau (matin/midi/soir) : "); scanf("%s", r.creneau);
                printf("Quantité : "); scanf("%d", &r.quantite);
                dispo = verifier_disponibilite(r.id, r.date, r.creneau, r.quantite);
                if (dispo) {
                    ajouter_reservation(r);
                } else {
                    printf("Non disponible.\n");
                }
                break;
            case 2:
                printf("ID à supprimer : "); scanf("%d", &id_supp);
                printf("Date : "); scanf("%s", date_supp);
                printf("Créneau : "); scanf("%s", creneau_supp);
                supprimer_reservation(id_supp, date_supp, creneau_supp);
                break;
        }
    } while (choix != 0);
} 
=======
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
>>>>>>> 905f79b4b307ebb2e2c4cd1b0d67d75839b74f9c
