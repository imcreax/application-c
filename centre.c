#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "centre.h"

int ajouter_centre(Centre c) {
    FILE *f;
    Centre tmp;
    int id_existe = 0;
    
    // Vérifier si l'ID existe déjà 
    f = fopen("centres.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &tmp.id, tmp.nom, tmp.adresse, tmp.ville, 
                      tmp.telephone, tmp.email, &tmp.capacite, 
                      &tmp.ouvert_weekend, &tmp.parking_disponible, &tmp.type) != EOF) {
            
            if (tmp.id == c.id) {
                id_existe = 1;
                break;
            }
        }
        fclose(f);
    }
    
    if (id_existe) {
        return 0; // Échec
    }
    
    // Ajouter le centre
    f = fopen("centres.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
        fclose(f);
        return 1; // Succès
    }
    
    return 0;
}

void modifier_centre(Centre c) {
    FILE *f, *temp;
    Centre tmp;
    
    f = fopen("centres.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &tmp.id, tmp.nom, tmp.adresse, tmp.ville, 
                      tmp.telephone, tmp.email, &tmp.capacite, 
                      &tmp.ouvert_weekend, &tmp.parking_disponible, &tmp.type) != EOF) {
            
            if (tmp.id == c.id) {
                fprintf(temp, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                        c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                        c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
            } else {
                fprintf(temp, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                        tmp.id, tmp.nom, tmp.adresse, tmp.ville, 
                        tmp.telephone, tmp.email, tmp.capacite, 
                        tmp.ouvert_weekend, tmp.parking_disponible, tmp.type);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("centres.txt");
        rename("temp.txt", "centres.txt");
    }
}

void supprimer_centre(int id) {
    FILE *f, *temp;
    Centre c;
    
    f = fopen("centres.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &c.id, c.nom, c.adresse, c.ville, 
                      c.telephone, c.email, &c.capacite, 
                      &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
            
            if (c.id != id) {
                fprintf(temp, "%d;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",
                        c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                        c.capacite, c.ouvert_weekend, c.parking_disponible, c.type);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("centres.txt");
        rename("temp.txt", "centres.txt");
    }
}

int chercher_centre(int id, Centre *c) {
    FILE *f;
    Centre tmp;
    int trouve = 0;
    
    f = fopen("centres.txt", "r");
    
    if (f != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &tmp.id, tmp.nom, tmp.adresse, tmp.ville, 
                      tmp.telephone, tmp.email, &tmp.capacite, 
                      &tmp.ouvert_weekend, &tmp.parking_disponible, &tmp.type) != EOF) {
            
            if (tmp.id == id) {
                c->id = tmp.id;
                strcpy(c->nom, tmp.nom);
                strcpy(c->adresse, tmp.adresse);
                strcpy(c->ville, tmp.ville);
                strcpy(c->telephone, tmp.telephone);
                strcpy(c->email, tmp.email);
                c->capacite = tmp.capacite;
                c->ouvert_weekend = tmp.ouvert_weekend;
                c->parking_disponible = tmp.parking_disponible;
                c->type = tmp.type;
                
                trouve = 1;
                break;
            }
        }
        fclose(f);
    }
    
    return trouve;
}

