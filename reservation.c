#include "reservation.h"
#include <string.h>
#include <stdlib.h>

void afficher_disponibilite_date(GtkTreeView *treeview)
{
    GtkListStore *store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
    GtkTreeIter iter;
    agent ag;
    FILE *f = fopen("equipment.txt", "r");
    if (!f) return;

    while (fscanf(f, "%s %s %d %s %s\n", ag.idag, ag.nom_ag, &ag.Quantite.jj, ag.Disponible, ag.etat) != EOF)
    {
        if (strcmp(ag.Disponible, "oui") == 0 && ag.Quantite.jj > 0)
        {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, ag.idag, 1, ag.nom_ag, 2, ag.Quantite.jj, -1);
        }
    }
    fclose(f);

    // Colonnes (une seule fois)
    if (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) == NULL)
    {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *col;

        col = gtk_tree_view_column_new_with_attributes("Équipement", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(treeview, col);

        col = gtk_tree_view_column_new_with_attributes("Disponibilité", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(treeview, col);

        col = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(treeview, col);
    }

    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
}

int reserver_equipement(Reservation r)
{
    agent *ag = chercherequipment(r.id);
    if (!ag || strcmp(ag->Disponible, "non") == 0 || ag->Quantite.jj < r.quantite)
    {
        if (ag) free(ag);
        return 0;
    }

    ag->Quantite.jj -= r.quantite;
    if (ag->Quantite.jj <= 0) strcpy(ag->Disponible, "non");

    modiferequipment(*ag);
    free(ag);

    FILE *f = fopen("reservations.txt", "a");
    if (f)
    {
        fprintf(f, "%s %s %02d/%02d/%d %s %d\n", r.id, r.nom, r.jour, r.mois, r.annee, r.periode, r.quantite);
        fclose(f);
        return 1;
    }
    return 0;
}
