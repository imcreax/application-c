#include <stdio.h>
#include <string.h>
#include "centre.h"
#include "inscription.h"

int ajouter_inscription(Inscription i) {
    FILE *f = fopen("inscriptions.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s\n", i.idCentre, i.nomEntraineur, i.emailEntraineur);
        fclose(f);
        return 1;
    }
    return 0;
}

void afficher_centres_par_ville(char *ville, GtkWidget *treeview) {
    FILE *f = fopen("centres.txt", "r");
    Centre c;
    char ligne[1024];
    
    if (f == NULL) {
        g_warning("Impossible d'ouvrir centres.txt");
        return;
    }
    
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    GtkListStore *store;
    GtkTreeIter iter;
    
    // Si le modèle n'existe pas, le créer
    if (model == NULL) {
        store = gtk_list_store_new(10,
                                   G_TYPE_INT,    // 0: ID
                                   G_TYPE_STRING, // 1: Nom
                                   G_TYPE_STRING, // 2: Adresse
                                   G_TYPE_STRING, // 3: Ville
                                   G_TYPE_STRING, // 4: Téléphone
                                   G_TYPE_STRING, // 5: Email
                                   G_TYPE_INT,    // 6: Capacité
                                   G_TYPE_STRING, // 7: Weekend
                                   G_TYPE_STRING, // 8: Parking
                                   G_TYPE_STRING  // 9: Type
        );
        
        // Créer les colonnes
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;
        
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
        column = gtk_tree_view_column_new_with_attributes("Weekend", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Parking", renderer, "text", 8, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 9, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
        
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
        g_object_unref(store);
    } else {
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
    
    // Lire et afficher les centres
    int compteur = 0;
    while (fgets(ligne, sizeof(ligne), f) != NULL && compteur < 1000) {
        int scan_result = sscanf(ligne, "%d;%49[^;];%99[^;];%29[^;];%19[^;];%49[^;];%d;%d;%d;%d",
                                 &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                                 &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type);
        
        if (scan_result == 10 && strcmp(c.ville, ville) == 0) {
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
            compteur++;
        }
    }
    
    fclose(f);
    
    printf("DEBUG: %d centres affichés pour la ville '%s'\n", compteur, ville);
    
    if (compteur == 0) {
        g_warning("Aucun centre trouvé pour la ville: %s", ville);
    }
}