void afficher_centre(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    
    FILE *f;
    Centre c;
    
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    
    if (old_model == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Weekend", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    
    store = gtk_list_store_new(10,
                              G_TYPE_INT,    // ID
                              G_TYPE_STRING, // Nom
                              G_TYPE_STRING, // Adresse
                              G_TYPE_STRING, // Ville
                              G_TYPE_STRING, // Téléphone
                              G_TYPE_STRING, // Email
                              G_TYPE_INT,    // Capacité
                              G_TYPE_STRING, // Weekend
                              G_TYPE_STRING, // Parking
                              G_TYPE_STRING  // Type
    );
    
    f = fopen("centres.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &c.id, c.nom, c.adresse, c.ville, 
                      c.telephone, c.email, &c.capacite, 
                      &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, c.id,
                              1, c.nom,
                              2, c.adresse,
                              3, c.ville,
                              4, c.telephone,
                              5, c.email,
                              6, c.capacite,
                              7, c.ouvert_weekend ? "Oui" : "Non",
                              8, c.parking_disponible ? "Oui" : "Non",
                              9, c.type == 0 ? "Privé" : "Public",
                              -1);
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

void vider_centre(GtkWidget *liste) {
    GtkListStore *store;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    
    if (model != NULL) {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
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

// Fonctions statistiques
int calculer_total_centres(char *ville, int type, int capaciteMin, int capaciteMax, 
                          int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int total = 0;
    
    if (f == NULL) return 0;
    
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                  &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                  &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
        
        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;
        
        if (match) total++;
    }
    
    fclose(f);
    return total;
}

float calculer_moyenne_capacite(char *ville, int type, int capaciteMin, int capaciteMax, 
                               int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int total = 0, somme = 0;
    
    if (f == NULL) return 0.0;
    
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                  &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                  &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
        
        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;
        
        if (match) {
            total++;
            somme += c.capacite;
        }
    }
    
    fclose(f);
    return total > 0 ? (float)somme / total : 0.0;
}

float calculer_pourcentage_parking(char *ville, int type, int capaciteMin, int capaciteMax, 
                                  int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int total = 0, avec_parking = 0;
    
    if (f == NULL) return 0.0;
    
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                  &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                  &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
        
        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;
        
        if (match) {
            total++;
            if (c.parking_disponible == 1) avec_parking++;
        }
    }
    
    fclose(f);
    return total > 0 ? (float)avec_parking * 100 / total : 0.0;
}

float calculer_pourcentage_weekend(char *ville, int type, int capaciteMin, int capaciteMax, 
                                  int parking, int weekend) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    int total = 0, ouvert_weekend = 0;
    
    if (f == NULL) return 0.0;
    
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                  &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                  &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
        
        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (type != -1 && c.type != type) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        
        if (match) {
            total++;
            if (c.ouvert_weekend == 1) ouvert_weekend++;
        }
    }
    
    fclose(f);
    return total > 0 ? (float)ouvert_weekend * 100 / total : 0.0;
}

void calculer_repartition_type(char *ville, int capaciteMin, int capaciteMax, 
                              int parking, int weekend, int *nb_prive, int *nb_public) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    
    *nb_prive = 0;
    *nb_public = 0;
    
    if (f == NULL) return;
    
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                  &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                  &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
        
        int match = 1;
        if (strlen(ville) > 0 && strcmp(c.ville, ville) != 0) match = 0;
        if (c.capacite < capaciteMin || c.capacite > capaciteMax) match = 0;
        if (parking != -1 && c.parking_disponible != parking) match = 0;
        if (weekend != -1 && c.ouvert_weekend != weekend) match = 0;
        
        if (match) {
            if (c.type == 0) (*nb_prive)++;
            else (*nb_public)++;
        }
    }
    
    fclose(f);
}

// Fonction pour afficher les centres par ville (pour l'inscription)
void afficher_centres_par_ville(const char *ville, GtkWidget *treeview) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    FILE *f;
    Centre c;
    
    // Vérifier si les colonnes existent déjà
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    
    if (old_model == NULL) {
        // Créer les colonnes si elles n'existent pas
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
        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
    
    // Créer un nouveau store
    store = gtk_list_store_new(5,
                              G_TYPE_INT,    // ID
                              G_TYPE_STRING, // Nom
                              G_TYPE_STRING, // Adresse
                              G_TYPE_STRING, // Ville
                              G_TYPE_INT     // Capacité
    );
    
    // Lire le fichier et filtrer par ville
    f = fopen("centres.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",
                      &c.id, c.nom, c.adresse, c.ville, 
                      c.telephone, c.email, &c.capacite, 
                      &c.ouvert_weekend, &c.parking_disponible, &c.type) != EOF) {
            
            // Filtrer par ville
            if (strcmp(c.ville, ville) == 0) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                  0, c.id,
                                  1, c.nom,
                                  2, c.adresse,
                                  3, c.ville,
                                  4, c.capacite,
                                  -1);
            }
        }
        fclose(f);
    }
    
    // Appliquer le nouveau modèle
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
