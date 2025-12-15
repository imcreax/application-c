#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "centre.h"

void ajouterCentre(Centre c) {
    FILE *f = fopen("centres.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
            c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
        fclose(f);
    }
}

void modifierCentre(Centre c) {
    FILE *f = fopen("centres.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    Centre temp;
    char ligne[300];

    if (f == NULL || tmp == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &temp.id, temp.nom, temp.adresse, temp.ville, temp.telephone, temp.email,
            &temp.capacite, &temp.ouvert_weekend, &temp.parking_disponible, &temp.type);

        if (temp.id == c.id) {
            fprintf(tmp, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
        } else {
            fputs(ligne, tmp);
        }
    }

    fclose(f);
    fclose(tmp);
    remove("centres.txt");
    rename("temp.txt", "centres.txt");
}

void supprimerCentre(int id) {
    FILE *f = fopen("centres.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    Centre c;
    char ligne[300];

    if (f == NULL || tmp == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        if (c.id != id) {
            fputs(ligne, tmp);
        }
    }

    fclose(f);
    fclose(tmp);
    remove("centres.txt");
    rename("temp.txt", "centres.txt");
}

Centre rechercherCentre(int id) {
    Centre c;
    c.id = -1; // par défaut non trouvé

    FILE *f = fopen("centres.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %s %s %s %d %d %d %d",
                      &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                      &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
            if (c.id == id) break;
        }
        fclose(f);
    }

    return c;
}

void afficher_centre_dans_treeview(GtkWidget *treeview, Centre c)
{
    GtkListStore *store;
    GtkTreeIter iter;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));

    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                       0, c.id,
                       1, c.nom,
                       2, c.adresse,
                       3, c.ville,
                       4, c.telephone,
                       5, c.email,
                       6, c.capacite,
                       7, c.ouvert_weekend,
                       8, c.parking_disponible,
                       9, (c.type == 0 ? "Privé" : "Public"),
                       -1);
}


void statistiquesFiltres(char* ville, int type, int capaciteMin, int capaciteMax, int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    FILE *out = fopen("stats.txt", "w");
    FILE *graph = fopen("graph.txt", "w");
    Centre c;
    char ligne[300];
    int total = 0, prive = 0, public = 0;
    int capaciteTotale = 0, avecParking = 0, ouvertWeekend = 0;

    if (f == NULL || out == NULL || graph == NULL) return;

    while (fgets(ligne, sizeof(ligne), f)) {
        sscanf(ligne, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d",
            &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
            &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);

        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;

        if (match) {
            fprintf(out, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);

            total++;
            capaciteTotale += c.capacite;
            if (c.type == 0) prive++;
            else public++;
            if (c.parking_disponible == 1) avecParking++;
            if (c.ouvert_weekend == 1) ouvertWeekend++;
        }
    }

    float moyenneCapacite = total > 0 ? (float)capaciteTotale / total : 0;
    float pourcentageParking = total > 0 ? (float)avecParking * 100 / total : 0;
    float pourcentageWeekend = total > 0 ? (float)ouvertWeekend * 100 / total : 0;

    fprintf(graph, "Total:%d\nPrivé:%d\nPublic:%d\n", total, prive, public);
    fprintf(graph, "Moyenne capacité:%.2f\n", moyenneCapacite);
    fprintf(graph, "%% avec parking:%.2f\n", pourcentageParking);
    fprintf(graph, "%% ouverts le weekend:%.2f\n", pourcentageWeekend);

    fclose(f);
    fclose(out);
    fclose(graph);

    FILE *villeOut = fopen("villes_filtrees.txt", "w");
    if (villeOut != NULL) {
        FILE *in = fopen("stats.txt", "r");
        if (in != NULL) {
            typedef struct { char nom[30]; int count; } VilleStat;
            VilleStat villes[100];
            int n = 0;

            while (fgets(ligne, sizeof(ligne), in)) {
                sscanf(ligne, "%*d;%*[^;];%*[^;];%[^;];", c.ville);
                int found = 0;
                for (int i = 0; i < n; i++) {
                    if (strcmp(villes[i].nom, c.ville) == 0) {
                        villes[i].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    strcpy(villes[n].nom, c.ville);
                    villes[n].count = 1;
                    n++;
                }
            }

            for (int i = 0; i < n; i++) {
                fprintf(villeOut, "%s;%d\n", villes[i].nom, villes[i].count);
            }

            fclose(in);
        }
        fclose(villeOut);
    }
}




void exporter_resultats_vers_fichier(GtkWidget *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkTreeIter iter;
    FILE *f = fopen("resultats.txt", "w");

    if (f == NULL) {
        g_print("Erreur ouverture fichier export.\n");
        return;
    }

    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        char nom[100], adresse[200], ville[50], telephone[20], email[100], capacite[10], type[10];

        gtk_tree_model_get(model, &iter,
                           0, &nom,
                           1, &adresse,
                           2, &ville,
                           3, &telephone,
                           4, &email,
                           5, &capacite,
                           6, &type,
                           -1);

        fprintf(f, "%s | %s | %s | %s | %s | %s | %s\n",
                nom, adresse, ville, telephone, email, capacite, type);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    fclose(f);
    g_print("Résultats exportés dans resultats.txt\n");
}


void partager_resultats(GtkWidget *treeview) {
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkTreeIter iter;
    FILE *f = fopen("partage.txt", "w");

    if (f == NULL) {
        g_print("Erreur ouverture fichier partage.\n");
        return;
    }

    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        char nom[100], adresse[200], ville[50], telephone[20], email[100], capacite[10], type[10];

        gtk_tree_model_get(model, &iter,
                           0, &nom,
                           1, &adresse,
                           2, &ville,
                           3, &telephone,
                           4, &email,
                           5, &capacite,
                           6, &type,
                           -1);

        fprintf(f, "Centre: %s (%s, %s) - Tel: %s, Email: %s, Capacité: %s, Type: %s\n",
                nom, adresse, ville, telephone, email, capacite, type);

        valid = gtk_tree_model_iter_next(model, &iter);
    }

    fclose(f);
    g_print("Résultats partagés dans partage.txt\n");
}

