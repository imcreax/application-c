/*
 * CALLBACKS.C - Combined callbacks for the main project
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "membre.h"
#include "entraineur.h"
#include "equipment.h"
#include "reservation.h"
#include "stats.h"
#include "admin.h"
#include "evenement.h"
#include "centre.h"
#include "inscription.h"
#include "coach.h"
#include "utilisateur.h"

/* =========================================================
 * FENÊTRES (globals renseignées par main.c)
 * ========================================================= */
// Après les #include, avant les variables globales
void vider_treeview(GtkWidget *treeview);
void afficher_centre_dans_treeview(GtkWidget *treeview, Centre c);
int authentifier_utilisateur(const char *identifiant, const char *mot_de_passe, char *type);
void afficher_statistiques(GtkWidget *window);
GtkWidget *gestion_membres_window = NULL;
GtkWidget *ajouter_window        = NULL;
GtkWidget *supprimer_window      = NULL;
GtkWidget *rechercher_window     = NULL;
GtkWidget *modifier_window       = NULL;
GtkWidget *trier_window          = NULL;
GtkWidget *filtrer_window        = NULL;
GtkWidget *statistique_window    = NULL;

/* Variable globale pour stocker l'ID sélectionné dans recherche */
static gchar *id_selectionne_recherche = NULL;

// Variables globales
int ouvert_weekend = 0;
int parking_disponible = 0;
char type[10] = "";
int selected_centre_id = -1;
int filtre_parking = -1;
int filtre_weekend = -1;int x = 1;
int x2=1;
int c=0;

// À ajouter dans callbacks.c, après les variables globales

void initialiser_toutes_fenetres_cachees(void)
{
    // Ne rien faire ici !
    // Les fenêtres seront créées UNIQUEMENT quand on clique sur les boutons
    // C'est la méthode correcte : créer à la demande
}
void initialiser_treeview_membres(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // Supprimer les anciennes colonnes si elles existent
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *l = columns; l != NULL; l = l->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(l->data));
    }
    g_list_free(columns);
    
    // Créer le modèle
    GtkListStore *store = gtk_list_store_new(8,
                                             G_TYPE_STRING,  // ID
                                             G_TYPE_STRING,  // Nom
                                             G_TYPE_STRING,  // Prénom
                                             G_TYPE_INT,     // Age
                                             G_TYPE_STRING,  // Téléphone
                                             G_TYPE_STRING,  // Email
                                             G_TYPE_STRING,  // Sexe
                                             G_TYPE_STRING); // Type abonnement
    
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Colonne ID
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Nom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Prénom
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Age
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Age", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Téléphone
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Email
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Email", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Sexe
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Sexe", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    // Colonne Type Abonnement
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Abonnement", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);
}
/* ========== CALLBACKS ESPACE ADMIN ========== */

void on_g_membre_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_membre;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des membres
    window_membre = create_emna_gestion_des_membres();
    gtk_widget_show(window_membre);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_g_entraineur_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_entraineur;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des entraîneurs
    window_entraineur = create_ge();
    gtk_widget_show(window_entraineur);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_g_cours_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_cours;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des cours
    window_cours = create_tasnim_window16_gestiondescourssportifs();
    gtk_widget_show(window_cours);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_g_equipement_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_equipment;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des équipements
    window_equipment = create_Afficherequipment();
    gtk_widget_show(window_equipment);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_g_centre_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_centre;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des centres
    window_centre = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(window_centre);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_g_evenement_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_principale;
    GtkWidget *window_evenement;
    
    window_principale = lookup_widget(GTK_WIDGET(button), "Espace_Admin");
    
    // Créer et afficher la fenêtre de gestion des événements
    window_evenement = create_Sarra___v__nement();
    gtk_widget_show(window_evenement);
    
    // Optionnel : cacher la fenêtre principale
    // gtk_widget_hide(window_principale);
}

void on_im_retour_EA_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // Fermer l'application
    gtk_widget_destroy(window_current);
    gtk_main_quit();
}
// Callback pour fermer la fenêtre
void on_window_destroy(GtkObject *object, gpointer user_data)
{
    gtk_main_quit();
}

void on_SarraK_button___quip_clicked(GtkButton *button, gpointer user_data)
{
    // Fonction à implémenter pour la gestion des équipements
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Fonctionnalité à implémenter");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/* ========== CALLBACKS FENETRE GESTION EVENEMENTS ========== */

void on_SarraK_button_Eventadd_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_ajout;
    GtkWidget *window_event;
    
    window_ajout = create_Sarra_Ajout();
    gtk_widget_show(window_ajout);
    
    window_event = lookup_widget(GTK_WIDGET(button), "Sarra___v__nement");
    gtk_widget_hide(window_event);
}

void on_SarraK_button_Eventaffiche_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_search;
    GtkWidget *window_event;
    GtkWidget *treeview;
    
    window_search = create_Sarra_Search();
    gtk_widget_show(window_search);
    
    treeview = lookup_widget(window_search, "satreeview1");
    afficher_evenement(treeview);
    
    g_signal_connect(treeview, "row-activated", G_CALLBACK(on_treeview1_row_activated), NULL);
    
    window_event = lookup_widget(GTK_WIDGET(button), "Sarra___v__nement");
    gtk_widget_hide(window_event);
}

void on_SarraK_button_Eventstat_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_stat;
    GtkWidget *window_event;
    GtkWidget *label_stat;
    GtkWidget *radio_jour;
    char pourcentage[50];
    
    window_stat = create_Sarra_Stat();
    
    // Calculer et afficher le pourcentage de jour par défaut
    float pourcent_jour = calculer_pourcentage_jour();
    sprintf(pourcentage, "%.1f%%", pourcent_jour);
    
    label_stat = lookup_widget(window_stat, "SarraK_label_Stat");
    gtk_label_set_text(GTK_LABEL(label_stat), pourcentage);
    
    // Activer le bouton jour par défaut
    radio_jour = lookup_widget(window_stat, "SarraK_radiobutton_Jour");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_jour), TRUE);
    
    gtk_widget_show(window_stat);
    
    window_event = lookup_widget(GTK_WIDGET(button), "Sarra___v__nement");
    gtk_widget_hide(window_event);
}

void on_SarraK_button_Gest_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_admin;
    
    gtk_widget_destroy(window_current);
    
    // REMPLACER create_Sarra_Admin() par create_Espace_Admin()
    window_admin = create_Espace_Admin();
    gtk_widget_show(window_admin);
}
/* ========== CALLBACKS FENETRE AJOUT ========== */


void on_SarraK_button_Add_clicked(GtkButton *button, gpointer user_data)
{
    evenement e;
    GtkWidget *window;
    
    window = lookup_widget(GTK_WIDGET(button), "Sarra_Ajout");
    
    GtkWidget *id_entry = lookup_widget(window, "SarraK_entry_ID");
    GtkWidget *nom_entry = lookup_widget(window, "SarraK_entry_Name");
    GtkWidget *org_entry = lookup_widget(window, "SarraK_entry_Organis");
    GtkWidget *web_entry = lookup_widget(window, "SarraK_entry_Web");
    GtkWidget *heure_combo = lookup_widget(window, "comboboxentry1");
    GtkWidget *jour_spin = lookup_widget(window, "spinbutton1");
    GtkWidget *mois_spin = lookup_widget(window, "spinbutton2");
    GtkWidget *annee_spin = lookup_widget(window, "spinbutton3");
    GtkWidget *buffet_yes = lookup_widget(window, "SarraK_checkbutton_Yes");
    
    // Récupérer les valeurs
    strcpy(e.id, gtk_entry_get_text(GTK_ENTRY(id_entry)));
    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(nom_entry)));
    strcpy(e.organisateur, gtk_entry_get_text(GTK_ENTRY(org_entry)));
    strcpy(e.site_web, gtk_entry_get_text(GTK_ENTRY(web_entry)));
    
    gchar *heure_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(heure_combo));
    if (heure_text != NULL) {
        strcpy(e.heure, heure_text);
        g_free(heure_text);
    } else {
        strcpy(e.heure, "");
    }
    
    e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour_spin));
    e.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_spin));
    e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_spin));
    
    e.buffet_disponible = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(buffet_yes)) ? 1 : 0;
    
    // Ajouter l'événement
    int resultat = ajouter_evenement(e);
    
    if (resultat == 1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Evenement enregistre avec succes!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        // Vider les champs
        gtk_entry_set_text(GTK_ENTRY(id_entry), "");
        gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
        gtk_entry_set_text(GTK_ENTRY(org_entry), "");
        gtk_entry_set_text(GTK_ENTRY(web_entry), "");
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur: Un evenement avec l'ID '%s' existe deja!", e.id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_SarraK_button_Del_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_Ajout");
    
    // Vider tous les champs
    GtkWidget *id_entry = lookup_widget(window, "SarraK_entry_ID");
    GtkWidget *nom_entry = lookup_widget(window, "SarraK_entry_Name");
    GtkWidget *org_entry = lookup_widget(window, "SarraK_entry_Organis");
    GtkWidget *web_entry = lookup_widget(window, "SarraK_entry_Web");
    
    gtk_entry_set_text(GTK_ENTRY(id_entry), "");
    gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
    gtk_entry_set_text(GTK_ENTRY(org_entry), "");
    gtk_entry_set_text(GTK_ENTRY(web_entry), "");
}

void on_SarraK_button_Ajoutretour_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_event;
    
    gtk_widget_destroy(window_current);
    
    window_event = create_Sarra___v__nement();
    gtk_widget_show(window_event);
}

/* ========== CALLBACKS FENETRE AFFICHER ========== */

void on_satreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                                 GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *id;
    
    model = gtk_tree_view_get_model(treeview);
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        
        GtkWidget *window_suppoumod = create_Sarra_suppoumod();
        g_object_set_data_full(G_OBJECT(window_suppoumod), "selected_id", 
                               g_strdup(id), (GDestroyNotify)g_free);
        
        gtk_widget_show(window_suppoumod);
        
        g_free(id);
    }
}

void on_SarraK_button_actualiser_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_Search");
    GtkWidget *treeview = lookup_widget(window, "satreeview1");
    
    vider_evenement(treeview);
    afficher_evenement(treeview);
}

void on_SarraK_button_Find_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_Search");
    GtkWidget *entry_id = lookup_widget(window, "SarraK_entry_SearchID");
    GtkWidget *treeview = lookup_widget(window, "satreeview1");
    
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    evenement e;
    
    if (chercher_evenement((char *)id, &e)) {
        // Vider le treeview
        vider_evenement(treeview);
        
        // Afficher seulement l'événement trouvé
        GtkListStore *store;
        GtkTreeIter iter;
        char date[20];
        char buffet[20];
        
        GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
        if (model == NULL) {
            afficher_evenement(treeview);
            model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
        }
        
        store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
        
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
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_WARNING,
                                                   GTK_BUTTONS_OK,
                                                   "Evenement avec l'ID '%s' non trouve!", id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_SarraK_button_Retour_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_event;
    
    gtk_widget_destroy(window_current);
    
    window_event = create_Sarra___v__nement();
    gtk_widget_show(window_event);
}

/* ========== CALLBACKS FENETRE SUPPRESSION/MODIFICATION ========== */

void on_SarraK_button_Supp_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_suppoumod = lookup_widget(GTK_WIDGET(button), "Sarra_suppoumod");
    gchar *id = (gchar *)g_object_get_data(G_OBJECT(window_suppoumod), "selected_id");
    
    if (id != NULL) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window_suppoumod),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "Etes-vous sur de vouloir supprimer cet evenement?");
        
        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        if (result == GTK_RESPONSE_YES) {
            supprimer_evenement(id);
            
            GtkWidget *info_dialog = gtk_message_dialog_new(GTK_WINDOW(window_suppoumod),
                                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            GTK_MESSAGE_INFO,
                                                            GTK_BUTTONS_OK,
                                                            "Evenement supprime avec succes!");
            gtk_dialog_run(GTK_DIALOG(info_dialog));
            gtk_widget_destroy(info_dialog);
            
            gtk_widget_destroy(window_suppoumod);
        }
    }
}

void on_SarraK_button_modifier_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_suppoumod = lookup_widget(GTK_WIDGET(button), "Sarra_suppoumod");
    gchar *id = (gchar *)g_object_get_data(G_OBJECT(window_suppoumod), "selected_id");
    
    if (id != NULL) {
        evenement e;
        
        if (chercher_evenement(id, &e)) {
            GtkWidget *window_modif = create_Sarra_Modif();
            
            // Remplir les champs avec les données existantes
            GtkWidget *id_entry = lookup_widget(window_modif, "SarraK_entry_IDmod");
            GtkWidget *nom_entry = lookup_widget(window_modif, "SarraK_entry_Namemod");
            GtkWidget *org_entry = lookup_widget(window_modif, "SarraK_entry_Modif");
            GtkWidget *web_entry = lookup_widget(window_modif, "Modif_entry_Webmod");
            GtkWidget *jour_spin = lookup_widget(window_modif, "spinbutton4");
            GtkWidget *mois_spin = lookup_widget(window_modif, "spinbutton5");
            GtkWidget *annee_spin = lookup_widget(window_modif, "spinbutton6");
            GtkWidget *buffet_yes = lookup_widget(window_modif, "SarraK_checkbutton_Yesmod");
            GtkWidget *buffet_no = lookup_widget(window_modif, "SarraK_checkbutton_Nomod");
            
            gtk_entry_set_text(GTK_ENTRY(id_entry), e.id);
            gtk_entry_set_text(GTK_ENTRY(nom_entry), e.nom);
            gtk_entry_set_text(GTK_ENTRY(org_entry), e.organisateur);
            gtk_entry_set_text(GTK_ENTRY(web_entry), e.site_web);
            
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour_spin), e.jour);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois_spin), e.mois);
            gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee_spin), e.annee);
            
            if (e.buffet_disponible) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffet_yes), TRUE);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffet_no), FALSE);
            } else {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffet_yes), FALSE);
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffet_no), TRUE);
            }
            
            // Sauvegarder l'ID original pour la modification
            g_object_set_data_full(G_OBJECT(window_modif), "id_to_modify", 
                                   g_strdup(id), (GDestroyNotify)g_free);
            
            gtk_widget_show(window_modif);
            gtk_widget_hide(window_suppoumod);
        }
    }
}

void on_SarraK_button_Return_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window_current);
}

/* ========== CALLBACKS FENETRE MODIFICATION ========== */

void on_SarraK_button_Misajour_clicked(GtkButton *button, gpointer user_data)
{
    evenement e;
    GtkWidget *window;
    gchar *old_id;
    
    window = lookup_widget(GTK_WIDGET(button), "Sarra_Modif");
    old_id = (gchar *)g_object_get_data(G_OBJECT(window), "id_to_modify");
    
    if (old_id == NULL) {
        return;
    }
    
    GtkWidget *id_entry = lookup_widget(window, "SarraK_entry_IDmod");
    GtkWidget *nom_entry = lookup_widget(window, "SarraK_entry_Namemod");
    GtkWidget *org_entry = lookup_widget(window, "SarraK_entry_Modif");
    GtkWidget *web_entry = lookup_widget(window, "Modif_entry_Webmod");
    GtkWidget *heure_combo = lookup_widget(window, "comboboxentry2");
    GtkWidget *jour_spin = lookup_widget(window, "spinbutton4");
    GtkWidget *mois_spin = lookup_widget(window, "spinbutton5");
    GtkWidget *annee_spin = lookup_widget(window, "spinbutton6");
    GtkWidget *buffet_yes = lookup_widget(window, "SarraK_checkbutton_Yesmod");
    
    strcpy(e.id, gtk_entry_get_text(GTK_ENTRY(id_entry)));
    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(nom_entry)));
    strcpy(e.organisateur, gtk_entry_get_text(GTK_ENTRY(org_entry)));
    strcpy(e.site_web, gtk_entry_get_text(GTK_ENTRY(web_entry)));
    
    gchar *heure_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(heure_combo));
    if (heure_text != NULL) {
        strcpy(e.heure, heure_text);
        g_free(heure_text);
    } else {
        strcpy(e.heure, "");
    }
    
    e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour_spin));
    e.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_spin));
    e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_spin));
    
    e.buffet_disponible = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(buffet_yes)) ? 1 : 0;
    
    modifier_evenement(old_id, e);
    
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Evenement modifie avec succes!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void on_Modif_button_Deletemod_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_Modif");
    
    // Vider tous les champs
    GtkWidget *id_entry = lookup_widget(window, "SarraK_entry_IDmod");
    GtkWidget *nom_entry = lookup_widget(window, "SarraK_entry_Namemod");
    GtkWidget *org_entry = lookup_widget(window, "SarraK_entry_Modif");
    GtkWidget *web_entry = lookup_widget(window, "Modif_entry_Webmod");
    
    gtk_entry_set_text(GTK_ENTRY(id_entry), "");
    gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
    gtk_entry_set_text(GTK_ENTRY(org_entry), "");
    gtk_entry_set_text(GTK_ENTRY(web_entry), "");
}

