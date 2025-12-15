#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entraineur.h"

int ajouter_entraineur(entraineur e) {
    FILE *f;
    entraineur tmp;
    int id_existe = 0;
    
    // Vérifier si l'ID existe déjà
    f = fopen("entraineurs.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                      tmp.nom, tmp.prenom, tmp.id, tmp.specialite, 
                      tmp.telephone, &tmp.experience,
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.sexe, tmp.email, tmp.adresse) != EOF) {
            
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
    
    // Sinon, ajouter l'entraîneur
    f = fopen("entraineurs.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                e.nom, e.prenom, e.id, e.specialite, 
                e.telephone, e.experience,
                e.jour, e.mois, e.annee,
                e.sexe, e.email, e.adresse);
        fclose(f);
        return 1; // Succès
    }
    
    return 0; // Échec
}

void afficher_entraineur(GtkWidget *liste) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    
    FILE *f;
    entraineur e;
    char date[20];
    
    // Vérifier si le modèle existe déjà
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));
    
    if (old_model == NULL) {
        // Créer les colonnes seulement si elles n'existent pas
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Spécialité", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Expérience", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date naissance", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }
    
    // Créer un nouveau store
    store = gtk_list_store_new(10, 
                              G_TYPE_STRING,  // nom
                              G_TYPE_STRING,  // prenom
                              G_TYPE_STRING,  // id
                              G_TYPE_STRING,  // specialite
                              G_TYPE_STRING,  // telephone
                              G_TYPE_INT,     // experience
                              G_TYPE_STRING,  // date
                              G_TYPE_STRING,  // sexe
                              G_TYPE_STRING,  // email
                              G_TYPE_STRING); // adresse
    
    // Lire le fichier
    f = fopen("entraineurs.txt", "r");
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                      e.nom, e.prenom, e.id, e.specialite, 
                      e.telephone, &e.experience,
                      &e.jour, &e.mois, &e.annee,
                      e.sexe, e.email, e.adresse) != EOF) {
            
            sprintf(date, "%d/%d/%d", e.jour, e.mois, e.annee);
            
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, e.nom,
                              1, e.prenom,
                              2, e.id,
                              3, e.specialite,
                              4, e.telephone,
                              5, e.experience,
                              6, date,
                              7, e.sexe,
                              8, e.email,
                              9, e.adresse,
                              -1);
        }
        fclose(f);
    }
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

void supprimer_entraineur(char *id) {
    FILE *f, *temp;
    entraineur e;
    
    f = fopen("entraineurs.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                      e.nom, e.prenom, e.id, e.specialite, 
                      e.telephone, &e.experience,
                      &e.jour, &e.mois, &e.annee,
                      e.sexe, e.email, e.adresse) != EOF) {
            
            if (strcmp(e.id, id) != 0) {
                fprintf(temp, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                        e.nom, e.prenom, e.id, e.specialite, 
                        e.telephone, e.experience,
                        e.jour, e.mois, e.annee,
                        e.sexe, e.email, e.adresse);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("entraineurs.txt");
        rename("temp.txt", "entraineurs.txt");
    }
}

void modifier_entraineur(char *old_id, entraineur e) {
    FILE *f, *temp;
    entraineur tmp;
    
    f = fopen("entraineurs.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                      tmp.nom, tmp.prenom, tmp.id, tmp.specialite, 
                      tmp.telephone, &tmp.experience,
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.sexe, tmp.email, tmp.adresse) != EOF) {
            
            if (strcmp(tmp.id, old_id) == 0) {
                // Écrire les nouvelles données
                fprintf(temp, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                        e.nom, e.prenom, e.id, e.specialite, 
                        e.telephone, e.experience,
                        e.jour, e.mois, e.annee,
                        e.sexe, e.email, e.adresse);
            } else {
                // Garder les anciennes données
                fprintf(temp, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                        tmp.nom, tmp.prenom, tmp.id, tmp.specialite, 
                        tmp.telephone, tmp.experience,
                        tmp.jour, tmp.mois, tmp.annee,
                        tmp.sexe, tmp.email, tmp.adresse);
            }
        }
        
        fclose(f);
        fclose(temp);
        
        remove("entraineurs.txt");
        rename("temp.txt", "entraineurs.txt");
    }
}

void vider(GtkWidget *lists)
{
    GtkListStore *store;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(lists));
    
    if (model != NULL) {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
}

int chercher_entraineur(char *id, entraineur *e) {
    FILE *f;
    entraineur tmp;
    int trouve = 0;
    
    f = fopen("entraineurs.txt", "r");
    
    if (f != NULL) {
        while (fscanf(f, "%s %s %s %s %s %d %d/%d/%d %s %s %s\n",
                      tmp.nom, tmp.prenom, tmp.id, tmp.specialite, 
                      tmp.telephone, &tmp.experience,
                      &tmp.jour, &tmp.mois, &tmp.annee,
                      tmp.sexe, tmp.email, tmp.adresse) != EOF) {
            
            if (strcmp(tmp.id, id) == 0) {
                // Copier les données trouvées
                strcpy(e->nom, tmp.nom);
                strcpy(e->prenom, tmp.prenom);
                strcpy(e->id, tmp.id);
                strcpy(e->specialite, tmp.specialite);
                strcpy(e->telephone, tmp.telephone);
                e->experience = tmp.experience;
                e->jour = tmp.jour;
                e->mois = tmp.mois;
                e->annee = tmp.annee;
                strcpy(e->sexe, tmp.sexe);
                strcpy(e->email, tmp.email);
                strcpy(e->adresse, tmp.adresse);
                
                trouve = 1;
                break;
            }
        }
        fclose(f);
    }
    
    return trouve;
}
