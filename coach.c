
#include "coach.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/* ==================================
 * Stockage en mémoire
 * ================================== */
#define MAX_COACHS 200
static Coach coachs[MAX_COACHS];
static int nb_coachs = 0;

/* ==================================
 * Lecture du fichier coachs.txt
 * Format (espaces) par ligne :
 *   ID NOM SPECIALITE DISPONIBILITE
 * Ex :
 *   C001 Jean_Dupont Fitness Disponible
 * ================================== */
void charger_coachs_depuis_fichier(void) {
    FILE *f = fopen("coachs.txt", "r");
    nb_coachs = 0;
    if (!f) {
        /* Pas de fichier => rien à charger */
        return;
    }
    while (nb_coachs < MAX_COACHS &&
           fscanf(f, "%19s %49s %49s %19s",
                  coachs[nb_coachs].id,
                  coachs[nb_coachs].nom,
                  coachs[nb_coachs].specialite,
                  coachs[nb_coachs].disponibilite) == 4) {
        nb_coachs++;
    }
    fclose(f);
}

/* ==================================
 * Colonnes TreeView coachs
 * ================================== */
void ensure_coach_treeview_columns(GtkTreeView *tv) {
    if (!tv) return;
    if (gtk_tree_view_get_columns(tv)) return; /* déjà créées */

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    const char *titles[] = {"ID", "Nom", "Spécialité", "Disponibilité"};
    for (int i = 0; i < 4; ++i) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes(titles[i], renderer, "text", i, NULL);
        gtk_tree_view_append_column(tv, column);
    }

    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tv));
    if (!store) {
        store = gtk_list_store_new(4,
                                   G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(tv, GTK_TREE_MODEL(store));
        g_object_unref(store);
    }
}

/* ==================================
 * Remplir le TreeView
 * ================================== */
void remplir_treeview_coachs(GtkTreeView *tv, int seulement_disponibles) {
    if (!tv) return;
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(tv));
    if (!store) return;

    gtk_list_store_clear(store);
    GtkTreeIter iter;
    for (int i = 0; i < nb_coachs; ++i) {
        if (seulement_disponibles &&
            strcmp(coachs[i].disponibilite, "Disponible") != 0) {
            continue;
        }
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, coachs[i].id,
                           1, coachs[i].nom,
                           2, coachs[i].specialite,
                           3, coachs[i].disponibilite,
                           -1);
    }
}

/* ==================================
 * Récupérer la ligne sélectionnée
 * ================================== */
gboolean get_selected_coach(GtkTreeView *tv, Coach *out) {
    if (!tv || !out) return FALSE;
    GtkTreeSelection *sel = gtk_tree_view_get_selection(tv);
    GtkTreeModel *model; GtkTreeIter it;
    if (!gtk_tree_selection_get_selected(sel, &model, &it)) return FALSE;

    gchar *id = NULL, *nom = NULL, *spec = NULL, *disp = NULL;
    gtk_tree_model_get(model, &it,
                       0, &id, 1, &nom, 2, &spec, 3, &disp, -1);

    if (!id || !nom || !spec || !disp) {
        if (id) g_free(id); if (nom) g_free(nom);
        if (spec) g_free(spec); if (disp) g_free(disp);
        return FALSE;
    }

    strncpy(out->id,            id,   sizeof out->id);            out->id[sizeof out->id - 1] = '\0';
    strncpy(out->nom,           nom,  sizeof out->nom);           out->nom[sizeof out->nom - 1] = '\0';
    strncpy(out->specialite,    spec, sizeof out->specialite);    out->specialite[sizeof out->specialite - 1] = '\0';
    strncpy(out->disponibilite, disp, sizeof out->disponibilite); out->disponibilite[sizeof out->disponibilite - 1] = '\0';

    g_free(id); g_free(nom); g_free(spec); g_free(disp);
    return TRUE;
}

/* ==================================
 * Enregistrer la demande (append)
 * Format demande.txt :
 *   YYYY-MM-DD HH:MM:SS;COACH_ID;COACH_NOM;CLIENT_ID
 * CLIENT_ID peut être vide (NULL)
 * ================================== */
gboolean enregistrer_demande(const char *id_coach,
                             const char *nom_coach,
                             const char *client_id) {
    FILE *f = fopen("demande.txt", "a");
    if (!f) return FALSE;

    time_t t = time(NULL);
    struct tm *tmv = localtime(&t);
    char stamp[32];
    strftime(stamp, sizeof stamp, "%Y-%m-%d %H:%M:%S", tmv);

    fprintf(f, "%s;%s;%s;%s\n",
            stamp,
            id_coach ? id_coach : "",
            nom_coach ? nom_coach : "",
            client_id ? client_id : "");
    fclose(f);
    return TRUE;
}