void on_SarraK_button_ModifRetour_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_event;
    
    gtk_widget_destroy(window_current);
    
    window_event = create_Sarra___v__nement();
    gtk_widget_show(window_event);
}

/* ========== CALLBACKS FENETRE INSCRIPTION ========== */

void on_SarraK_button_Inscrip_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_subscribe");
    GtkWidget *entry_userid = lookup_widget(window, "SarraK_entry_InscripID");
    GtkWidget *entry_eventid = lookup_widget(window, "SarraK_entry_EventID");
    
    const gchar *user_id = gtk_entry_get_text(GTK_ENTRY(entry_userid));
    const gchar *event_id = gtk_entry_get_text(GTK_ENTRY(entry_eventid));
    
    // Vérifier si l'événement existe
    evenement e;
    if (chercher_evenement((char *)event_id, &e)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Inscription reussie a l'evenement '%s'!", e.nom);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        // Vider les champs
        gtk_entry_set_text(GTK_ENTRY(entry_userid), "");
        gtk_entry_set_text(GTK_ENTRY(entry_eventid), "");
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Evenement non trouve!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_Inscrip_button_Inscripdel_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Sarra_subscribe");
    
    // Vider les champs
    GtkWidget *entry_userid = lookup_widget(window, "SarraK_entry_InscripID");
    GtkWidget *entry_eventid = lookup_widget(window, "SarraK_entry_EventID");
    
    gtk_entry_set_text(GTK_ENTRY(entry_userid), "");
    gtk_entry_set_text(GTK_ENTRY(entry_eventid), "");
}

void on_SarraK_button_InscripRetour_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window_current);
}

/* ========== CALLBACKS FENETRE STATISTIQUES ========== */

void on_SarraK_radiobutton_Jour_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(togglebutton));
        GtkWidget *label_stat = lookup_widget(window, "SarraK_label_Stat");
        
        float pourcent_jour = calculer_pourcentage_jour();
        char pourcentage[50];
        sprintf(pourcentage, "%.1f%%", pourcent_jour);
        
        gtk_label_set_text(GTK_LABEL(label_stat), pourcentage);
    }
}

void on_SarraK_radiobutton_Soir_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(togglebutton));
        GtkWidget *label_stat = lookup_widget(window, "SarraK_label_Stat");
        
        float pourcent_soir = calculer_pourcentage_soir();
        char pourcentage[50];
        sprintf(pourcentage, "%.1f%%", pourcent_soir);
        
        gtk_label_set_text(GTK_LABEL(label_stat), pourcentage);
    }
}


/* ========== CALLBACKS FENETRE GE (GESTION) ========== */

void on_ajouter_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_ajouter;
    GtkWidget *window_ge;
    
    window_ajouter = create_Ajouter();
    gtk_widget_show(window_ajouter);
    
    window_ge = lookup_widget(GTK_WIDGET(button), "ge");
    gtk_widget_hide(window_ge);
}

void on_afiicher_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_afficher;
    GtkWidget *window_ge;
    GtkWidget *treeview;
    
    window_afficher = create_Afficher();
    gtk_widget_show(window_afficher);
    
    treeview = lookup_widget(window_afficher, "abtreeview1");
    afficher_entraineur(treeview);
    
    g_signal_connect(treeview, "row-activated", G_CALLBACK(on_treeview1_row_activated), NULL);
    
    window_ge = lookup_widget(GTK_WIDGET(button), "ge");
    gtk_widget_hide(window_ge);
}

/* ========== CALLBACKS FENETRE AJOUTER ========== */

void on_abbuttonenrigister_clicked(GtkButton *objet, gpointer user_data)
{
    entraineur e;
    GtkWidget *window;
    gchar *old_id = NULL;
    gboolean is_modification = FALSE;
    
    window = lookup_widget(GTK_WIDGET(objet), "Ajouter");
    if (!window) {
        window = lookup_widget(GTK_WIDGET(objet), "modifier");
        is_modification = TRUE;
        old_id = (gchar *)g_object_get_data(G_OBJECT(window), "id_to_modify");
    }
    
    GtkWidget *nom_entry = lookup_widget(window, "abentrynom");
    GtkWidget *prenom_entry = lookup_widget(window, "abentryprenom");
    GtkWidget *id_entry = lookup_widget(window, "abentryid");
    GtkWidget *specialite_combo = lookup_widget(window, "abcomboboxentrysp__cialit__");
    GtkWidget *telephone_entry = lookup_widget(window, "abentrytelephone");
    GtkWidget *experience_spin = lookup_widget(window, "abspinbuttonexperience");
    GtkWidget *jour_spin = lookup_widget(window, "abspinbuttonjours");
    GtkWidget *mois_spin = lookup_widget(window, "abspinbuttonmois");
    GtkWidget *annee_spin = lookup_widget(window, "abspinbuttonannees");
    GtkWidget *male_radio = lookup_widget(window, "abradiobuttonmale");
    GtkWidget *email_entry = lookup_widget(window, "abentryemail");
    GtkWidget *adresse_entry = lookup_widget(window, "abentryadresse");
    
    // Pour modifier
    if (!nom_entry) {
        nom_entry = lookup_widget(window, "abmodentrynom");
        prenom_entry = lookup_widget(window, "abmodentryprenom");
        id_entry = lookup_widget(window, "abmodentryid");
        specialite_combo = lookup_widget(window, "abmodcomboboxentryspecialite");
        telephone_entry = lookup_widget(window, "abmodentrytelephone");
        experience_spin = lookup_widget(window, "abmodspinbuttonnbr");
        jour_spin = lookup_widget(window, "abmodspinbuttonjour");
        mois_spin = lookup_widget(window, "abmodspinbuttonmois");
        annee_spin = lookup_widget(window, "abmodspinbuttonannee");
        male_radio = lookup_widget(window, "abmodradiobuttonmale");
        email_entry = lookup_widget(window, "abmodentryemail");
        adresse_entry = lookup_widget(window, "abmodentryadresse");
    }
    
    strcpy(e.nom, gtk_entry_get_text(GTK_ENTRY(nom_entry)));
    strcpy(e.prenom, gtk_entry_get_text(GTK_ENTRY(prenom_entry)));
    strcpy(e.id, gtk_entry_get_text(GTK_ENTRY(id_entry)));
    strcpy(e.telephone, gtk_entry_get_text(GTK_ENTRY(telephone_entry)));
    strcpy(e.email, gtk_entry_get_text(GTK_ENTRY(email_entry)));
    strcpy(e.adresse, gtk_entry_get_text(GTK_ENTRY(adresse_entry)));
    
    gchar *specialite_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(specialite_combo));
    if (specialite_text != NULL) {
        strcpy(e.specialite, specialite_text);
        g_free(specialite_text);
    } else {
        strcpy(e.specialite, "");
    }
    
    e.experience = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(experience_spin));
    e.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour_spin));
    e.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_spin));
    e.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_spin));
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(male_radio))) {
        strcpy(e.sexe, "Male");
    } else {
        strcpy(e.sexe, "Female");
    }
    
    // Appeler la bonne fonction selon le mode
    if (is_modification && old_id) {
        modifier_entraineur(old_id, e);
        
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Entraineur modifie avec succes!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        // Vider les champs après modification
        gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
        gtk_entry_set_text(GTK_ENTRY(prenom_entry), "");
        gtk_entry_set_text(GTK_ENTRY(id_entry), "");
        gtk_entry_set_text(GTK_ENTRY(telephone_entry), "");
        gtk_entry_set_text(GTK_ENTRY(email_entry), "");
        gtk_entry_set_text(GTK_ENTRY(adresse_entry), "");
    } else {
        // Ajouter un nouvel entraîneur
        int resultat = ajouter_entraineur(e);
        
        if (resultat == 1) {
            // Succès
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Entraineur enregistre avec succes!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            
            // Vider les champs
            gtk_entry_set_text(GTK_ENTRY(nom_entry), "");
            gtk_entry_set_text(GTK_ENTRY(prenom_entry), "");
            gtk_entry_set_text(GTK_ENTRY(id_entry), "");
            gtk_entry_set_text(GTK_ENTRY(telephone_entry), "");
            gtk_entry_set_text(GTK_ENTRY(email_entry), "");
            gtk_entry_set_text(GTK_ENTRY(adresse_entry), "");
        } else {
            // Échec - ID existe déjà
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Erreur: Un entraineur avec l'ID '%s' existe deja!", e.id);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return; // Ne pas vider les champs pour permettre la correction
        }
    }
}

void on_abbuttonretour_clicked(GtkButton *objet, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(objet));
    GtkWidget *window_ge;
    
    gtk_widget_destroy(window_current);
    
    window_ge = create_ge();
    gtk_widget_show(window_ge);
}

/* ========== CALLBACKS FENETRE AFFICHER ========== */

void on_abtreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                                 GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeIter iter;
    gchar *id, *nom, *prenom, *specialite, *telephone, *email, *adresse, *sexe;
    gint experience;
    GtkTreeModel *model;
    
    model = gtk_tree_view_get_model(treeview);
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter,
                          0, &nom,
                          1, &prenom,
                          2, &id,
                          3, &specialite,
                          4, &telephone,
                          5, &experience,
                          7, &sexe,
                          8, &email,
                          9, &adresse,
                          -1);
        
        GtkWidget *window_supoumod = create_supoumod();
        gtk_widget_show(window_supoumod);
        
        // Stocker toutes les données de l'entraîneur
        g_object_set_data_full(G_OBJECT(window_supoumod), "id", g_strdup(id), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "nom", g_strdup(nom), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "prenom", g_strdup(prenom), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "specialite", g_strdup(specialite), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "telephone", g_strdup(telephone), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "email", g_strdup(email), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "adresse", g_strdup(adresse), g_free);
        g_object_set_data_full(G_OBJECT(window_supoumod), "sexe", g_strdup(sexe), g_free);
        g_object_set_data(G_OBJECT(window_supoumod), "experience", GINT_TO_POINTER(experience));
        g_object_set_data(G_OBJECT(window_supoumod), "treeview", treeview);
        
        g_free(id);
        g_free(nom);
        g_free(prenom);
        g_free(specialite);
        g_free(telephone);
        g_free(email);
        g_free(adresse);
        g_free(sexe);
    }
}

void on_abbuttonactualiser_clicked(GtkButton *objet, gpointer user_data)
{
    GtkWidget *window_afficher;
    GtkWidget *treeview1;
    
    window_afficher = lookup_widget(GTK_WIDGET(objet), "Afficher");
    treeview1 = lookup_widget(window_afficher, "abtreeview1");
    
    vider(treeview1);
    afficher_entraineur(treeview1);
}

void on_abbuttonrechercher_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_afficher;
    GtkWidget *treeview1;
    GtkWidget *entry_id;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkListStore *store;
    const gchar *id_recherche;
    gchar *id_courant;
    entraineur e;
    gboolean trouve = FALSE;
    
    // Récupérer les widgets
    window_afficher = lookup_widget(GTK_WIDGET(button), "Afficher");
    treeview1 = lookup_widget(window_afficher, "treeview1");
    entry_id = lookup_widget(window_afficher, "abcherentryid");
    
    // Récupérer l'ID à rechercher
    id_recherche = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    // Vérifier que l'ID n'est pas vide
    if (strlen(id_recherche) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window_afficher),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_WARNING,
                                                   GTK_BUTTONS_OK,
                                                   "Veuillez entrer un ID!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Chercher l'entraîneur dans le fichier
    if (chercher_entraineur((char *)id_recherche, &e)) {
        trouve = TRUE;
        
        model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1));
        
        if (model == NULL) {
            // Si le modèle n'existe pas, afficher d'abord
            afficher_entraineur(treeview1);
            model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1));
        }
        
        store = GTK_LIST_STORE(model);
        
        // Chercher et supprimer l'ancienne position dans le TreeView
        if (gtk_tree_model_get_iter_first(model, &iter)) {
            do {
                gtk_tree_model_get(model, &iter, 2, &id_courant, -1);
                
                if (strcmp(id_courant, id_recherche) == 0) {
                    gtk_list_store_remove(store, &iter);
                    g_free(id_courant);
                    break;
                }
                
                g_free(id_courant);
                
            } while (gtk_tree_model_iter_next(model, &iter));
        }
        
        // Insérer l'entraîneur au début du TreeView
        GtkTreeIter new_iter;
        gchar date[20];
        sprintf(date, "%d/%d/%d", e.jour, e.mois, e.annee);
        
        gtk_list_store_prepend(store, &new_iter);
        gtk_list_store_set(store, &new_iter,
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
        
        // Sélectionner la première ligne
        GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));
        gtk_tree_selection_select_iter(selection, &new_iter);
        
        // Faire défiler pour voir la ligne sélectionnée
        GtkTreePath *path = gtk_tree_model_get_path(model, &new_iter);
        gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(treeview1), path, NULL, TRUE, 0.0, 0.0);
        gtk_tree_path_free(path);
        
        // Message de confirmation
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window_afficher),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Entraineur trouve: %s %s", e.nom, e.prenom);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    
    if (!trouve) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window_afficher),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_WARNING,
                                                   GTK_BUTTONS_OK,
                                                   "Aucun entraineur trouve avec l'ID: %s", id_recherche);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

/* ========== CALLBACKS FENETRE SUPOUMOD ========== */

void on_supprimer_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_supoumod = lookup_widget(GTK_WIDGET(button), "supoumod");
    
    gchar *id = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "id");
    GtkWidget *treeview = (GtkWidget *)g_object_get_data(G_OBJECT(window_supoumod), "treeview");
    
    GtkWidget *window_cdf = create_cdf();
    gtk_widget_show(window_cdf);
    
    GtkWidget *oui = lookup_widget(window_cdf, "oui");
    GtkWidget *non = lookup_widget(window_cdf, "non");
    
    g_object_set_data_full(G_OBJECT(oui), "id_to_delete", g_strdup(id), g_free);
    g_object_set_data(G_OBJECT(oui), "treeview", treeview);
    g_object_set_data(G_OBJECT(oui), "supoumod_window", window_supoumod);
    
    g_signal_connect(oui, "clicked", G_CALLBACK(on_oui_clicked), NULL);
    g_signal_connect(non, "clicked", G_CALLBACK(on_non_clicked), NULL);
}

