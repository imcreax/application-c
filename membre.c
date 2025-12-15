#include "membre.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define MAX_MEMBRES 1000

static Membre membres[MAX_MEMBRES];
static int nb_membres = 0;

void ajouter_membre(Membre *m) {
    if (nb_membres < MAX_MEMBRES) {
        membres[nb_membres++] = *m;
        sauvegarder_membres_dans_fichier();
    } else {
        g_printerr("Erreur: nombre maximum de membres atteint\n");
    }
}

void supprimer_membre(char *id) {
    for (int i = 0; i < nb_membres; ++i) {
        if (strcmp(membres[i].id, id) == 0) {
            for (int j = i; j < nb_membres - 1; ++j) {
                membres[j] = membres[j + 1];
            }
            nb_membres--;
            sauvegarder_membres_dans_fichier();
            return;
        }
    }
    g_printerr("Membre non trouvé pour suppression: %s\n", id);
}

Membre* rechercher_membre(char *id) {
    for (int i = 0; i < nb_membres; ++i) {
        if (strcmp(membres[i].id, id) == 0) return &membres[i];
    }
    return NULL;
}

void modifier_membre(char *id, Membre *nouveau) {
    for (int i = 0; i < nb_membres; ++i) {
        if (strcmp(membres[i].id, id) == 0) {
            membres[i] = *nouveau;
            sauvegarder_membres_dans_fichier();
            return;
        }
    }
    g_printerr("Membre non trouvé pour modification: %s\n", id);
}

void charger_membres_depuis_fichier(void) {
    FILE *f = fopen("membres.txt", "r");
    if (!f) {
        f = fopen("membres.txt", "w");
        if (f) fclose(f);
        nb_membres = 0;
        return;
    }
    nb_membres = 0;
    while (nb_membres < MAX_MEMBRES &&
           fscanf(f, "%19s %49s %49s %d %19s %99s %9s %19s",
                  membres[nb_membres].id,
                  membres[nb_membres].nom,
                  membres[nb_membres].prenom,
                  &membres[nb_membres].age,
                  membres[nb_membres].telephone,
                  membres[nb_membres].email,
                  membres[nb_membres].sexe,
                  membres[nb_membres].type_abonnement) == 8) {
        nb_membres++;
    }
    fclose(f);
}

void sauvegarder_membres_dans_fichier(void) {
    FILE *f = fopen("membres.txt", "w");
    if (!f) {
        g_printerr("Erreur: impossible d'ouvrir membres.txt en écriture\n");
        return;
    }
    for (int i = 0; i < nb_membres; ++i) {
        fprintf(f, "%s %s %s %d %s %s %s %s\n",
                membres[i].id,
                membres[i].nom,
                membres[i].prenom,
                membres[i].age,
                membres[i].telephone,
                membres[i].email,
                membres[i].sexe,
                membres[i].type_abonnement);
    }
    fclose(f);
}

void afficher_membres_dans_treeview(GtkTreeView *treeview) {
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) {
        store = gtk_list_store_new(8,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
        g_object_unref(store);
        store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    }
    gtk_list_store_clear(store);
    GtkTreeIter iter;
    for (int i = 0; i < nb_membres; ++i) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           0, membres[i].id,
                           1, membres[i].nom,
                           2, membres[i].prenom,
                           3, membres[i].age,
                           4, membres[i].telephone,
                           5, membres[i].email,
                           6, membres[i].sexe,
                           7, membres[i].type_abonnement,
                           -1);
    }
}

void filtrer_membres_par_sexe(GtkTreeView *treeview, char *sexe) {
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) return;
    gtk_list_store_clear(store);
    GtkTreeIter iter;
    for (int i = 0; i < nb_membres; ++i) {
        if (strcmp(membres[i].sexe, sexe) == 0) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, membres[i].id,
                               1, membres[i].nom,
                               2, membres[i].prenom,
                               3, membres[i].age,
                               4, membres[i].telephone,
                               5, membres[i].email,
                               6, membres[i].sexe,
                               7, membres[i].type_abonnement,
                               -1);
        }
    }
}

void trier_membres_par_age(GtkTreeView *treeview, int ordre_croissant) {
    for (int i = 0; i < nb_membres - 1; ++i) {
        for (int j = 0; j < nb_membres - i - 1; ++j) {
            if ((ordre_croissant && membres[j].age > membres[j + 1].age) ||
                (!ordre_croissant && membres[j].age < membres[j + 1].age)) {
                Membre tmp = membres[j];
                membres[j] = membres[j + 1];
                membres[j + 1] = tmp;
            }
        }
    }
    afficher_membres_dans_treeview(treeview);
}

void exporter_membres_csv(const char *filename, GtkTreeView *treeview) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        g_printerr("Erreur: impossible de créer %s\n", filename);
        return;
    }
    fprintf(f, "ID,Nom,Prenom,Age,Telephone,Email,Sexe,Type_Abonnement\n");
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    if (!model) { fclose(f); return; }
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        gchar *id, *nom, *prenom, *tel, *mail, *sexe, *type;
        gint age;
        gtk_tree_model_get(model, &iter,
                           0, &id, 1, &nom, 2, &prenom, 3, &age,
                           4, &tel, 5, &mail, 6, &sexe, 7, &type, -1);
        fprintf(f, "%s,%s,%s,%d,%s,%s,%s,%s\n",
                id ? id : "", nom ? nom : "", prenom ? prenom : "",
                age, tel ? tel : "", mail ? mail : "", sexe ? sexe : "", type ? type : "");
        if (id)    g_free(id);
        if (nom)   g_free(nom);
        if (prenom)g_free(prenom);
        if (tel)   g_free(tel);
        if (mail)  g_free(mail);
        if (sexe)  g_free(sexe);
        if (type)  g_free(type);
        valid = gtk_tree_model_iter_next(model, &iter);
    }
    fclose(f);
}

char* generer_statistiques_membres(void) {
    int total = nb_membres;
    int hommes = 0, femmes = 0;
    int mensuel = 0, semestriel = 0, annuel = 0;
    int age_sum = 0;

    for (int i = 0; i < nb_membres; ++i) {
        if (strcmp(membres[i].sexe, "Homme") == 0) hommes++;
        else if (strcmp(membres[i].sexe, "Femme") == 0) femmes++;

        if (strcmp(membres[i].type_abonnement, "Mensuel") == 0) mensuel++;
        else if (strcmp(membres[i].type_abonnement, "Semestriel") == 0) semestriel++;
        else if (strcmp(membres[i].type_abonnement, "Annuel") == 0) annuel++;

        age_sum += membres[i].age;
    }

    double age_moyen = (total > 0) ? ((double)age_sum / (double)total) : 0.0;

    gchar *txt = g_strdup_printf(
        "Statistiques des membres\n"
        "------------------------\n"
        "Total membres : %d\n"
        "Homme : %d | Femme : %d\n"
        "Âge moyen : %.2f\n"
        "Abonnements : Mensuel=%d, Semestriel=%d, Annuel=%d\n",
        total, hommes, femmes, age_moyen, mensuel, semestriel, annuel
    );

    return txt;
}
