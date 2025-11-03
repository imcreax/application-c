#include <stdio.h>
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
                    }
                }
                break;

           

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