void on_modifier_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_supoumod = lookup_widget(GTK_WIDGET(button), "supoumod");
    
    gchar *id = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "id");
    gchar *nom = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "nom");
    gchar *prenom = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "prenom");
    gchar *specialite = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "specialite");
    gchar *telephone = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "telephone");
    gchar *email = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "email");
    gchar *adresse = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "adresse");
    gchar *sexe = (gchar *)g_object_get_data(G_OBJECT(window_supoumod), "sexe");
    gint experience = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(window_supoumod), "experience"));
    
    GtkWidget *window_modifier = create_modifier();
    gtk_widget_show(window_modifier);
    
    // Remplir les champs avec les données existantes
    GtkWidget *nom_entry = lookup_widget(window_modifier, "abmodentrynom");
    GtkWidget *prenom_entry = lookup_widget(window_modifier, "abmodentryprenom");
    GtkWidget *id_entry = lookup_widget(window_modifier, "abmodentryid");
    GtkWidget *telephone_entry = lookup_widget(window_modifier, "abmodentrytelephone");
    GtkWidget *email_entry = lookup_widget(window_modifier, "abmodentryemail");
    GtkWidget *adresse_entry = lookup_widget(window_modifier, "abmodentryadresse");
    GtkWidget *experience_spin = lookup_widget(window_modifier, "abmodspinbuttonnbr");
    GtkWidget *male_radio = lookup_widget(window_modifier, "abmodradiobuttonmale");
    GtkWidget *female_radio = lookup_widget(window_modifier, "abmodradiobuttonfemale");
    
    gtk_entry_set_text(GTK_ENTRY(nom_entry), nom);
    gtk_entry_set_text(GTK_ENTRY(prenom_entry), prenom);
    gtk_entry_set_text(GTK_ENTRY(id_entry), id);
    gtk_entry_set_text(GTK_ENTRY(telephone_entry), telephone);
    gtk_entry_set_text(GTK_ENTRY(email_entry), email);
    gtk_entry_set_text(GTK_ENTRY(adresse_entry), adresse);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(experience_spin), experience);
    
    if (strcmp(sexe, "Male") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(male_radio), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(female_radio), TRUE);
    }
    
    // Stocker l'ID original pour la modification
    g_object_set_data_full(G_OBJECT(window_modifier), "id_to_modify", g_strdup(id), g_free);
    
    gtk_widget_destroy(window_supoumod);
}

/* ========== CALLBACKS FENETRE CDF (CONFIRMATION) ========== */

void on_oui_clicked(GtkButton *button, gpointer user_data)
{
    gchar *id = (gchar *)g_object_get_data(G_OBJECT(button), "id_to_delete");
    GtkWidget *treeview = (GtkWidget *)g_object_get_data(G_OBJECT(button), "treeview");
    GtkWidget *supoumod_window = (GtkWidget *)g_object_get_data(G_OBJECT(button), "supoumod_window");
    
    supprimer_entraineur(id);
    
    afficher_entraineur(treeview);
    
    GtkWidget *window_cdf = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window_cdf);
    
    if (supoumod_window) {
        gtk_widget_destroy(supoumod_window);
    }
}

void on_non_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_cdf = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window_cdf);
}



/* =========================================================
 * UTILITAIRES
 * ========================================================= */
void afficher_message(GtkWindow *parent, const gchar *message, GtkMessageType type) {
    GtkWidget *dialog = gtk_message_dialog_new(parent,
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               type, GTK_BUTTONS_OK, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void sanitize_id(const char *src, char *dst, size_t dstsz) {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0' && j + 1 < dstsz; ++i) {
        char c = src[i];
        if (isalnum((unsigned char)c) || c == '_') dst[j++] = c;
        else dst[j++] = '_';
    }
    dst[j] = '\0';
    size_t w = 0;
    for (size_t r = 0; dst[r] != '\0'; ++r) {
        if (dst[r] == '_' && w > 0 && dst[w-1] == '_') continue;
        dst[w++] = dst[r];
    }
    dst[w] = '\0';
}

static GtkWidget *find_widget(GtkWidget *root, const char *glade_id) {
    if (!root || !glade_id) return NULL;
    GtkWidget *w = lookup_widget(root, glade_id);
    if (w) return w;
    char alt[256];
    sanitize_id(glade_id, alt, sizeof alt);
    w = lookup_widget(root, alt);
    return w;
}


static gboolean valider_tel(const gchar *tel) {
    if (!tel || !*tel) return FALSE;
    regex_t regex;
    regcomp(&regex, "^[0-9]{8,15}$", REG_EXTENDED);
    int ok = regexec(&regex, tel, 0, NULL, 0);
    regfree(&regex);
    return ok == 0;
}

/* Navigation */
void cacher_toutes_fenetres(void) {
    if (gestion_membres_window) gtk_widget_hide(gestion_membres_window);
    if (ajouter_window)         gtk_widget_hide(ajouter_window);
    if (supprimer_window)       gtk_widget_hide(supprimer_window);
    if (rechercher_window)      gtk_widget_hide(rechercher_window);
    if (modifier_window)        gtk_widget_hide(modifier_window);
    if (trier_window)           gtk_widget_hide(trier_window);
    if (filtrer_window)         gtk_widget_hide(filtrer_window);
    if (statistique_window)     gtk_widget_hide(statistique_window);
}

void afficher_fenetre(const gchar *nom_f) {
    cacher_toutes_fenetres();
    if (!nom_f) return;
    if (g_strcmp0(nom_f, "gestion_membres") == 0 && gestion_membres_window) gtk_widget_show(gestion_membres_window);
    else if (g_strcmp0(nom_f, "ajouter")    == 0 && ajouter_window)         gtk_widget_show(ajouter_window);
    else if (g_strcmp0(nom_f, "supprimer")  == 0 && supprimer_window)       gtk_widget_show(supprimer_window);
    else if (g_strcmp0(nom_f, "rechercher") == 0 && rechercher_window)      gtk_widget_show(rechercher_window);
    else if (g_strcmp0(nom_f, "modifier")   == 0 && modifier_window)        gtk_widget_show(modifier_window);
    else if (g_strcmp0(nom_f, "trier")      == 0 && trier_window)           gtk_widget_show(trier_window);
    else if (g_strcmp0(nom_f, "filtrer")    == 0 && filtrer_window)         gtk_widget_show(filtrer_window);
    else if (g_strcmp0(nom_f, "statistique")== 0 && statistique_window)     gtk_widget_show(statistique_window);
}

void initialiser_donnees(void) {
    charger_membres_depuis_fichier();
}

/* =========================================================
 * CHARGER DANS LE FORMULAIRE DE MODIFICATION
 * ========================================================= */
void charger_membre_dans_formulaire_modification(const gchar *id) {
    if (!modifier_window || !id || !*id) return;

    Membre *m = rechercher_membre((char*)id);
    if (!m) {
        afficher_message(GTK_WINDOW(modifier_window), "Membre non trouvé", GTK_MESSAGE_WARNING);
        return;
    }

    GtkWidget *entry_nom    = find_widget(modifier_window, "emna_entry_nom_modif");
    GtkWidget *entry_prenom = find_widget(modifier_window, "emna.entry16.pre");
    GtkWidget *spin_age     = find_widget(modifier_window, "emna.spinbutton1.32.age");
    GtkWidget *entry_tel    = find_widget(modifier_window, "emna.entry14.tel");
    GtkWidget *entry_mail   = find_widget(modifier_window, "emna_entry_mail_modif");
    GtkWidget *combo_type   = find_widget(modifier_window, "combobox2");
    GtkWidget *radio_homme  = find_widget(modifier_window, "radio_homme_modif");
    GtkWidget *radio_femme  = find_widget(modifier_window, "radio_femme_modif");

    if (entry_nom)    gtk_entry_set_text(GTK_ENTRY(entry_nom), m->nom);
    if (entry_prenom) gtk_entry_set_text(GTK_ENTRY(entry_prenom), m->prenom);
    if (spin_age)     gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_age), m->age);
    if (entry_tel)    gtk_entry_set_text(GTK_ENTRY(entry_tel), m->telephone);
    if (entry_mail)   gtk_entry_set_text(GTK_ENTRY(entry_mail), m->email);

    if (radio_homme && radio_femme) {
        gboolean is_h = g_strcmp0(m->sexe, "Homme") == 0;
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_homme), is_h);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio_femme), !is_h);
    }

    if (combo_type) {
        if (g_strcmp0(m->type_abonnement, "Mensuel") == 0)         gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 0);
        else if (g_strcmp0(m->type_abonnement, "Semestriel") == 0) gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 1);
        else                                                       gtk_combo_box_set_active(GTK_COMBO_BOX(combo_type), 2);
    }

    afficher_message(GTK_WINDOW(modifier_window), "Données chargées avec succès !", GTK_MESSAGE_INFO);
}

/* =========================================================
 * CALLBACKS – Fenêtre principale
 * ========================================================= */
void on_emna_button_ajou2_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_ajouter;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre d'ajout
    window_ajouter = create_emna_ajouter_un_membre();
    gtk_widget_show(window_ajouter);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}
void on_emna_button_supp1_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_supprimer;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de suppression
    window_supprimer = create_emna_supprimer_un_membre();
    gtk_widget_show(window_supprimer);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}

void on_emna_button_rech2_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_rechercher;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de recherche
    window_rechercher = create_emna_rechercher_un_membre();
    gtk_widget_show(window_rechercher);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}
void on_emna_button_filtre2_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_filtrer;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de filtre
    window_filtrer = create_emna_filtrer_par_sexe();
    gtk_widget_show(window_filtrer);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}

void on_emna_button_tri2_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_trier;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de tri
    window_trier = create_emna_trier_par_age();
    gtk_widget_show(window_trier);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}

void on_emna_button_retour_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(b));
    GtkWidget *window_admin;
    
    gtk_widget_destroy(window_current);
    
    // Retourner à l'espace admin
    window_admin = create_Espace_Admin();
    gtk_widget_show(window_admin);
}

void on_emna_button_modif1_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_modifier;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de modification
    window_modifier = create_emna_modifier_un_membre();
    gtk_widget_show(window_modifier);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}

void on_emna_button_statistique_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_stat;
    GtkWidget *window_gestion;
    
    window_gestion = lookup_widget(GTK_WIDGET(b), "emna_gestion_des_membres");
    
    // Créer et afficher la fenêtre de statistiques
    window_stat = create_statistique();
    gtk_widget_show(window_stat);
    
    // Optionnel : cacher la fenêtre de gestion
    // gtk_widget_hide(window_gestion);
}

/* =========================================================
 * AJOUTER
 * ========================================================= */
void on_emna_button_entre2_clicked(GtkButton *button, gpointer user_data)
{
    Membre m;
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_ajouter_un_membre");
    
    // Récupérer les widgets avec les VRAIS noms (underscores)
    GtkWidget *entry_id = lookup_widget(window, "emna_entry_id1");
    GtkWidget *entry_nom = lookup_widget(window, "emna_entry_nom1");
    GtkWidget *entry_prenom = lookup_widget(window, "emna_entry_pre1");
    GtkWidget *entry_tel = lookup_widget(window, "emna_entry_tel");
    GtkWidget *entry_email = lookup_widget(window, "emna_entry_email1");
    GtkWidget *spinbutton_age = lookup_widget(window, "emna_spinbutton_age1");
    GtkWidget *combobox = lookup_widget(window, "combobox1");
    GtkWidget *radio_homme = lookup_widget(window, "emna_radiobutton_homme");
    
    if (!entry_id || !entry_nom) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur: Widgets introuvables!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    // Récupérer les valeurs
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const gchar *nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const gchar *prenom = gtk_entry_get_text(GTK_ENTRY(entry_prenom));
    const gchar *telephone = gtk_entry_get_text(GTK_ENTRY(entry_tel));
    const gchar *email = gtk_entry_get_text(GTK_ENTRY(entry_email));
    int age = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_age));
    
    // Récupérer l'abonnement
    gchar *type_abo = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox));
    
    // Copier dans la structure Membre
    strcpy(m.id, id);
    strcpy(m.nom, nom);
    strcpy(m.prenom, prenom);
    strcpy(m.telephone, telephone);
    strcpy(m.email, email);
    m.age = age;
    
    // sexe est un tableau de char
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_homme))) {
        strcpy(m.sexe, "Homme");
    } else {
        strcpy(m.sexe, "Femme");
    }
    
    // type_abonnement
    if(type_abo) {
        strcpy(m.type_abonnement, type_abo);
        g_free(type_abo);
    }
    
    // Ajouter le membre
    ajouter_membre(&m);
    
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Membre ajouté avec succès!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    // Vider les champs
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_prenom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");
}



/* =========================================================
 * DIALOG AJOUT AUTRE MEMBRE
 * ========================================================= */
void on_cancelbutton_emna_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_dialog_response(GTK_DIALOG(dialog), GTK_RESPONSE_CANCEL);
    afficher_fenetre("gestion_membres");
}

void on_okbutton1_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_dialog_response(GTK_DIALOG(dialog), GTK_RESPONSE_OK);
    
    GtkWidget *entry_id    = find_widget(ajouter_window, "emna.entry.id1");
    GtkWidget *entry_nom   = find_widget(ajouter_window, "emna.entry.nom1");
    GtkWidget *entry_prenom= find_widget(ajouter_window, "emna.entry.pre1");
    GtkWidget *entry_tel   = find_widget(ajouter_window, "emna.entry.tel");
    GtkWidget *entry_mail  = find_widget(ajouter_window, "emna.entry.email1");
    GtkWidget *spin_age    = find_widget(ajouter_window, "emna.spinbutton.age1");
    
    if (entry_id)    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    if (entry_nom)   gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    if (entry_prenom)gtk_entry_set_text(GTK_ENTRY(entry_prenom), "");
    if (entry_tel)   gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
    if (entry_mail)  gtk_entry_set_text(GTK_ENTRY(entry_mail), "");
    if (spin_age)    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin_age), 18);
    
    afficher_fenetre("ajouter");
}

/* =========================================================
 * SUPPRIMER
 * ========================================================= */
void on_emna_button_supp6_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id = find_widget(supprimer_window, "emna.entry.id3");
    if (!entry_id) {
        afficher_message(GTK_WINDOW(supprimer_window), "Erreur: champ ID non trouvé", GTK_MESSAGE_ERROR);
        return;
    }
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    if (strlen(id) == 0) {
        afficher_message(GTK_WINDOW(supprimer_window), "Veuillez entrer un ID", GTK_MESSAGE_WARNING);
        return;
    }
    if (!rechercher_membre((char*)id)) {
        afficher_message(GTK_WINDOW(supprimer_window), "Membre non trouvé !", GTK_MESSAGE_WARNING);
        return;
    }
    supprimer_membre((char*)id);
    afficher_message(GTK_WINDOW(supprimer_window), "Membre supprimé avec succès !", GTK_MESSAGE_INFO);
}

void on_emna_button_retour5_clicked(GtkButton *button, gpointer user_data) { 
    afficher_fenetre("gestion_membres"); 
}

/* =========================================================
 * RECHERCHER
 * ========================================================= */
void on_emna_button24_rech_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_rechercher_un_membre");
    GtkWidget *entry_id = lookup_widget(window, "emna_entry10_idd_rech");
    GtkWidget *treeview = lookup_widget(window, "emtreeview1");
    
    if (!treeview) {
        g_print("TreeView introuvable!\n");
        return;
    }
    
    // Initialiser le treeview
    initialiser_treeview_membres(GTK_TREE_VIEW(treeview));
    
    // Charger tous les membres
    charger_membres_depuis_fichier();
    
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    
    if (strlen(id) > 0) {
        // Rechercher un membre spécifique
        Membre *m = rechercher_membre((char*)id);
        if (m) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Membre trouvé: %s %s", m->nom, m->prenom);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Membre non trouvé!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
    
    // TOUJOURS afficher tous les membres dans le treeview
    afficher_membres_dans_treeview(GTK_TREE_VIEW(treeview));
}

void on_emna_button_actualiser_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_rechercher_un_membre");
    GtkWidget *treeview = lookup_widget(window, "emtreeview1");
    
    // Recharger depuis le fichier et afficher
    charger_membres_depuis_fichier();
    afficher_membres_dans_treeview(GTK_TREE_VIEW(treeview));
}
void on_emna_button25_expoo_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_rechercher_un_membre");
    GtkWidget *treeview = lookup_widget(window, "emtreeview1");
    
    if (treeview) {
        exporter_membres_csv("membres_recherche.csv", GTK_TREE_VIEW(treeview));
        
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Exportation réussie : membres_recherche.csv");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

// Retour depuis rechercher
void on_emna_button26_ret_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_gestion;
    
    gtk_widget_destroy(window_current);
    
    window_gestion = create_emna_gestion_des_membres();
    gtk_widget_show(window_gestion);
}

// Retour depuis modifier (bouton annuler)
void on_emna_button40_annu_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_gestion;
    
    gtk_widget_destroy(window_current);
    
    window_gestion = create_emna_gestion_des_membres();
    gtk_widget_show(window_gestion);
}

// Retour depuis ajouter (bouton annuler)
void on_button_annu2_clicked(GtkButton *b, gpointer d)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(b));
    GtkWidget *window_gestion;
    
    gtk_widget_destroy(window_current);
    
    window_gestion = create_emna_gestion_des_membres();
    gtk_widget_show(window_gestion);
}

