
#ifndef COACH_H
#define COACH_H

#include <gtk/gtk.h>

typedef struct {
    char id[20];
    char nom[50];
    char specialite[50];
    char disponibilite[20]; /* "Disponible" ou "Occupé" */
} Coach;

/* Données */
void charger_coachs_depuis_fichier(void);

/* UI / TreeView */
void ensure_coach_treeview_columns(GtkTreeView *tv);
void remplir_treeview_coachs(GtkTreeView *tv, int seulement_disponibles);

/* Sélection */
gboolean get_selected_coach(GtkTreeView *tv, Coach *out);

/* Demande (append dans demande.txt) */
gboolean enregistrer_demande(const char *id_coach,
                             const char *nom_coach,
                             const char *client_id /* optionnel, peut être NULL */);

#endif /* COACH_H */