// Vider la TreeView
void vider_treeview(GtkWidget *liste)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkListStore *store;

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", COL_NOM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", COL_ADRESSE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", COL_VILLE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", COL_TELEPHONE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", COL_EMAIL, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", COL_CAPACITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", COL_TYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(NUM_COLS,
                               G_TYPE_STRING,  // Nom
                               G_TYPE_STRING,  // Adresse
                               G_TYPE_STRING,  // Ville
                               G_TYPE_STRING,  // Téléphone
                               G_TYPE_STRING,  // Email
                               G_TYPE_INT,     // Capacité
                               G_TYPE_STRING); // Type (privé/public)

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}


// Afficher les centres
void afficher_tous_les_centres(GtkWidget *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    int id, capacite, ouvert_weekend, parking_disponible, type;
    char nom[50], adresse[100], ville[50], telephone[20], email[50];
    FILE *f;

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (store == NULL) {
        // Création des colonnes
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ouvert weekend", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    // Définition du modèle avec 10 colonnes
    store = gtk_list_store_new(10,
                               G_TYPE_INT,    // ID
                               G_TYPE_STRING, // Nom
                               G_TYPE_STRING, // Adresse
                               G_TYPE_STRING, // Ville
                               G_TYPE_STRING, // Téléphone
                               G_TYPE_STRING, // Email
                               G_TYPE_INT,    // Capacité
                               G_TYPE_INT,    // Ouvert weekend
                               G_TYPE_INT,    // Parking
                               G_TYPE_STRING  // Type (Privé/Public)
    );

    f = fopen("centres.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d %s %s %s %s %s %d %d %d %d",
                      &id, nom, adresse, ville, telephone, email,
                      &capacite, &ouvert_weekend, &parking_disponible, &type) != EOF) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, id,
                               1, nom,
                               2, adresse,
                               3, ville,
                               4, telephone,
                               5, email,
                               6, capacite,
                               7, ouvert_weekend,
                               8, parking_disponible,
                               9, (type == 0 ? "Privé" : "Public"),
                               -1);
        }
        fclose(f);
    }

    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}



int valider_telephone(char *tel) {
    if (strlen(tel) != 8) return 0;
    for (int i = 0; i < 8; i++) {
        if (!isdigit(tel[i])) return 0;
    }
    return 1;
}

int valider_email(char *email) {
    return (strchr(email, '@') != NULL && strchr(email, '.') != NULL);
}