void on_emtreeview1_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d) { 
    /* optionnel */ 
}

/* Fonction d'actualisation pour la fenêtre Rechercher */


/* =========================================================
 * MODIFIER
 * ========================================================= */
void on_emna_entry_iddiii_activate(GtkEntry *entry, gpointer user_data) {
    const gchar *id = gtk_entry_get_text(entry);
    if (strlen(id) > 0) charger_membre_dans_formulaire_modification(id);
    else afficher_message(GTK_WINDOW(modifier_window), "Veuillez entrer un ID", GTK_MESSAGE_WARNING);
}



void on_emna_on41_mod_clicked(GtkButton *button, gpointer user_data)
{
    Membre m;
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_modifier_un_membre");
    
    GtkWidget *entry_id = lookup_widget(window, "emna_entry_iddiii");
    GtkWidget *entry_nom = lookup_widget(window, "emna_entry_nom_modif");
    GtkWidget *entry_prenom = lookup_widget(window, "emna_entry16_pre");
    GtkWidget *entry_tel = lookup_widget(window, "emna_entry14_tel");
    GtkWidget *entry_email = lookup_widget(window, "emna_entry_mail_modif");
    GtkWidget *spinbutton_age = lookup_widget(window, "emna_spinbutton1_32_age");
    GtkWidget *combobox = lookup_widget(window, "combobox2");
    GtkWidget *radio_homme = lookup_widget(window, "radio_homme_modif");
    
    if (!entry_id || !entry_nom) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur: Widgets introuvables!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    const gchar *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const gchar *nom = gtk_entry_get_text(GTK_ENTRY(entry_nom));
    const gchar *prenom = gtk_entry_get_text(GTK_ENTRY(entry_prenom));
    const gchar *telephone = gtk_entry_get_text(GTK_ENTRY(entry_tel));
    const gchar *email = gtk_entry_get_text(GTK_ENTRY(entry_email));
    int age = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton_age));
    
    gchar *type_abo = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox));
    
    strcpy(m.id, id);
    strcpy(m.nom, nom);
    strcpy(m.prenom, prenom);
    strcpy(m.telephone, telephone);
    strcpy(m.email, email);
    m.age = age;
    
    if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radio_homme))) {
        strcpy(m.sexe, "Homme");
    } else {
        strcpy(m.sexe, "Femme");
    }
    
    if(type_abo) {
        strcpy(m.type_abonnement, type_abo);
        g_free(type_abo);
    }
    
    // CORRECT: passer l'ID et le pointeur
    char id_buffer[50];
    strcpy(id_buffer, id);
    modifier_membre(id_buffer, &m);
    
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Membre modifié avec succès!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
/* =========================================================
 * TRIER
 * ========================================================= */


void on_emna_button44_trier44_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_trier_par_age");
    GtkWidget *treeview = lookup_widget(window, "emtreeview3");
    GtkWidget *check_croi = lookup_widget(window, "emna_checkbutton7_croi");
    GtkWidget *check_dec = lookup_widget(window, "emna_checkbutton8_dec");
    
    if (!treeview) {
        g_print("TreeView introuvable!\n");
        return;
    }
    
    // Initialiser le treeview
    initialiser_treeview_membres(GTK_TREE_VIEW(treeview));
    
    // Charger les données
    charger_membres_depuis_fichier();
    
    // Déterminer l'ordre (croissant ou décroissant)
    int ordre_croissant = 1; // par défaut croissant
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_croi))) {
        ordre_croissant = 1;
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_dec))) {
        ordre_croissant = 0;
    }
    
    // Trier
    trier_membres_par_age(GTK_TREE_VIEW(treeview), ordre_croissant);
}

void on_button45_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_gestion;
    
    gtk_widget_destroy(window_current);
    
    window_gestion = create_emna_gestion_des_membres();
    gtk_widget_show(window_gestion);
}

void on_treeview3_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d) { 
    /* optionnel */ 
}

void on_emna_button464_expo_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "emna_trier_par_age");
    GtkWidget *treeview = lookup_widget(window, "emtreeview3");
    
    if (treeview) {
        exporter_membres_csv("membres_tries.csv", GTK_TREE_VIEW(treeview));
        
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Exportation réussie : membres_tries.csv");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_emna_button_actualiser_tri_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview_w = find_widget(trier_window, "treeview3");
    if (treeview_w) {
        afficher_membres_dans_treeview(GTK_TREE_VIEW(treeview_w));
        afficher_message(GTK_WINDOW(trier_window), "Liste actualisée !", GTK_MESSAGE_INFO);
    }
}

/* =========================================================
 * FILTRER
 * ========================================================= */
void on_emna_button_rouuu_clicked(GtkButton *button, gpointer user_data) { 
    afficher_fenetre("gestion_membres"); 
}

void on_emna_button_fil2_clicked(GtkButton *button, gpointer user_data)
{
    // Essayer de trouver depuis le bouton directement
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "emtreeview4");
    GtkWidget *combobox = lookup_widget(GTK_WIDGET(button), "combobox3");
    
    if (!treeview) {
        g_print("ERREUR: TreeView 'emtreeview4' introuvable!\n");
        
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur: TreeView introuvable!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    if (!combobox) {
        g_print("ERREUR: ComboBox 'combobox3' introuvable!\n");
        return;
    }
    
    g_print("TreeView et ComboBox trouvés!\n");
    
    // Initialiser le treeview
    initialiser_treeview_membres(GTK_TREE_VIEW(treeview));
    
    // Charger les données
    charger_membres_depuis_fichier();
    
    // Obtenir le sexe sélectionné dans le combobox
    gchar *sexe = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox));
    
    if (sexe && strlen(sexe) > 0) {
        g_print("Filtrage par sexe: %s\n", sexe);
        filtrer_membres_par_sexe(GTK_TREE_VIEW(treeview), sexe);
        g_free(sexe);
    } else {
        g_print("Aucun sexe sélectionné, affichage de tous les membres\n");
        afficher_membres_dans_treeview(GTK_TREE_VIEW(treeview));
    }
}

void on_treeview4_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d) { 
    /* optionnel */ 
}

void on_emna_button_xxxx_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview_w = find_widget(filtrer_window, "treeview4");
    if (treeview_w) {
        exporter_membres_csv("resultats_filtre.csv", GTK_TREE_VIEW(treeview_w));
        afficher_message(GTK_WINDOW(filtrer_window), "Export: resultats_filtre.csv", GTK_MESSAGE_INFO);
    }
}

void on_emna_button_actualiser_filtre_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview_w = find_widget(filtrer_window, "treeview4");
    if (treeview_w) {
        afficher_membres_dans_treeview(GTK_TREE_VIEW(treeview_w));
        afficher_message(GTK_WINDOW(filtrer_window), "Liste actualisée !", GTK_MESSAGE_INFO);
    }
}

/* =========================================================
 * STATISTIQUE
 * ========================================================= */
void on_emna_button_ret_statis_clicked(GtkButton *button, gpointer user_data) {
    afficher_fenetre("gestion_membres");
}



/* ========== HELPER FUNCTIONS FOR DIALOGS ========== */
void show_error_dialog(GtkWidget *parent, const char *message)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(parent)),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_ERROR,
        GTK_BUTTONS_OK,
        "%s", message);
    
    // Version non-bloquante
    g_signal_connect_swapped(dialog, "response",
                             G_CALLBACK(gtk_widget_destroy),
                             dialog);
    gtk_widget_show(dialog);
}

void show_success_dialog(GtkWidget *parent, const char *message)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(parent)),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "%s", message);
    
    // Version non-bloquante
    g_signal_connect_swapped(dialog, "response",
                             G_CALLBACK(gtk_widget_destroy),
                             dialog);
    gtk_widget_show(dialog);
}

// Callback pour le dialog de confirmation
static void confirmation_response_callback(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    int *result = (int *)user_data;
    *result = (response_id == GTK_RESPONSE_YES) ? 1 : 0;
    gtk_widget_destroy(GTK_WIDGET(dialog));
}

int show_confirmation_dialog(GtkWidget *parent, const char *message)
{
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(gtk_widget_get_toplevel(parent)),
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "%s", message);
    
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    
    return (response == GTK_RESPONSE_YES);
}


/* ========== CALLBACKS ESPACE ENTRAINEUR ========== */
void on_inscri1_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_cours;
    
    gtk_widget_destroy(window_current);
    
    window_cours = create_ent_courssportif();
    
    // Initialiser et afficher les cours
    GtkWidget *treeview = lookup_widget(window_cours, "treeviewcourssportif");
    if (treeview) {
        initialiser_treeview_cours(GTK_TREE_VIEW(treeview));
        afficher_tous_les_cours(GTK_TREE_VIEW(treeview));
    }
    
    gtk_widget_show(window_cours);
}

void on_reserver_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_equipment;
    
    gtk_widget_destroy(window_current);
    
    window_equipment = create_ent_equipment();
    
    // Initialiser et afficher les équipements
    GtkWidget *treeview = lookup_widget(window_equipment, "treeviewequipment");
    if (treeview) {
        initialiser_treeview_equipment(GTK_TREE_VIEW(treeview));
        afficher_tous_les_equipments_ent(GTK_TREE_VIEW(treeview));
    }
    
    gtk_widget_show(window_equipment);
}

void on_inscri2_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_centre;
    
    gtk_widget_destroy(window_current);
    
    window_centre = create_ent_centresportif();
    
    // Initialiser et afficher les centres
    GtkWidget *treeview = lookup_widget(window_centre, "treeviewcentre");
    if (treeview) {
        initialiser_treeview_centre(GTK_TREE_VIEW(treeview));
        afficher_tous_les_centres(GTK_TREE_VIEW(treeview));
    }
    
    gtk_widget_show(window_centre);
}

void on_im_retour_EE_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_auth;
    
    gtk_widget_destroy(window_current);
    
    window_auth = create_Athentification();
    gtk_widget_show(window_auth);
}

/* ========== CALLBACKS GESTION CENTRES ========== */
void on_im_ajouter_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *ajout_window = create_imen_bm_Ajouter();
    gtk_widget_show(ajout_window);
}

//void on_im_modifier_button_clicked(GtkButton *button, gpointer user_data)
//{
    //GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
   // gtk_widget_hide(current_window);
   
    //GtkWidget *modif_window = create_imen_bm_Modifier();
   // gtk_widget_show(modif_window);
//}

//void on_im_supprimer_button_clicked(GtkButton *button, gpointer user_data)
//{
    //GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    //gtk_widget_hide(current_window);
   
    //GtkWidget *supp_window = create_imen_bm_Suppmod();
    //gtk_widget_show(supp_window);
//}

void on_im_rechercher_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *rech_window = create_imen_bm_Rechercher();
    gtk_widget_show(rech_window);
}

void on_im_stat_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *stat_window = create_imen_bm_Statistiques_Filtrees();
    gtk_widget_show(stat_window);
}

void on_im_retour_gc_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *admin_window = create_Espace_Admin();
    gtk_widget_show(admin_window);
}

/* ========== CALLBACKS AJOUT ========== */
void on_im_ajout_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    ouvert_weekend = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_im_ajout_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    parking_disponible = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_im_ajout_radiobutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(type, "Prive");
}

void on_im_ajout_radiobutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(type, "Public");
}

void on_im_enrigistrer_button_clicked(GtkButton *button, gpointer user_data)
{
    Centre c;
    GtkWidget *input;
    
    printf("DEBUG: Début de l'enregistrement\n");  // Debug
    
    // ========== RÉCUPÉRATION ET VALIDATION ID ==========
    input = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry");
    if (!input) {
        printf("ERROR: Widget im_id_centre_entry not found\n");
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ID introuvable");
        return;
    }
    
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(input));
    if (!id_text || strlen(id_text) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : L'ID est obligatoire");
        return;
    }
    c.id = atoi(id_text);
    printf("DEBUG: ID = %d\n", c.id);
    
    // ========== RÉCUPÉRATION NOM ==========
    input = lookup_widget(GTK_WIDGET(button), "im_nom_entry");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ nom introuvable");
        return;
    }
    const char *nom = gtk_entry_get_text(GTK_ENTRY(input));
    if (!nom || strlen(nom) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Le nom est obligatoire");
        return;
    }
    strncpy(c.nom, nom, sizeof(c.nom) - 1);
    c.nom[sizeof(c.nom) - 1] = '\0';
    printf("DEBUG: Nom = %s\n", c.nom);
    
    // ========== RÉCUPÉRATION ADRESSE ==========
    input = lookup_widget(GTK_WIDGET(button), "im_adresse_entry");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ adresse introuvable");
        return;
    }
    const char *adresse = gtk_entry_get_text(GTK_ENTRY(input));
    if (!adresse || strlen(adresse) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : L'adresse est obligatoire");
        return;
    }
    strncpy(c.adresse, adresse, sizeof(c.adresse) - 1);
    c.adresse[sizeof(c.adresse) - 1] = '\0';
    printf("DEBUG: Adresse = %s\n", c.adresse);
    
    // ========== RÉCUPÉRATION VILLE ==========
    input = lookup_widget(GTK_WIDGET(button), "im_ville_combobox");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ville introuvable");
        return;
    }
    char *ville = gtk_combo_box_get_active_text(GTK_COMBO_BOX(input));
    if (!ville || strlen(ville) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : La ville est obligatoire");
        if (ville) g_free(ville);
        return;
    }
    strncpy(c.ville, ville, sizeof(c.ville) - 1);
    c.ville[sizeof(c.ville) - 1] = '\0';
    g_free(ville);
    printf("DEBUG: Ville = %s\n", c.ville);
    
    // ========== RÉCUPÉRATION TÉLÉPHONE ==========
    input = lookup_widget(GTK_WIDGET(button), "im_telephone_entry");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ téléphone introuvable");
        return;
    }
    const char *telephone = gtk_entry_get_text(GTK_ENTRY(input));
    if (!telephone || strlen(telephone) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Le téléphone est obligatoire");
        return;
    }
    strncpy(c.telephone, telephone, sizeof(c.telephone) - 1);
    c.telephone[sizeof(c.telephone) - 1] = '\0';
    printf("DEBUG: Téléphone = %s\n", c.telephone);
    
    // ========== RÉCUPÉRATION EMAIL ==========
    input = lookup_widget(GTK_WIDGET(button), "im_email_entry");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ email introuvable");
        return;
    }
    const char *email = gtk_entry_get_text(GTK_ENTRY(input));
    if (!email || strlen(email) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : L'email est obligatoire");
        return;
    }
    strncpy(c.email, email, sizeof(c.email) - 1);
    c.email[sizeof(c.email) - 1] = '\0';
    printf("DEBUG: Email = %s\n", c.email);
    
    // ========== RÉCUPÉRATION CAPACITÉ ==========
    input = lookup_widget(GTK_WIDGET(button), "im_capacit___spinbutton");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ capacité introuvable");
        return;
    }
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
    printf("DEBUG: Capacité = %d\n", c.capacite);
    
    // ========== AUTRES CHAMPS ==========
    c.ouvert_weekend = ouvert_weekend;
    c.parking_disponible = parking_disponible;
    c.type = (strcmp(type, "Prive") == 0) ? 0 : 1;
    
    printf("DEBUG: Weekend=%d, Parking=%d, Type=%d\n", 
           c.ouvert_weekend, c.parking_disponible, c.type);
    
    // ========== VALIDATION ==========
    if (!valider_telephone(c.telephone)) {
        show_error_dialog(GTK_WIDGET(button), 
                         "Erreur : Le téléphone doit contenir 8 chiffres");
        return;
    }
    
    if (!valider_email(c.email)) {
        show_error_dialog(GTK_WIDGET(button), 
                         "Erreur : L'email doit contenir @ et .");
        return;
    }
    
    // ========== AJOUT ==========
    printf("DEBUG: Tentative d'ajout...\n");
    
    // IMPORTANT: Forcer le flush des printf avant l'ajout
    fflush(stdout);
    
    int resultat = ajouter_centre(c);
    
    printf("DEBUG: Résultat ajout = %d\n", resultat);
    fflush(stdout);
    
    if (resultat) {
        printf("DEBUG: Succès - Affichage du dialog\n");
        fflush(stdout);
        
        show_success_dialog(GTK_WIDGET(button), "Centre ajouté avec succès !");
        
        // Vider les champs après succès
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(button), "im_id_centre_entry")), "");
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(button), "im_nom_entry")), "");
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(button), "im_adresse_entry")), "");
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(button), "im_telephone_entry")), "");
        gtk_entry_set_text(GTK_ENTRY(lookup_widget(GTK_WIDGET(button), "im_email_entry")), "");
        
        printf("DEBUG: Fin de l'enregistrement avec succès\n");
    } else {
        printf("DEBUG: Échec - Affichage du dialog d'erreur\n");
        fflush(stdout);
        
        show_error_dialog(GTK_WIDGET(button), 
                         "Erreur : ID déjà existant ou problème d'écriture");
    }
    
    fflush(stdout);
}

