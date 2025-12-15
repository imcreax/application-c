#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "evenement.h"

// Fonction pour vérifier si l'heure est le soir (19h-22h ou 00-03h)
int est_heure_soir(const char *heure) {
    if (strstr(heure, "19h") || strstr(heure, "22h") || 
        strstr(heure, "00") || strstr(heure, "03h")) {
        return 1;
    }
    return 0;
}

int ajouter_evenement(evenement e) {
    FILE *f;
    evenement tmp;
    int id_existe = 0;
    
    // Vérifier si l'ID existe déjà 
    f = fopen("evenements.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      tmp.id, tmp.nom, 
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.heure, &tmp.buffet_disponible,
                      tmp.organisateur, tmp.site_web) != EOF) {
            
            if (strcmp(tmp.id, e.id) == 0) {
                id_existe = 1;
                break;
            }
        }
        fclose(f);
    }
    
    // Si l'ID existe déjà, retourner 0 (échec)
    if (id_existe) {
        return 0;
    }
    
    // Sinon, ajouter l'événement
    f = fopen("evenements.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                e.id, e.nom,
                e.jour, e.mois, e.annee,
                e.heure, e.buffet_disponible,
                e.organisateur, e.site_web);
        fclose(f);
        return 1; // Succès
    }
    
    return 0; // Échec
}

void afficher_evenement(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    
    FILE *f;
    evenement e;
    char date[20];
    char buffet[20];
    
    // Vérifier si le modèle existe déjà 
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    
    if (old_model == NULL) {
        // Créer les colonnes seulement si elles n'existent pas
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Buffet", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Organisateur", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Site Web", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    
    // Créer un nouveau store avec 7 colonnes
    store = gtk_list_store_new(7, 
                              G_TYPE_STRING,  // id
                              G_TYPE_STRING,  // nom
                              G_TYPE_STRING,  // date
                              G_TYPE_STRING,  // heure
                              G_TYPE_STRING,  // buffet
                              G_TYPE_STRING,  // organisateur
                              G_TYPE_STRING); // site_web
    
    // Lire le fichier
    f = fopen("evenements.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      e.id, e.nom,
                      &e.jour, &e.mois, &e.annee,
                      e.heure, &e.buffet_disponible,
                      e.organisateur, e.site_web) != EOF) {
            
            sprintf(date, "%d/%d/%d", e.jour, e.mois, e.annee);
            strcpy(buffet, e.buffet_disponible ? "Oui" : "Non");
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, e.id,
                              1, e.nom,
                              2, date,
                              3, e.heure,
                              4, buffet,
                              5, e.organisateur,
                              6, e.site_web,
                              -1);
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

void supprimer_evenement(char *id) {
    FILE *f, *temp;
    evenement e;
    
    f = fopen("evenements.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      e.id, e.nom,
                      &e.jour, &e.mois, &e.annee,
                      e.heure, &e.buffet_disponible,
                      e.organisateur, e.site_web) != EOF) {
            
            if (strcmp(e.id, id) != 0) {
                fprintf(temp, "%s %s %d/%d/%d %s %d %s %s\n",
                        e.id, e.nom,
                        e.jour, e.mois, e.annee,
                        e.heure, e.buffet_disponible,
                        e.organisateur, e.site_web);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("evenements.txt");
        rename("temp.txt", "evenements.txt");
    }
}

void modifier_evenement(char *old_id, evenement e) {
    FILE *f, *temp;
    evenement tmp;
    
    f = fopen("evenements.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      tmp.id, tmp.nom,
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.heure, &tmp.buffet_disponible,
                      tmp.organisateur, tmp.site_web) != EOF) {
            
            if (strcmp(tmp.id, old_id) == 0) {
                // Écrire les nouvelles données
                fprintf(temp, "%s %s %d/%d/%d %s %d %s %s\n",
                        e.id, e.nom,
                        e.jour, e.mois, e.annee,
                        e.heure, e.buffet_disponible,
                        e.organisateur, e.site_web);
            } else {
                // Garder les anciennes données
                fprintf(temp, "%s %s %d/%d/%d %s %d %s %s\n",
                        tmp.id, tmp.nom,
                        tmp.jour, tmp.mois, tmp.annee,
                        tmp.heure, tmp.buffet_disponible,
                        tmp.organisateur, tmp.site_web);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("evenements.txt");
        rename("temp.txt", "evenements.txt");
    }
}

void vider_evenement(GtkWidget *lists)
{
    GtkListStore *store;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(lists));
    
    if (model != NULL) {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
}

int chercher_evenement(char *id, evenement *e) {
    FILE *f;
    evenement tmp;
    int trouve = 0;
    
    f = fopen("evenements.txt", "r");
    
    if (f != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      tmp.id, tmp.nom,
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.heure, &tmp.buffet_disponible,
                      tmp.organisateur, tmp.site_web) != EOF) {
            
            if (strcmp(tmp.id, id) == 0) {
                // Copier les données trouvées
                strcpy(e->id, tmp.id);
                strcpy(e->nom, tmp.nom);
                e->jour = tmp.jour;
                e->mois = tmp.mois;
                e->annee = tmp.annee;
                strcpy(e->heure, tmp.heure);
                e->buffet_disponible = tmp.buffet_disponible;
                strcpy(e->organisateur, tmp.organisateur);
                strcpy(e->site_web, tmp.site_web);
                
                trouve = 1;
                break;
            }
        }
        fclose(f);
    }
    
    return trouve;
}

float calculer_pourcentage_soir(void) {
    FILE *f;
    evenement e;
    int total = 0;
    int soir = 0;
    
    f = fopen("evenements.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %d/%d/%d %s %d %s %s\n",
                      e.id, e.nom,
                      &e.jour, &e.mois, &e.annee,
                      e.heure, &e.buffet_disponible,
                      e.organisateur, e.site_web) != EOF) {
            total++;
            if (est_heure_soir(e.heure)) {
                soir++;
            }
        }
        fclose(f);
    }
    
    if (total == 0) return 0.0;
    return (float)(soir * 100) / total;
}

float calculer_pourcentage_jour(void) {
    return 100.0 - calculer_pourcentage_soir();
}