void on_im_annuler_ajout_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(current_window);
}

void on_im_retour_ajout_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

/* ========== CALLBACKS MODIFIER ========== */
void on_im_rechercher_modif_button_clicked(GtkButton *button, gpointer user_data)
{
    int id;
    Centre c;
    GtkWidget *input = lookup_widget(GTK_WIDGET(button), "im_id_modif");
   
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ID introuvable");
        return;
    }
   
    id = atoi(gtk_entry_get_text(GTK_ENTRY(input)));
   
    if (chercher_centre(id, &c)) {
        GtkWidget *output;
       
        output = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
        if (output) gtk_entry_set_text(GTK_ENTRY(output), c.nom);
       
        output = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
        if (output) gtk_entry_set_text(GTK_ENTRY(output), c.adresse);
       
        output = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_modif");
        if (output) {
            // Set combo box text
            gtk_entry_set_text(GTK_ENTRY(GTK_BIN(output)->child), c.ville);
        }
       
        output = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
        if (output) gtk_entry_set_text(GTK_ENTRY(output), c.telephone);
       
        output = lookup_widget(GTK_WIDGET(button), "im_email_modif");
        if (output) gtk_entry_set_text(GTK_ENTRY(output), c.email);
       
        output = lookup_widget(GTK_WIDGET(button), "im_capacite_modif");
        if (output) gtk_spin_button_set_value(GTK_SPIN_BUTTON(output), c.capacite);
       
        GtkWidget *check1 = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton1");
        if (check1) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check1), c.ouvert_weekend);
       
        GtkWidget *check2 = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton2");
        if (check2) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check2), c.parking_disponible);
       
        GtkWidget *radio1 = lookup_widget(GTK_WIDGET(button), "im_modif_radiobutton1");
        GtkWidget *radio2 = lookup_widget(GTK_WIDGET(button), "im_modif_radiobutton2");
        if (c.type == 0 && radio1) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio1), TRUE);
            strcpy(type, "Prive");
        } else if (radio2) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio2), TRUE);
            strcpy(type, "Public");
        }
       
        ouvert_weekend = c.ouvert_weekend;
        parking_disponible = c.parking_disponible;
       
    } else {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Centre non trouvé");
    }
}

void on_im_modif_checkbutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data)
{
    ouvert_weekend = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_im_modif_checkbutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data)
{
    parking_disponible = gtk_toggle_button_get_active(togglebutton) ? 1 : 0;
}

void on_im_modif_radiobutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(type, "Prive");
}

void on_im_modif_radiobutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data)
{
    if (gtk_toggle_button_get_active(togglebutton))
        strcpy(type, "Public");
}

void on_im_mettreajour_button_clicked(GtkButton *button, gpointer user_data)
{
    Centre c;
    GtkWidget *input;
   
    input = lookup_widget(GTK_WIDGET(button), "im_id_modif");
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champs introuvables");
        return;
    }
    c.id = atoi(gtk_entry_get_text(GTK_ENTRY(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
    strcpy(c.adresse, gtk_entry_get_text(GTK_ENTRY(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_modif");
    strcpy(c.ville, gtk_combo_box_get_active_text(GTK_COMBO_BOX(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
    strcpy(c.telephone, gtk_entry_get_text(GTK_ENTRY(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_email_modif");
    strcpy(c.email, gtk_entry_get_text(GTK_ENTRY(input)));
   
    input = lookup_widget(GTK_WIDGET(button), "im_capacite_modif");
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(input));
   
    c.ouvert_weekend = ouvert_weekend;
    c.parking_disponible = parking_disponible;
    c.type = (strcmp(type, "Prive") == 0) ? 0 : 1;
   
    if (!valider_email(c.email) || !valider_telephone(c.telephone)) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Email ou téléphone invalide");
        return;
    }
   
    modifier_centre(c);
    show_success_dialog(GTK_WIDGET(button), "Centre modifié avec succès");
}

void on_im_annuler_modif_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(current_window);
}

void on_im_retour_modif_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

/* ========== CALLBACKS SUPPRIMER ========== */
void on_im_suppmod_supp_button_clicked(GtkButton *button, gpointer user_data)
{

    // Récupérer le champ ID dans la fenêtre de suppression
    GtkWidget *input = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry_supp");

    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ID introuvable");
        return;
    }

    const gchar *text = gtk_entry_get_text(GTK_ENTRY(input));
    if (text == NULL || strlen(text) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Veuillez entrer un ID");
        return;
    }

    int id = atoi(text);
    if (id <= 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : ID invalide");
        return;
    }

    // Confirmation avant suppression
    if (show_confirmation_dialog(GTK_WIDGET(button), "Confirmez-vous la suppression ?")) {
        supprimer_centre(id);
        show_success_dialog(GTK_WIDGET(button), "Centre supprimé avec succès");
    }


    // Get ID from the suppmod window - trying both possible entry names
  //  GtkWidget *input = lookup_widget(GTK_WIDGET(button), "im_id_modif");
   // if (!input) {
       // input = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry");
   // }
   
   // if (!input) {
       // show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ID introuvable");
       // return;
  // }
   
   // int id = atoi(gtk_entry_get_text(GTK_ENTRY(input)));
   
   // if (show_confirmation_dialog(GTK_WIDGET(button), "Confirmez-vous la suppression ?")) {
      //  supprimer_centre(id);
      //  show_success_dialog(GTK_WIDGET(button), "Centre supprimé avec succès");
   // }
}

void on_im_retour_supp_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

void on_im_suppmod_mod_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *modif_window = create_imen_bm_Modifier();
    gtk_widget_show(modif_window);
}

/* ========== CALLBACKS RECHERCHER ========== */
void on_im_rechercher_rech_button_clicked(GtkButton *button, gpointer user_data)
{
    int id;
    Centre c;
    GtkWidget *input = lookup_widget(GTK_WIDGET(button), "im_id_recherche_entry");
   
    if (!input) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ID introuvable");
        return;
    }
   
    id = atoi(gtk_entry_get_text(GTK_ENTRY(input)));
   
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "imtreeview1");
    if (!treeview) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : TreeView introuvable");
        return;
    }
   
    vider_treeview(treeview);
   
    if (chercher_centre(id, &c)) {
        afficher_centre_dans_treeview(treeview, c);
    } else {
        show_error_dialog(GTK_WIDGET(button), "Centre non trouvé");
    }
}

void on_im_paratger_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "imtreeview1");
    if (!treeview) {
        g_warning("TreeView treeview3 not found");
        show_error_dialog(GTK_WIDGET(button), "Erreur : TreeView introuvable");
        return;
    }
    
    // Vider avant d'afficher
    vider_treeview(treeview);
    
    // Afficher tous les centres
    afficher_centre(treeview);
}

void on_im_retour_recherche_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

void on_imtreeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
   
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gint id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        selected_centre_id = id;
    }
}


void on_imtreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    on_imtreeview2_row_activated(treeview, path, column, user_data);
}

void on_im_export_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité export à implémenter");
}

/* ========== CALLBACKS INSCRIPTION ========== */
void on_im_inscri_button_clicked(GtkButton *button, gpointer user_data)
{
    Inscription i;
   
    if (selected_centre_id == -1) {
        show_error_dialog(GTK_WIDGET(button), "Veuillez sélectionner un centre");
        return;
    }
   
    i.idCentre = selected_centre_id;
    strcpy(i.nomEntraineur, "Entraineur"); // À récupérer depuis un champ
    strcpy(i.emailEntraineur, "test@test.com"); // À récupérer depuis un champ
   
    if (ajouter_inscription(i)) {
        show_success_dialog(GTK_WIDGET(button), "Inscription réussie");
    } else {
        show_error_dialog(GTK_WIDGET(button), "Erreur lors de l'inscription");
    }
}

void on_im_annuler_inscri_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(current_window);
}

void on_im_retour_inscri_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *ent_window = create_Espace_Entraineur();
    gtk_widget_show(ent_window);
}

/* ========== CALLBACKS STATISTIQUES ========== */
void on_im_stat_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    filtre_parking = gtk_toggle_button_get_active(togglebutton) ? 1 : -1;
}

void on_im_stat_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    filtre_weekend = gtk_toggle_button_get_active(togglebutton) ? 1 : -1;
}

void on_im_appliquer_button_clicked(GtkButton *button, gpointer user_data)
{
    char ville[50] = "";
    int type = -1;
    int capacite_min = 0;
    int capacite_max = 10000;
   
    GtkWidget *combo = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_stat");
    if (combo) {
        const char *v = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));
        if (v) strcpy(ville, v);
    }
   
    GtkWidget *entry_min = lookup_widget(GTK_WIDGET(button), "im_cmin_entry");
    if (entry_min) {
        const char *txt = gtk_entry_get_text(GTK_ENTRY(entry_min));
        if (txt && strlen(txt) > 0) capacite_min = atoi(txt);
    }
   
    GtkWidget *entry_max = lookup_widget(GTK_WIDGET(button), "im_cmax_entry");
    if (entry_max) {
        const char *txt = gtk_entry_get_text(GTK_ENTRY(entry_max));
        if (txt && strlen(txt) > 0) capacite_max = atoi(txt);
    }
   
    int total = calculer_total_centres(ville, type, capacite_min, capacite_max,
                                       filtre_parking, filtre_weekend);
    float moyenne = calculer_moyenne_capacite(ville, type, capacite_min, capacite_max,
                                              filtre_parking, filtre_weekend);
    float pourc_parking = calculer_pourcentage_parking(ville, type, capacite_min, capacite_max,
                                                        filtre_parking, filtre_weekend);
    float pourc_weekend = calculer_pourcentage_weekend(ville, type, capacite_min, capacite_max,
                                                        filtre_parking, filtre_weekend);
   
    int nb_prive = 0, nb_public = 0;
    calculer_repartition_type(ville, capacite_min, capacite_max,
                              filtre_parking, filtre_weekend, &nb_prive, &nb_public);
   
    char buffer[256];
    GtkWidget *label;
   
    label = lookup_widget(GTK_WIDGET(button), "im_tot_label");
    if (label) {
        sprintf(buffer, "Nombre total de centres : %d", total);
        gtk_label_set_text(GTK_LABEL(label), buffer);
    }
   
    label = lookup_widget(GTK_WIDGET(button), "im_moy_label");
    if (label) {
        sprintf(buffer, "Moyenne de capacité : %.2f", moyenne);
        gtk_label_set_text(GTK_LABEL(label), buffer);
    }
   
    label = lookup_widget(GTK_WIDGET(button), "im_pourc_park_label");
    if (label) {
        sprintf(buffer, "%% centres avec parking : %.1f%%", pourc_parking);
        gtk_label_set_text(GTK_LABEL(label), buffer);
    }
   
    GtkWidget *progressbar1 = lookup_widget(GTK_WIDGET(button), "im_progressbar1");
    if (progressbar1) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar1), pourc_parking / 100.0);
    }
   
    label = lookup_widget(GTK_WIDGET(button), "im_pourc_ouvert_label");
    if (label) {
        sprintf(buffer, "%% centres ouverts le week-end : %.1f%%", pourc_weekend);
        gtk_label_set_text(GTK_LABEL(label), buffer);
    }
   
    GtkWidget *progressbar2 = lookup_widget(GTK_WIDGET(button), "im_progressbar2");
    if (progressbar2) {
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressbar2), pourc_weekend / 100.0);
    }
   
    label = lookup_widget(GTK_WIDGET(button), "im_repartition_label");
    if (label) {
        sprintf(buffer, "Privés : %d\nPublics : %d", nb_prive, nb_public);
        gtk_label_set_text(GTK_LABEL(label), buffer);
    }
}

void on_im_retour_stat_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

/* ========== HELPER FUNCTIONS FOR TREEVIEW ========== */
void vider_treeview(GtkWidget *treeview)
{
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (model != NULL) {
        GtkListStore *store = GTK_LIST_STORE(model);
        gtk_list_store_clear(store);
    }
}

void afficher_centre_dans_treeview(GtkWidget *treeview, Centre c)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
   
    if (model == NULL) {
        // Create the model if it doesn't exist
        GtkListStore *store = gtk_list_store_new(10,
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
       
        // Create columns
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
        model = GTK_TREE_MODEL(store);
    }
   
    GtkListStore *store = GTK_LIST_STORE(model);
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
/* ========== MISSING CALLBACKS FOR CONFIRMATION DIALOG ========== */
void on_confirmer_cancel_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);

    /* Important : si vous utilisez un dialogue personnalisé à la place de
       show_confirmation_dialog(), vous devez transmettre la réponse "NON"
       au code appelant. Ici on suppose que vous avez stocké un pointeur
       vers une variable int *response dans user_data. */
    if (user_data != NULL) {
        *((int *)user_data) = GTK_RESPONSE_NO;
    }
}

void on_confirmer_ok_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);

    /* Transmission de la réponse "OUI" au code appelant */
    if (user_data != NULL) {
        *((int *)user_data) = GTK_RESPONSE_YES;
    }
}

void
on_im_modifier_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *modif_window = create_imen_bm_Modifier();
    gtk_widget_show(modif_window);
}


void
on_im_supprimer_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *supp_window = create_imen_bm_Suppmod();
    gtk_widget_show(supp_window);
}


void on_rechercher_inscri_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *combo = lookup_widget(GTK_WIDGET(button), "im_inscri_ville_combobox");
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    
    if (!combo) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champ ville introuvable");
        return;
    }
    
    if (!treeview) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : TreeView introuvable");
        return;
    }
    
    // Récupérer la ville sélectionnée
    char *ville = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo));
    
    if (!ville || strlen(ville) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Veuillez sélectionner une ville");
        if (ville) g_free(ville);
        return;
    }
    
    printf("DEBUG: Recherche des centres pour la ville: %s\n", ville);
    
    // Vider le treeview avant d'afficher
    vider_treeview(treeview);
    
    // Afficher les centres par ville
    afficher_centres_par_ville(ville, treeview);
    
    g_free(ville);
}



/* ========== CALLBACKS AUTHENTIFICATION ========== */
void on_se_connecter_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *input_id, *input_mdp;
    const char *identifiant, *mot_de_passe;
    char type[20];
    
    // Récupérer les widgets
    input_id = lookup_widget(GTK_WIDGET(button), "entry_identifiant");
    input_mdp = lookup_widget(GTK_WIDGET(button), "entry_mot_de_passe");
    
    if (!input_id || !input_mdp) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Champs introuvables");
        return;
    }
    
    // Récupérer les valeurs
    identifiant = gtk_entry_get_text(GTK_ENTRY(input_id));
    mot_de_passe = gtk_entry_get_text(GTK_ENTRY(input_mdp));
    
    // Validation
    if (strlen(identifiant) == 0 || strlen(mot_de_passe) == 0) {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Veuillez remplir tous les champs");
        return;
    }
    
    // Authentification
    if (authentifier_utilisateur(identifiant, mot_de_passe, type)) {
        GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
        gtk_widget_hide(current_window);
        
        // Ouvrir l'interface appropriée
        if (strcmp(type, "admin") == 0) {
            GtkWidget *admin_window = create_Espace_Admin();
            gtk_widget_show(admin_window);
        } else if (strcmp(type, "entraineur") == 0) {
            GtkWidget *entraineur_window = create_Espace_Entraineur();
            gtk_widget_show(entraineur_window);
        }
    } else {
        show_error_dialog(GTK_WIDGET(button), "Erreur : Identifiant ou mot de passe incorrect");
    }
}
void
on_notreeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar *idag,*nom_ag,*Disponible,*etat;
gint  *Quantite_ag;
agent d;
GtkTreeModel *model=gtk_tree_view_get_model(treeview);
if (gtk_tree_model_get_iter(model,&iter,path))
{ gtk_tree_model_get(GTK_TREE_MODEL(model),&iter,0,idag,1,nom_ag,2,Quantite_ag,3,Disponible,4,etat,-1);
strcpy(d.idag,idag);
strcpy(d.nom_ag,nom_ag);
strcpy(d.Disponible,Disponible);
strcpy(d.etat,etat);
d.Quantite.jj=*Quantite_ag;
afficherequipment(treeview);}
}


void
on_btngotoaj_clicked                   (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "Afficherequipment");
p=lookup_widget(objet_graphique, "Ajoutequipment");
p=  create_Ajoutequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_btngotomodif_clicked                (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "Afficherequipment");
p=lookup_widget(objet_graphique, "modifierequipment");
p=  create_modifierequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_gotosupp_clicked                    (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "Afficherequipment");
p=lookup_widget(objet_graphique, "supprimerequipment");
p=  create_supprimerequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_actualiser_clicked                  (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget *treeview;
treeview=lookup_widget(objet_graphique,"notreeview1");
afficherequipment(GTK_TREE_VIEW(treeview));
}


void
on_checkbuttonconfaj_toggled           (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
c=1;
}


void
on_buttonrtaj_clicked                  (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "Ajoutequipment");
p=lookup_widget(objet_graphique, "Afficherequipment");
p=  create_Afficherequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_btnajagent_clicked                  (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*id;
GtkWidget*nom;
GtkWidget*Disponible;
GtkWidget*Quantite;
GtkWidget*etat;
GtkWidget*label;
agent a;
int t;
label=lookup_widget(objet_graphique, "labelccaj");
id=lookup_widget(objet_graphique, "entryidagentaj");
nom=lookup_widget(objet_graphique, "entrynomagentaj");
strcpy(a.idag,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(a.nom_ag,gtk_entry_get_text(GTK_ENTRY(nom)));  
etat=lookup_widget(objet_graphique, "comboboxentryposteaj");
strcpy(a.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)));
if (x==1){
strcpy(a.Disponible,"oui");}
else 
if (x==2){
strcpy(a.Disponible,"non");}
Quantite=lookup_widget(objet_graphique, "spinbuttonjouraj");
a.Quantite.jj=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Quantite));
if(c==1){
t=ajoutequipment(a);
if(t==1)
gtk_label_set_text(GTK_LABEL(label)," valider");
else
gtk_label_set_text(GTK_LABEL(label)," error");
}
else
gtk_label_set_text(GTK_LABEL(label)," Confirmer !");
}


void
on_radiobuttonhommeaj_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
x=1;
}


void
on_radiobuttonfemmeaj_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
x=2;
}


void
on_buttonrechidmodif_clicked           (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*id;
GtkWidget*nom;
GtkWidget*etat;
GtkWidget*Quantite;
GtkWidget*oui;
GtkWidget*non;
GtkWidget*label;
char ch[50];
agent *a;
id=lookup_widget(objet_graphique, "entryidagentmodif");
nom=lookup_widget(objet_graphique, "entrynomagmodif");
etat=lookup_widget(objet_graphique, "comboboxentrypostemodif");
Quantite=lookup_widget(objet_graphique, "spinbuttondayagmodif");
oui=lookup_widget(objet_graphique, "radiobuttonhommemodif");
non=lookup_widget(objet_graphique, "radiobuttonfemmodif");
label=lookup_widget(objet_graphique, "lablresultmodifrech");
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(id))); 
a=chercherequipment(ch);
if(a==NULL)
gtk_label_set_text(GTK_LABEL(label),"non trouvé");
else{
gtk_entry_set_text(GTK_ENTRY(nom),a->nom_ag);
if(strcmp(a->Disponible,"oui")==0){
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(oui),TRUE);
}
else{
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(non),TRUE);
}
gtk_spin_button_set_value(GTK_SPIN_BUTTON(Quantite),a->Quantite.jj);
if(strcmp(a->etat,"neuf")==0)
gtk_combo_box_set_active(GTK_COMBO_BOX(etat),0);
else if(strcmp(a->etat,"moyen")==0)
gtk_combo_box_set_active(GTK_COMBO_BOX(etat),1);
else
gtk_combo_box_set_active(GTK_COMBO_BOX(etat),2);
}
}


void
on_radiobuttonfemmodif_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
x2=2;
}


void
on_radiobuttonhommemodif_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(togglebutton)))
x2=1;
}


void
on_btnmodifieragent_clicked            (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*id;
GtkWidget*nom;
GtkWidget*etat;
GtkWidget*Quantite;
GtkWidget*label;
agent a;
int t;
id=lookup_widget(objet_graphique, "entryidagentmodif");
nom=lookup_widget(objet_graphique, "entrynomagmodif");
etat=lookup_widget(objet_graphique, "comboboxentrypostemodif");
Quantite=lookup_widget(objet_graphique, "spinbuttondayagmodif");
label=lookup_widget(objet_graphique, "labccmodif");
strcpy(a.idag,gtk_entry_get_text(GTK_ENTRY(id)));
strcpy(a.nom_ag,gtk_entry_get_text(GTK_ENTRY(nom))); 
strcpy(a.etat,gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)));
if (x2==1){
strcpy(a.Disponible,"oui");}
else 
if (x2==2){
strcpy(a.Disponible,"non");}
a.Quantite.jj=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(Quantite));
t=modiferequipment(a);
if(t==1)
gtk_label_set_text(GTK_LABEL(label)," valider");
else
gtk_label_set_text(GTK_LABEL(label)," error"); 
}


void
on_buttonrtmodi_clicked                (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "modifierequipment");
p=lookup_widget(objet_graphique, "Afficherequipment");
p=  create_Afficherequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_buttonrtsupp_clicked                (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*n;
GtkWidget*p;
n=lookup_widget(objet_graphique, "supprimerequipment");
p=lookup_widget(objet_graphique, "Afficherequipment");
p=  create_Afficherequipment();
gtk_widget_show(p);
gtk_widget_destroy(n);
}


void
on_buttonsupprimeagent_clicked         (GtkWidget *objet_graphique, gpointer user_data)
{
GtkWidget*id;
GtkWidget*label;
char ch[50];
int t=0;
label=lookup_widget(objet_graphique, "labelccsupprimer");
id=lookup_widget(objet_graphique, "entrysupprimerag");
strcpy(ch,gtk_entry_get_text(GTK_ENTRY(id))); 
t=supprimerequipment(ch);
if(t==1)
gtk_label_set_text(GTK_LABEL(label)," valider");
else
gtk_label_set_text(GTK_LABEL(label)," error");
}


void on_calendar_res_day_selected(GtkCalendar *calendar, gpointer user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(calendar), "treeview_dispo");
    afficher_disponibilite_date(GTK_TREE_VIEW(treeview));
}

void on_btn_chercher_res_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *entry_id = lookup_widget(button, "entry_id_res");
    GtkWidget *entry_nom = lookup_widget(button, "entry_nom_equipement");
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    agent *ag = chercherequipment((char*)id);

    if (ag)
    {
        gtk_entry_set_text(GTK_ENTRY(entry_nom), ag->nom_ag);
        free(ag);
    }
    else
        gtk_entry_set_text(GTK_ENTRY(entry_nom), "Introuvable");
}

void on_btn_reserver_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *entry_id = lookup_widget(button, "entry_id_res");
    GtkWidget *entry_nom = lookup_widget(button, "entry_nom_equipement");
    GtkWidget *spin = lookup_widget(button, "spin_quantite_res");
    GtkWidget *cal = lookup_widget(button, "calendar_res");
    GtkWidget *label = lookup_widget(button, "label_message_res");

    Reservation r;
    strcpy(r.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    strcpy(r.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));

    guint y, m, d;
    gtk_calendar_get_date(GTK_CALENDAR(cal), &y, &m, &d);
    r.jour = d; r.mois = m+1; r.annee = y;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "check_matin"))))
        strcpy(r.periode, "matin");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "check_midi"))))
        strcpy(r.periode, "midi");
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(button, "check_soir"))))
        strcpy(r.periode, "soir");
    else { gtk_label_set_text(GTK_LABEL(label), "Choisissez une période !"); return; }

    r.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));

    if (reserver_equipement(r))
    {
        gtk_label_set_text(GTK_LABEL(label), "Réservation effectuée !");
        afficher_disponibilite_date(GTK_TREE_VIEW(lookup_widget(button, "treeview_dispo")));
    }
    else
        gtk_label_set_text(GTK_LABEL(label), "Échec : indisponible ou quantité insuffisante");
}

void on_btn_annuler_res_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *win = lookup_widget(button, "reservationequipment");
    gtk_widget_destroy(win);
}

void on_btn_stats_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *stats = create_statistiques();
    gtk_widget_show(stats);
    afficher_statistiques(stats);
}

void on_btn_actualiser_stats_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *win = lookup_widget(button, "statistiques");
    afficher_statistiques(win);
}

void on_btn_fermer_stats_clicked(GtkWidget *button, gpointer user_data)
{
    GtkWidget *win = lookup_widget(button, "statistiques");
    gtk_widget_destroy(win);
}


void on_tasnim_button0_clicked (GtkWidget *button, gpointer user_data) {
    g_print("=== DEBUT on_tasnim_button0_clicked ===\n");
    
    GtkWidget *window = gtk_widget_get_toplevel (GTK_WIDGET (button));
    g_print("Window récupérée: %p\n", window);
    
    GtkWidget *entry = (GtkWidget *) g_object_get_data (G_OBJECT (window), "entry_id");
    
    if (entry == NULL) {
        g_print("Entry non trouvée via g_object_get_data, essai avec lookup_widget...\n");
        entry = lookup_widget(window, "tasnim_entry0");
        g_print("Entry via lookup_widget: %p\n", entry);
    }
    
    if (entry == NULL) {
        g_print ("ERREUR: Champ d'identifiant non trouvé!\n");
        return;
    }
    
    const gchar *id = gtk_entry_get_text (GTK_ENTRY (entry));
    g_print ("Identifiant saisi: '%s'\n", id);
    
    /* Vérification du rôle */
    if (g_ascii_strcasecmp (id, "admin") == 0) {
        g_print ("==> Ouverture de l'interface Admin...\n");
        
        // Créer la nouvelle fenêtre
        g_print ("Création de la fenêtre admin...\n");
        GtkWidget *admin_window = create_tasnim_window16_gestiondescourssportifs();
        g_print ("Fenêtre admin créée: %p\n", admin_window);
        
        if (admin_window == NULL) {
            g_print("ERREUR CRITIQUE: Impossible de créer la fenêtre admin!\n");
            return;
        }
        
        // Afficher la fenêtre AVANT de détruire l'ancienne
        g_print ("Affichage de la fenêtre admin...\n");
        gtk_widget_show_all(admin_window);
        g_print ("gtk_widget_show_all() exécuté\n");
        
        // Connecter le signal destroy
        g_print ("Connexion du signal destroy...\n");
        g_signal_connect(admin_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        
        // Détruire l'ancienne fenêtre
        g_print ("Destruction de la fenêtre d'authentification...\n");
        gtk_widget_destroy(window);
        g_print ("Fenêtre d'authentification détruite\n");
        
        g_print ("=== Interface Admin ouverte avec succès ===\n");
        
    } else if (g_ascii_strcasecmp (id, "membre") == 0) {
        g_print ("==> Ouverture de l'interface Membre...\n");
        
        // Créer la nouvelle fenêtre
        g_print ("Création de la fenêtre membre...\n");
        GtkWidget *membre_window = create_tasnim_window10_inscriptioncours();
        g_print ("Fenêtre membre créée: %p\n", membre_window);
        
        if (membre_window == NULL) {
            g_print("ERREUR CRITIQUE: Impossible de créer la fenêtre membre!\n");
            return;
        }
        
        // Afficher la fenêtre AVANT de détruire l'ancienne
        g_print ("Affichage de la fenêtre membre...\n");
        gtk_widget_show_all(membre_window);
        g_print ("gtk_widget_show_all() exécuté\n");
        
        // Connecter le signal destroy
        g_print ("Connexion du signal destroy...\n");
        g_signal_connect(membre_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        
        // Détruire l'ancienne fenêtre
        g_print ("Destruction de la fenêtre d'authentification...\n");
        gtk_widget_destroy(window);
        g_print ("Fenêtre d'authentification détruite\n");
        
        g_print ("=== Interface Membre ouverte avec succès ===\n");
        
    } else {
        g_print ("==> Identifiant invalide: '%s'\n", id);
        
        // Identifiant invalide
        GtkWidget *dialog = gtk_message_dialog_new (GTK_WINDOW (window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Identifiant invalide!\nUtilisez 'admin' ou 'membre'.");
        gtk_window_set_title (GTK_WINDOW (dialog), "Erreur d'authentification");
        gtk_dialog_run (GTK_DIALOG (dialog));
        gtk_widget_destroy (dialog);
        
        // Effacer le champ et remettre le focus
        gtk_entry_set_text (GTK_ENTRY (entry), "");
        gtk_widget_grab_focus (entry);
    }
    
    g_print("=== FIN on_tasnim_button0_clicked ===\n\n");
}
	

// Variables globales
int duree_selectionnee = 0;
int niveau_checked[3] = {0, 0, 0};
char id_membre_courant[20] = "MEM001"; // ID par défaut

void set_id_membre_courant(char id[]) {
    strcpy(id_membre_courant, id);
}

char* get_id_membre_courant() {
    return id_membre_courant;
}

// Fonctions auxiliaires
void afficher_cours_dans_treeview(GtkWidget *treeview) {
    GtkListStore *store = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING,
                                            G_TYPE_STRING, G_TYPE_STRING,
                                            G_TYPE_STRING, G_TYPE_INT,
                                            G_TYPE_FLOAT);
    GtkTreeIter iter;
   
    // Créer les colonnes si elles n'existent pas
    if (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) == NULL) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *col;
       
        col = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Entraîneur", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
       
        col = gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
    }
   
    // Lire les cours du fichier
    FILE *f = fopen("cours.txt", "r");
    if (f) {
        Cours c;
        while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                      c.id, c.nom, c.entraineur, c.date,
                      c.heure, &c.duree, c.centre, c.niveau,
                      &c.capacite_max, &c.tarif, &c.inscrits) != EOF) {
           
            char capacite[20];
            sprintf(capacite, "%d/%d", c.inscrits, c.capacite_max);
           
            char tarif_str[20];
            sprintf(tarif_str, "%.2f DT", c.tarif);
           
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, c.id,
                              1, c.nom,
                              2, c.entraineur,
                              3, c.date,
                              4, c.heure,
                              5, c.capacite_max,
                              6, c.tarif,
                              -1);
        }
        fclose(f);
    }
   
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}

// Gestion des cours - Menu principal
void on_tasnim_button16_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *ajout = create_tasnim_window15_ajoutd_uncours();
   
    gtk_widget_show(ajout);
    gtk_widget_hide(current);
}

void on_tasnim_button1616_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *modif = create_tasnim_window14_modificationducours();
   
    gtk_widget_show(modif);
    gtk_widget_hide(current);
}

void on_tasnim_button161616_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *supp = create_tasnim_window13_suppressiond_uncours();
   
    gtk_widget_show(supp);
    gtk_widget_hide(current);
}

void on_tasnim_button16161616_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *recherche = create_tasnim_window12_recherched_uncours();
   
    gtk_widget_show(recherche);
    gtk_widget_hide(current);
}

void on_tasnim_button1616161616_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *stats = create_tasnim_window7_statistiquesglobales();
   
    gtk_widget_show(stats);
    gtk_widget_hide(current);
   
    // Actualiser les statistiques
    afficher_statistiques_globales(stats);
}

void on_tasnim_button161616161616_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = lookup_widget(button, "tasnim.window16.gestiondescourssportifs");
    GtkWidget *stats_filtre = create_tasnim_window6_statistiquesparfiltre();
   
    gtk_widget_show(stats_filtre);
    gtk_widget_hide(current);
}

// Ajout cours
void on_tasnim_radiobutton15_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 1; // 30 minutes
    }
}

void on_tasnim_radiobutton1515_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 2; // 1 heure
    }
}

void on_tasnim_radiobutton151515_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 3; // 90 minutes
    }
}

void on_tasnim_checkbutton15_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[0] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_checkbutton1515_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[1] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_checkbutton151515_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[2] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_button15_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu principal
    GtkWidget *current = lookup_widget(button, "tasnim.window15.ajoutd'uncours");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button1515_clicked(GtkWidget *button, gpointer user_data) {
    // Ajouter le cours
    GtkWidget *entry_id = lookup_widget(button, "tasnim.entry15");
    GtkWidget *entry_nom = lookup_widget(button, "tasnim.entry15");
    GtkWidget *combo_entraineur = lookup_widget(button, "tasnim.comboboxentry151515");
    GtkWidget *entry_date = lookup_widget(button, "tasnim.entry15151515");
    GtkWidget *entry_heure = lookup_widget(button, "tasnim.entry1515151515");
    GtkWidget *combo_centre = lookup_widget(button, "tasnim.comboboxentry1515");
    GtkWidget *spin_capacite = lookup_widget(button, "tasnim.spinbutton15");
    GtkWidget *entry_tarif = lookup_widget(button, "tasnim.entry15151515151515151515");
   
    // Validation des données
    if (strlen(gtk_entry_get_text(GTK_ENTRY(entry_id))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(entry_nom))) == 0 ||
        duree_selectionnee == 0) {
       
        // Afficher dialogue d'erreur
        GtkWidget *dialog = create_tasnim_dialog4_erreurajout();
        gtk_widget_show(dialog);
        return;
    }
   
    Cours nouveau;
    strcpy(nouveau.id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
    strcpy(nouveau.nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
   
    const char *entraineur = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_entraineur));
    if (entraineur) strcpy(nouveau.entraineur, entraineur);
    else strcpy(nouveau.entraineur, "ali selmi");
   
    strcpy(nouveau.date, gtk_entry_get_text(GTK_ENTRY(entry_date)));
    strcpy(nouveau.heure, gtk_entry_get_text(GTK_ENTRY(entry_heure)));
   
    nouveau.duree = duree_selectionnee;
   
    const char *centre = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
    if (centre) strcpy(nouveau.centre, centre);
    else strcpy(nouveau.centre, "tunis");
   
    // Déterminer le niveau
    if (niveau_checked[0]) strcpy(nouveau.niveau, "débutant");
    else if (niveau_checked[1]) strcpy(nouveau.niveau, "intermédiaire");
    else if (niveau_checked[2]) strcpy(nouveau.niveau, "avancé");
    else strcpy(nouveau.niveau, "débutant");
   
    nouveau.capacite_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    nouveau.tarif = atof(gtk_entry_get_text(GTK_ENTRY(entry_tarif)));
    nouveau.inscrits = 0;
   
    ajouter_cours(nouveau);
   
    // Afficher message de succès
    GtkWidget *succes = create_tasnim_window5_succesajout();
    gtk_widget_show(succes);
   
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window15.ajoutd'uncours");
    gtk_widget_hide(current);
}

// Modification cours
void on_tasnim_radiobutton14_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 1;
    }
}

void on_tasnim_radiobutton1414_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 2;
    }
}

void on_tasnim_radiobutton141414_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        duree_selectionnee = 3;
    }
}

void on_tasnim_checkbutton14_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[0] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_checkbutton1414_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[1] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_checkbutton141414_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    niveau_checked[2] = gtk_toggle_button_get_active(togglebutton);
}

void on_tasnim_button14_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window14.modificationducours");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button1414_clicked(GtkWidget *button, gpointer user_data) {
    // Récupérer les données du formulaire
    GtkWidget *entry_id = lookup_widget(button, "tasnim.entry14");
    GtkWidget *entry_nom = lookup_widget(button, "tasnim.entry14");
    GtkWidget *combo_entraineur = lookup_widget(button, "tasnim.comboboxentry141414");
    GtkWidget *entry_date = lookup_widget(button, "tasnim.entry14141414");
    GtkWidget *entry_heure = lookup_widget(button, "tasnim.entry1414141414");
    GtkWidget *combo_centre = lookup_widget(button, "tasnim.comboboxentry1414");
    GtkWidget *spin_capacite = lookup_widget(button, "tasnim.spinbutton14");
    GtkWidget *entry_tarif = lookup_widget(button, "tasnim.entry14141414141414141414");
   
    char id[20];
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
   
    Cours *c = rechercher_cours(id);
    if (!c) {
        // Cours non trouvé
        return;
    }
   
    // Mettre à jour les données
    strcpy(c->nom, gtk_entry_get_text(GTK_ENTRY(entry_nom)));
   
    const char *entraineur = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_entraineur));
    if (entraineur) strcpy(c->entraineur, entraineur);
   
    strcpy(c->date, gtk_entry_get_text(GTK_ENTRY(entry_date)));
    strcpy(c->heure, gtk_entry_get_text(GTK_ENTRY(entry_heure)));
   
    c->duree = duree_selectionnee;
   
    const char *centre = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
    if (centre) strcpy(c->centre, centre);
   
    // Déterminer le niveau
    if (niveau_checked[0]) strcpy(c->niveau, "débutant");
    else if (niveau_checked[1]) strcpy(c->niveau, "intermédiaire");
    else if (niveau_checked[2]) strcpy(c->niveau, "avancé");
   
    c->capacite_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    c->tarif = atof(gtk_entry_get_text(GTK_ENTRY(entry_tarif)));
   
    modifier_cours(*c);
    free(c);
   
    // Message de succès
    GtkWidget *succes = create_tasnim_window5_succesajout();
    gtk_widget_show(succes);
}

// Suppression cours
void on_tasnim_button13_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window13.suppressiond'uncours");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button1313_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *entry_id = lookup_widget(button, "tasnim.entry13");
    char id[20];
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
   
    if (strlen(id) == 0) {
        return;
    }
   
    // Afficher confirmation
    GtkWidget *dialog = create_tasnim_dialog2_confirmationdesuppression();
    gtk_widget_show(dialog);
   
    // Stocker l'ID pour la suppression
    g_object_set_data(G_OBJECT(dialog), "cours_id", g_strdup(id));
}

// Recherche cours
void on_tasnim_button12_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *entry_id = lookup_widget(button, "tasnim.entry12");
    GtkWidget *treeview = lookup_widget(button, "tasnim.treeview12");
   
    char id[20];
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(entry_id)));
   
    if (strlen(id) == 0) {
        // Afficher tous les cours
        afficher_cours_dans_treeview(treeview);
        return;
    }
   
    Cours *c = rechercher_cours(id);
    if (!c) {
        // Afficher dialogue d'erreur
        GtkWidget *dialog = create_tasnim_dialog11_erreurderecherche();
        gtk_widget_show(dialog);
        return;
    }
   
    // Afficher le cours trouvé dans le treeview
    vider_treeview(treeview);
    GtkListStore *store = gtk_list_store_new(7, G_TYPE_STRING, G_TYPE_STRING,
                                            G_TYPE_STRING, G_TYPE_STRING,
                                            G_TYPE_STRING, G_TYPE_INT,
                                            G_TYPE_FLOAT);
    GtkTreeIter iter;
   
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter,
                      0, c->id,
                      1, c->nom,
                      2, c->entraineur,
                      3, c->date,
                      4, c->heure,
                      5, c->capacite_max,
                      6, c->tarif,
                      -1);
   
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
    free(c);
}

void on_tasnim_button1212_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window12.recherched'uncours");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button121212_clicked(GtkWidget *button, gpointer user_data) {
    // Exporter les recherches (simplement afficher un message)
    GtkWidget *treeview = lookup_widget(button, "tasnim.treeview12");
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
   
    if (model) {
        FILE *f = fopen("recherches_export.txt", "w");
        if (f) {
            GtkTreeIter iter;
            gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
           
            while (valid) {
                char *id, *nom, *entraineur, *date, *heure;
                int capacite;
                float tarif;
               
                gtk_tree_model_get(model, &iter,
                                  0, &id,
                                  1, &nom,
                                  2, &entraineur,
                                  3, &date,
                                  4, &heure,
                                  5, &capacite,
                                  6, &tarif,
                                  -1);
               
                fprintf(f, "%s,%s,%s,%s,%s,%d,%.2f\n",
                        id, nom, entraineur, date, heure, capacite, tarif);
               
                g_free(id);
                g_free(nom);
                g_free(entraineur);
                g_free(date);
                g_free(heure);
               
                valid = gtk_tree_model_iter_next(model, &iter);
            }
            fclose(f);
        }
    }
}

// Inscription cours
void on_tasnim_button10_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(button, "tasnim.treeview10");
    afficher_cours_dans_treeview(treeview);
}

void on_tasnim_treeview10_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                       GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    char *id_cours;
   
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &id_cours, -1);
       
        // Vérifier disponibilité et inscrire
        if (inscription_cours(id_cours, id_membre_courant)) {
            // Afficher message de succès
            GtkWidget *succes = create_tasnim_window1_inscriptionavecsucces();
            gtk_widget_show(succes);
           
            // Actualiser l'affichage
            afficher_cours_dans_treeview(GTK_WIDGET(treeview));
        } else {
            // Afficher message d'erreur
            GtkWidget *dialog = create_tasnim_dialog8_impossibledes_inscrire();
            gtk_widget_show(dialog);
        }
        g_free(id_cours);
    }
}

void on_tasnim_button1010_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window10.inscriptioncours");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button101010_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *treeview = lookup_widget(button, "tasnim.treeview10");
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;
   
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        char *id_cours;
        gtk_tree_model_get(model, &iter, 0, &id_cours, -1);
       
        // Vérifier disponibilité et inscrire
        if (inscription_cours(id_cours, id_membre_courant)) {
            // Afficher message de succès
            GtkWidget *succes = create_tasnim_window1_inscriptionavecsucces();
            gtk_widget_show(succes);
           
            // Actualiser l'affichage
            afficher_cours_dans_treeview(treeview);
        } else {
            // Afficher message d'erreur
            GtkWidget *dialog = create_tasnim_dialog8_impossibledes_inscrire();
            gtk_widget_show(dialog);
        }
        g_free(id_cours);
    }
}

// Statistiques
void on_tasnim_button7_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window7.statistiquesglobales");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

void on_tasnim_button6_clicked(GtkWidget *button, gpointer user_data) {
    // Retour au menu
    GtkWidget *current = lookup_widget(button, "tasnim.window6.statistiquesparfiltre");
    GtkWidget *menu = create_tasnim_window16_gestiondescourssportifs();
   
    gtk_widget_show(menu);
    gtk_widget_hide(current);
}

// Dialogues
void on_tasnim_okbutton11_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_cancelbutton8_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_okbutton8_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_cancelbutton4_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_okbutton4_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_cancelbutton2_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(dialog);
}

void on_tasnim_okbutton2_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    char *id = (char*)g_object_get_data(G_OBJECT(dialog), "cours_id");
   
    if (id) {
        if (supprimer_cours(id)) {
            // Afficher message de succès
            GtkWidget *succes = create_tasnim_window3_successupprimer();
            gtk_widget_show(succes);
        }
        g_free(id);
    }
   
    gtk_widget_destroy(dialog);
}

// Succès
void on_tasnim_button5_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(current);
}

void on_tasnim_button3_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(current);
}

void on_tasnim_button1_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *current = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(current);
}
	


void
on_tasnim_button16161616161616_clicked (GtkWidget      *button,
                                        gpointer         user_data)
{

}
// AJOUTEZ CES 3 FONCTIONS dans callbacks.c
// (après les autres callbacks, avant la fin du fichier)

void on_tasnim_spinbutton15_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    // Callback pour le changement de la valeur du spinbutton (capacité max)
    // Pas d'action spécifique nécessaire pour l'instant
    g_print("Capacité changée: %d\n", gtk_spin_button_get_value_as_int(spinbutton));
}

void on_tasnim_comboboxentry151515_changed(GtkComboBox *combobox, gpointer user_data) {
    // Callback pour le changement de sélection du combobox (entraîneur)
    // Pas d'action spécifique nécessaire pour l'instant
    const char *text = gtk_combo_box_get_active_text(combobox);
    if (text) {
        g_print("Entraîneur sélectionné: %s\n", text);
    }
}

void on_tasnim_treeview12_row_activated(GtkTreeView *treeview, GtkTreePath *path,
                                       GtkTreeViewColumn *column, gpointer user_data) {
    // Callback pour double-clic sur une ligne du treeview de recherche
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    char *id_cours;
   
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &id_cours, -1);
        
        // Afficher les détails du cours sélectionné
        g_print("Cours sélectionné: %s\n", id_cours);
        
        g_free(id_cours);
    }
}
/* ========== CALLBACKS MANQUANTS À AJOUTER DANS callbacks.c ========== */

/* Callbacks Centre manquants */
void on_on_im_stat_checknutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    on_im_stat_checkbutton2_toggled(togglebutton, user_data);
}
/* ========== CALLBACKS MANQUANTS - À AJOUTER À LA FIN DE callbacks.c ========== */

// Callback TreeView générique
void on_treeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                               GtkTreeViewColumn *column, gpointer user_data) {
    // Callback générique pour activation de ligne
}

// Callbacks Tasnim manquants
void on_tasnim_spinbutton4_capacit__max_changed(GtkSpinButton *spinbutton, gpointer user_data) {
    // Callback pour changement de capacité max
}

void on_tasnim_comboboxentry1_entra__neur_changed(GtkComboBox *combobox, gpointer user_data) {
    // Callback pour changement d'entraîneur
}

void on_tasnim_buttonretour_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(window);
}

void on_tasnim_buttonretour1_clicked(GtkWidget *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(button);
    gtk_widget_destroy(window);
}

// Callbacks Centre manquants
void on_im_supprimer_supp_button_clicked(GtkButton *button, gpointer user_data) {
    on_im_suppmod_supp_button_clicked(button, user_data);
}

void on_im_stat_checknutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    on_im_stat_checkbutton2_toggled(togglebutton, user_data);
}

// Callbacks messages Centre
void on_msg1_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg2_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg3_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg4_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg5_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg6_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_msg7_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

// Callbacks dialogues d'erreur
void on_error_id_cancel_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_error_id_ok_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_error_ajout_cancel_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

void on_error_ajout_ok_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *dialog = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(dialog);
}

// Callbacks authentification


// Callbacks TreeView Emna
void on_emtreeview3_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                                 GtkTreeViewColumn *column, gpointer user_data) {
    on_treeview3_row_activated(treeview, path, column, user_data);
}

void on_emtreeview4_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                                 GtkTreeViewColumn *column, gpointer user_data) {
    on_treeview4_row_activated(treeview, path, column, user_data);
}

// Callbacks Coach
void on_treeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, 
                               GtkTreeViewColumn *column, gpointer user_data) {
    // Callback pour activation ligne coach
}

void on_button46_clicked(GtkButton *button, gpointer user_data) {
    // Callback bouton 46
}

void on_emna_button43__ret_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(window);
}
void on_button_auth_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "Athentification");
    GtkWidget *entry_identifiant = lookup_widget(window, "entry1");
    GtkWidget *entry_mdp = lookup_widget(window, "entry2");
    
    if (!entry_identifiant || !entry_mdp) {
        g_print("ERREUR: Widgets d'authentification introuvables!\n");
        return;
    }
    
    const gchar *identifiant = gtk_entry_get_text(GTK_ENTRY(entry_identifiant));
    const gchar *mot_de_passe = gtk_entry_get_text(GTK_ENTRY(entry_mdp));
    
    char type_utilisateur[20];
    
    // Authentifier
    if (authentifier_utilisateur(identifiant, mot_de_passe, type_utilisateur)) {
        g_print("Connexion réussie en tant que: %s\n", type_utilisateur);
        
        // Fermer la fenêtre d'authentification
        gtk_widget_destroy(window);
        
        // Ouvrir la fenêtre selon le type
        if (strcmp(type_utilisateur, "admin") == 0) {
            g_print("Ouverture de l'Espace Admin...\n");
            GtkWidget *window_admin = create_Espace_Admin();
            gtk_widget_show(window_admin);
        } 
        else if (strcmp(type_utilisateur, "entraineur") == 0) {
            g_print("Ouverture de l'Espace Entraineur...\n");
            GtkWidget *window_entraineur = create_Espace_Entraineur();
            gtk_widget_show(window_entraineur);
        }
        else {
            g_print("Type d'utilisateur inconnu: %s\n", type_utilisateur);
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Type d'utilisateur inconnu!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // Authentification échouée
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Identifiant ou mot de passe incorrect!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        
        // Vider les champs
        gtk_entry_set_text(GTK_ENTRY(entry_identifiant), "");
        gtk_entry_set_text(GTK_ENTRY(entry_mdp), "");
    }
}
void initialiser_treeview_cours(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // Supprimer les anciennes colonnes
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *l = columns; l != NULL; l = l->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(l->data));
    }
    g_list_free(columns);
    
    // Créer le modèle
    GtkListStore *store = gtk_list_store_new(9,
                                             G_TYPE_STRING,  // ID
                                             G_TYPE_STRING,  // Nom
                                             G_TYPE_STRING,  // Entraineur
                                             G_TYPE_STRING,  // Date
                                             G_TYPE_STRING,  // Heure
                                             G_TYPE_INT,     // Durée
                                             G_TYPE_STRING,  // Centre
                                             G_TYPE_STRING,  // Niveau
                                             G_TYPE_INT);    // Inscrits/Capacité
    
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Colonnes
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Entraineur", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Durée", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Centre", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Niveau", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Inscrits", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(treeview, column);
}
void afficher_tous_les_cours(GtkTreeView *treeview)
{
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) return;
    
    gtk_list_store_clear(store);
    
    FILE *f = fopen("cours.txt", "r");
    if (!f) {
        g_print("Erreur: impossible d'ouvrir cours.txt\n");
        return;
    }
    
    Cours c;
    GtkTreeIter iter;
    
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%f|%d\n",
                  c.id, c.nom, c.entraineur, c.date, c.heure,
                  &c.duree, c.centre, c.niveau, &c.capacite_max,
                  &c.tarif, &c.inscrits) != EOF) {
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, c.id,
                          1, c.nom,
                          2, c.entraineur,
                          3, c.date,
                          4, c.heure,
                          5, c.duree,
                          6, c.centre,
                          7, c.niveau,
                          8, c.inscrits,
                          -1);
    }
    
    fclose(f);
}
void on_treeviewcourssportif_row_activated(GtkTreeView *treeview,
                                           GtkTreePath *path,
                                           GtkTreeViewColumn *column,
                                           gpointer user_data)
{
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    gchar *id_cours;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 0, &id_cours, -1);
        
        // Ici vous devez récupérer l'ID de l'entraineur connecté
        // Pour l'instant, on utilise "entraineur1" comme exemple
        char id_entraineur[20] = "entraineur1";
        
        if (inscription_cours(id_cours, id_entraineur)) {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Inscription réussie au cours %s!", id_cours);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            
            // Rafraîchir le treeview
            afficher_tous_les_cours(treeview);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Échec de l'inscription (cours complet ou déjà inscrit)");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        
        g_free(id_cours);
    }
}
void on_recherchercourssportif_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ent_courssportif");
    GtkWidget *entry = lookup_widget(window, "abcourssportif");
    GtkWidget *treeview = lookup_widget(window, "treeviewcourssportif");
    
    const gchar *id_recherche = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (!treeview) {
        g_print("TreeView introuvable!\n");
        return;
    }
    
    initialiser_treeview_cours(GTK_TREE_VIEW(treeview));
    
    if (strlen(id_recherche) > 0) {
        // Rechercher un cours spécifique
        Cours *c = rechercher_cours((char*)id_recherche);
        
        if (c) {
            GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
            gtk_list_store_clear(store);
            
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, c->id,
                              1, c->nom,
                              2, c->entraineur,
                              3, c->date,
                              4, c->heure,
                              5, c->duree,
                              6, c->centre,
                              7, c->niveau,
                              8, c->inscrits,
                              -1);
            free(c);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Cours non trouvé!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // Afficher tous les cours
        afficher_tous_les_cours(GTK_TREE_VIEW(treeview));
    }
}
void initialiser_treeview_equipment(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // Supprimer les anciennes colonnes
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *l = columns; l != NULL; l = l->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(l->data));
    }
    g_list_free(columns);
    
    // Créer le modèle (même structure que equipment.c)
    GtkListStore *store = gtk_list_store_new(5,
                                             G_TYPE_STRING,  // ID equipment
                                             G_TYPE_STRING,  // Nom
                                             G_TYPE_INT,     // Quantité
                                             G_TYPE_STRING,  // Disponible
                                             G_TYPE_STRING); // État
    
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Colonnes
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID Equipment", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Quantité", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Disponible", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("État", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);
}
void afficher_tous_les_equipments_ent(GtkTreeView *treeview)
{
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) return;
    
    gtk_list_store_clear(store);
    
    FILE *f = fopen("equipment.txt", "r");
    if (!f) {
        g_print("Erreur: impossible d'ouvrir equipment.txt\n");
        return;
    }
    
    agent a;
    GtkTreeIter iter;
    
    // Format: idag nom_ag quantite.jj disponible etat
    while (fscanf(f, "%s %s %d %s %s\n", 
                  a.idag, a.nom_ag, &a.Quantite.jj, a.Disponible, a.etat) != EOF) {
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, a.idag,
                          1, a.nom_ag,
                          2, a.Quantite.jj,
                          3, a.Disponible,
                          4, a.etat,
                          -1);
    }
    
    fclose(f);
}
int acheter_equipment_ent(char *id_equipment, int quantite_demandee)
{
    FILE *f = fopen("equipment.txt", "r");
    FILE *ft = fopen("temp.txt", "w");
    
    if (!f || !ft) {
        if (f) fclose(f);
        if (ft) fclose(ft);
        return -1; // Erreur fichier
    }
    
    agent a;
    int trouve = 0;
    int stock_insuffisant = 0;
    
    while (fscanf(f, "%s %s %d %s %s\n", 
                  a.idag, a.nom_ag, &a.Quantite.jj, a.Disponible, a.etat) != EOF) {
        
        if (strcmp(a.idag, id_equipment) == 0) {
            trouve = 1;
            
            if (a.Quantite.jj < quantite_demandee) {
                stock_insuffisant = 1;
                // Réécrire sans modification
                fprintf(ft, "%s %s %d %s %s\n", a.idag, a.nom_ag, a.Quantite.jj, a.Disponible, a.etat);
            } else {
                // Déduire la quantité
                a.Quantite.jj -= quantite_demandee;
                
                // Mettre à jour "Disponible" si stock = 0
                if (a.Quantite.jj == 0) {
                    strcpy(a.Disponible, "Non");
                }
                
                fprintf(ft, "%s %s %d %s %s\n", a.idag, a.nom_ag, a.Quantite.jj, a.Disponible, a.etat);
            }
        } else {
            fprintf(ft, "%s %s %d %s %s\n", a.idag, a.nom_ag, a.Quantite.jj, a.Disponible, a.etat);
        }
    }
    
    fclose(f);
    fclose(ft);
    
    if (!trouve) {
        remove("temp.txt");
        return 0; // Equipment non trouvé
    }
    
    if (stock_insuffisant) {
        remove("temp.txt");
        return -2; // Stock insuffisant
    }
    
    remove("equipment.txt");
    rename("temp.txt", "equipment.txt");
    return 1; // Achat réussi
}
void on_treeviewequipment_row_activated(GtkTreeView *treeview,
                                        GtkTreePath *path,
                                        GtkTreeViewColumn *column,
                                        gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(treeview), "ent_equipment");
    GtkWidget *entry_quantite = lookup_widget(window, "abquantite");
    
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    gchar *id_equipment;
    gint stock_actuel;
    
    if (!entry_quantite) {
        g_print("Entry quantité introuvable!\n");
        return;
    }
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 
                          0, &id_equipment,
                          2, &stock_actuel,
                          -1);
        
        const gchar *quantite_text = gtk_entry_get_text(GTK_ENTRY(entry_quantite));
        int quantite_demandee = atoi(quantite_text);
        
        if (quantite_demandee <= 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Veuillez entrer une quantité valide!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            g_free(id_equipment);
            return;
        }
        
        int resultat = acheter_equipment_ent(id_equipment, quantite_demandee);
        
        if (resultat == 1) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Achat réussi! %d unité(s) de %s", 
                                                       quantite_demandee, id_equipment);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            
            // Vider l'entry
            gtk_entry_set_text(GTK_ENTRY(entry_quantite), "");
            
            // Rafraîchir le treeview
            initialiser_treeview_equipment(treeview);
            afficher_tous_les_equipments_ent(treeview);
        } 
        else if (resultat == -2) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Stock insuffisant! Stock actuel: %d", stock_actuel);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else if (resultat == 0) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Équipement non trouvé!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Erreur lors de l'achat!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        
        g_free(id_equipment);
    }
}





void on_rechercherequipment_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ent_equipment");
    GtkWidget *entry = lookup_widget(window, "abequipment");
    GtkWidget *treeview = lookup_widget(window, "treeviewequipment");
    
    if (!treeview) {
        g_print("TreeView introuvable!\n");
        return;
    }
    
    initialiser_treeview_equipment(GTK_TREE_VIEW(treeview));
    
    const gchar *id_recherche = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strlen(id_recherche) > 0) {
        // Utiliser la fonction existante
        agent *a = chercherequipment((char*)id_recherche);
        
        if (a) {
            GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
            gtk_list_store_clear(store);
            
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                              0, a->idag,
                              1, a->nom_ag,
                              2, a->Quantite.jj,
                              3, a->Disponible,
                              4, a->etat,
                              -1);
            free(a);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Équipement non trouvé!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // Afficher tous les équipements
        afficher_tous_les_equipments_ent(GTK_TREE_VIEW(treeview));
    }
}
void initialiser_treeview_centre(GtkTreeView *treeview)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    
    // Supprimer les anciennes colonnes
    GList *columns = gtk_tree_view_get_columns(treeview);
    for (GList *l = columns; l != NULL; l = l->next) {
        gtk_tree_view_remove_column(treeview, GTK_TREE_VIEW_COLUMN(l->data));
    }
    g_list_free(columns);
    
    // Créer le modèle
    GtkListStore *store = gtk_list_store_new(6,
                                             G_TYPE_STRING,  // ID
                                             G_TYPE_STRING,  // Nom
                                             G_TYPE_STRING,  // Adresse
                                             G_TYPE_STRING,  // Ville
                                             G_TYPE_INT,     // Capacité
                                             G_TYPE_STRING); // Type
    
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // Colonnes
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(treeview, column);
    
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(treeview, column);
}
void afficher_tous_les_centres(GtkTreeView *treeview)
{
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
    if (!store) return;
    
    gtk_list_store_clear(store);
    
    FILE *f = fopen("centres.txt", "r");
    if (!f) {
        g_print("Erreur: impossible d'ouvrir centres.txt\n");
        return;
    }
    
    char id[20], nom[50], adresse[100], ville[50], type[50];
    int capacite;
    GtkTreeIter iter;
    
    // Format: id|nom|adresse|ville|capacite|type
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
                  id, nom, adresse, ville, &capacite, type) != EOF) {
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                          0, id,
                          1, nom,
                          2, adresse,
                          3, ville,
                          4, capacite,
                          5, type,
                          -1);
    }
    
    fclose(f);
}
int inscrire_centre(char *id_centre, char *id_entraineur)
{
    // Vérifier si le centre existe
    FILE *f = fopen("centres.txt", "r");
    if (!f) return 0;
    
    char id[20], nom[50], adresse[100], ville[50], type[50];
    int capacite;
    int centre_existe = 0;
    
    while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
                  id, nom, adresse, ville, &capacite, type) != EOF) {
        if (strcmp(id, id_centre) == 0) {
            centre_existe = 1;
            break;
        }
    }
    fclose(f);
    
    if (!centre_existe) return 0;
    
    // Vérifier si déjà inscrit
    FILE *fi = fopen("inscriptions_centres.txt", "r");
    if (fi) {
        char id_c[20], id_e[20];
        while (fscanf(fi, "%[^|]|%[^\n]\n", id_c, id_e) != EOF) {
            if (strcmp(id_c, id_centre) == 0 && strcmp(id_e, id_entraineur) == 0) {
                fclose(fi);
                return -1; // Déjà inscrit
            }
        }
        fclose(fi);
    }
    
    // Ajouter l'inscription
    fi = fopen("inscriptions_centres.txt", "a");
    if (fi) {
        fprintf(fi, "%s|%s\n", id_centre, id_entraineur);
        fclose(fi);
        return 1; // Succès
    }
    
    return 0;
}
void on_treeviewcentre_row_activated(GtkTreeView *treeview,
                                     GtkTreePath *path,
                                     GtkTreeViewColumn *column,
                                     gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(treeview), "ent_centresportif");
    
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    GtkTreeIter iter;
    gchar *id_centre;
    gchar *nom_centre;
    
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter, 
                          0, &id_centre,
                          1, &nom_centre,
                          -1);
        
        // ID de l'entraineur connecté (à récupérer depuis la session)
        char id_entraineur[20] = "entraineur1"; // Exemple
        
        int resultat = inscrire_centre(id_centre, id_entraineur);
        
        if (resultat == 1) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Inscription réussie au centre %s!", nom_centre);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } 
        else if (resultat == -1) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_WARNING,
                                                       GTK_BUTTONS_OK,
                                                       "Vous êtes déjà inscrit à ce centre!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        else {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Échec de l'inscription!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        
        g_free(id_centre);
        g_free(nom_centre);
    }
}
void on_recherchercentre_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window = lookup_widget(GTK_WIDGET(button), "ent_centresportif");
    GtkWidget *entry = lookup_widget(window, "abcentresportif");
    GtkWidget *treeview = lookup_widget(window, "treeviewcentre");
    
    if (!treeview) {
        g_print("TreeView introuvable!\n");
        return;
    }
    
    initialiser_treeview_centre(GTK_TREE_VIEW(treeview));
    
    const gchar *id_recherche = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (strlen(id_recherche) > 0) {
        // Rechercher un centre spécifique
        FILE *f = fopen("centres.txt", "r");
        if (!f) {
            g_print("Erreur: impossible d'ouvrir centres.txt\n");
            return;
        }
        
        char id[20], nom[50], adresse[100], ville[50], type[50];
        int capacite;
        int trouve = 0;
        
        GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
        gtk_list_store_clear(store);
        
        while (fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%[^\n]\n",
                      id, nom, adresse, ville, &capacite, type) != EOF) {
            
            if (strcmp(id, id_recherche) == 0) {
                trouve = 1;
                GtkTreeIter iter;
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                  0, id,
                                  1, nom,
                                  2, adresse,
                                  3, ville,
                                  4, capacite,
                                  5, type,
                                  -1);
                break;
            }
        }
        
        fclose(f);
        
        if (!trouve) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_ERROR,
                                                       GTK_BUTTONS_OK,
                                                       "Centre non trouvé!");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        // Afficher tous les centres
        afficher_tous_les_centres(GTK_TREE_VIEW(treeview));
    }
}

void on_retourge_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_admin;
    
    gtk_widget_destroy(window_current);
    
    window_admin = create_Espace_Admin();
    gtk_widget_show(window_admin);
}
void on_retourcours_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_entraineur;
    
    gtk_widget_destroy(window_current);
    
    window_entraineur = create_Espace_Entraineur();
    gtk_widget_show(window_entraineur);
}
void on_retourequipment_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_entraineur;
    
    gtk_widget_destroy(window_current);
    
    window_entraineur = create_Espace_Entraineur();
    gtk_widget_show(window_entraineur);
}
void on_retourcentres_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *window_current = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *window_entraineur;
    
    gtk_widget_destroy(window_current);
    
    window_entraineur = create_Espace_Entraineur();
    gtk_widget_show(window_entraineur);
}


