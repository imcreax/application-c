#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"
#include "inscription.h"

int ouvert_weekend = 0;
int parking_disponible = 0;
char type[10] = "";


void
on_im_modifier_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle

    GtkWidget *modif_window = create_imen_bm_Modifier(); // Ouvre la fenêtre Modifier
    gtk_widget_show(modif_window);

}


void
on_im_supprimer_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);

    GtkWidget *suppr_window = create_imen_bm_Supprimer(); // Ouvre la fenêtre Supprimer
    gtk_widget_show(suppr_window);

}


void
on_im_rechercher_button_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);

    GtkWidget *rech_window = create_imen_bm_Rechercher(); // Ouvre la fenêtre Rechercher
    gtk_widget_show(rech_window);

}


void
on_im_stat_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);

    GtkWidget *stats_window = create_imen_bm_Statistiques_Filtrees(); // Ouvre la fenêtre Statistiques
    gtk_widget_show(stats_window);

}


void
on_im_retour_gc_button_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_Espace_Admin(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);


}


void
on_im_ajouter_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);

    GtkWidget *ajout_window = create_imen_bm_Ajouter(); // Ouvre la fenêtre Ajouter
    gtk_widget_show(ajout_window);

}


void
on_im_ajout_checkbutton1_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        ouvert_weekend = TRUE;
        g_print("Ouvert le week-end : Oui\n");
    } else {
        ouvert_weekend = FALSE;
        g_print("Ouvert le week-end : Non\n");
    }

}


void
on_im_ajout_checkbutton2_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        parking_disponible = TRUE;
        g_print("Parking disponible : Oui\n");
    } else {
        parking_disponible = FALSE;
        g_print("Parking disponible : Non\n");
    }
}


void
on_im_ajout_radiobutton1_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(type, "public");
        g_print("Type sélectionné : %s\n", type);
    }
}


void
on_im_ajout_radiobutton2_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(type, "privé");
        g_print("Type sélectionné : %s\n", type);
    }
}


void
on_im_enrigistrer_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération des widgets
    GtkWidget *entry_id       = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry");
    GtkWidget *entry_nom      = lookup_widget(GTK_WIDGET(button), "im_nom_entry");
    GtkWidget *entry_adresse  = lookup_widget(GTK_WIDGET(button), "im_adresse_entry");
    GtkWidget *entry_tel      = lookup_widget(GTK_WIDGET(button), "im_telephone_entry");
    GtkWidget *entry_email    = lookup_widget(GTK_WIDGET(button), "im_email_entry");
    GtkWidget *combo_ville    = lookup_widget(GTK_WIDGET(button), "im_ville_combobox");
    GtkWidget *spin_capacite  = lookup_widget(GTK_WIDGET(button), "im_capacite_spinbutton"); // corrigé
    GtkWidget *chk_weekend    = lookup_widget(GTK_WIDGET(button), "im_ajout_checkbutton1");
    GtkWidget *chk_parking    = lookup_widget(GTK_WIDGET(button), "im_ajout_checkbutton2");
    GtkWidget *rb_prive       = lookup_widget(GTK_WIDGET(button), "im_ajout_radiobutton1");

    // Buffers pour les champs texte
    char id_buf[20];
    char nom_buf[50];
    char adresse_buf[100];
    char tel_buf[20];
    char email_buf[50];
    char ville_buf[50];

    // Récupération des valeurs dans les buffers
    strncpy(id_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)), sizeof(id_buf) - 1);
    id_buf[sizeof(id_buf) - 1] = '\0';

    strncpy(nom_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_nom)), sizeof(nom_buf) - 1);
    nom_buf[sizeof(nom_buf) - 1] = '\0';

    strncpy(adresse_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_adresse)), sizeof(adresse_buf) - 1);
    adresse_buf[sizeof(adresse_buf) - 1] = '\0';

    strncpy(tel_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_tel)), sizeof(tel_buf) - 1);
    tel_buf[sizeof(tel_buf) - 1] = '\0';

    strncpy(email_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_email)), sizeof(email_buf) - 1);
    email_buf[sizeof(email_buf) - 1] = '\0';

    GtkEntry *entry_ville = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_ville)));
    strncpy(ville_buf, (char*) gtk_entry_get_text(entry_ville), sizeof(ville_buf) - 1);
    ville_buf[sizeof(ville_buf) - 1] = '\0';

    // Vérification des champs
    if (strlen(id_buf) == 0 || strlen(nom_buf) == 0 || strlen(adresse_buf) == 0 ||
        strlen(ville_buf) == 0 || strlen(tel_buf) == 0 || strlen(email_buf) == 0 ||
        !valider_telephone(tel_buf) || !valider_email(email_buf)) {

        GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error_ajouter");
        gtk_widget_show(dialog);
        return;
    }

    // Construction de la structure Centre
    Centre c;
    c.id = atoi(id_buf);
    strcpy(c.nom, nom_buf);
    strcpy(c.adresse, adresse_buf);
    strcpy(c.ville, ville_buf);
    strcpy(c.telephone, tel_buf);
    strcpy(c.email, email_buf);
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    c.ouvert_weekend = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk_weekend)) ? 1 : 0;
    c.parking_disponible = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk_parking)) ? 1 : 0;
    c.type = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_prive)) ? 0 : 1;

    // Ajout du centre
    ajouterCentre(c);

    // Affichage automatique dans la TreeView
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");
    afficher_centre_dans_treeview(treeview, c);

    // Message de confirmation
    GtkWidget *msg1 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_1");
    gtk_widget_show(msg1);
}




void
on_im_annuler_ajout_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération des widgets
    GtkWidget *entry_id      = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry");
    GtkWidget *entry_nom     = lookup_widget(GTK_WIDGET(button), "im_nom_entry");
    GtkWidget *entry_adresse = lookup_widget(GTK_WIDGET(button), "im_adresse_entry");
    GtkWidget *entry_tel     = lookup_widget(GTK_WIDGET(button), "im_telephone_entry");
    GtkWidget *entry_email   = lookup_widget(GTK_WIDGET(button), "im_email_entry");

    // Réinitialisation des champs
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
    gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");

    g_print("Action annulée, champs réinitialisés.\n");
}


void
on_im_retour_ajout_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_imen_bm_Gestion_des_centres(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);
}


void
on_im_rechercher_modif_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération du champ ID
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "im_id_modif");

    // Buffer pour l’ID
    char id_buf[50];
    strcpy(id_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Conversion en entier
    int identifiant = atoi(id_buf);

    // Recherche du centre
    Centre c = rechercherCentre(identifiant);

    // Vérification et affichage
    if (c.id != -1) {
        GtkWidget *entry_nom     = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
        GtkWidget *entry_adresse = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
        GtkWidget *entry_tel     = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
        GtkWidget *entry_email   = lookup_widget(GTK_WIDGET(button), "im_email_modif");

        gtk_entry_set_text(GTK_ENTRY(entry_nom), c.nom);
        gtk_entry_set_text(GTK_ENTRY(entry_adresse), c.adresse);
        gtk_entry_set_text(GTK_ENTRY(entry_tel), c.telephone);
        gtk_entry_set_text(GTK_ENTRY(entry_email), c.email);

        g_print("Centre trouvé et affiché.\n");
    } else {
        g_print("Centre introuvable.\n");
    }
}


void
on_im_modif_checkbutton1_clicked       (GtkToggleButton       *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        ouvert_weekend = TRUE;
        g_print("Ouvert le week-end : Oui\n");
    } else {
        ouvert_weekend = FALSE;
        g_print("Ouvert le week-end : Non\n");
    }

}


void
on_im_modif_checkbutton2_clicked       (GtkToggleButton       *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        parking_disponible = TRUE;
        g_print("Parking disponible : Oui\n");
    } else {
        parking_disponible = FALSE;
        g_print("Parking disponible : Non\n");
    }
}


void
on_im_modif_radiobutton1_clicked       (GtkToggleButton       *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(type, "public");
        g_print("Type sélectionné : %s\n", type);
    }
}


void
on_im_modif_radiobutton2_clicked       (GtkToggleButton       *togglebutton,
                                        gpointer         user_data)
{
    if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(type, "privé");
        g_print("Type sélectionné : %s\n", type);
    }
}


void
on_im_mettreajour_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération des widgets
    GtkWidget *entry_id       = lookup_widget(GTK_WIDGET(button), "im_id_modif");
    GtkWidget *entry_nom      = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
    GtkWidget *entry_adresse  = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
    GtkWidget *entry_tel      = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
    GtkWidget *entry_email    = lookup_widget(GTK_WIDGET(button), "im_email_modif");
    GtkWidget *combo_ville    = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_modif");
    GtkWidget *spin_capacite  = lookup_widget(GTK_WIDGET(button), "im_capacite_modif");
    GtkWidget *chk_weekend    = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton1");
    GtkWidget *chk_parking    = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton2");
    GtkWidget *rb_prive       = lookup_widget(GTK_WIDGET(button), "im_modif_radiobutton1");

    // Buffers pour les champs texte
    char id_buf[20];
    char nom_buf[50];
    char adresse_buf[100];
    char tel_buf[20];
    char email_buf[50];
    char ville_buf[50];

    // Récupération des valeurs dans les buffers
    strcpy(id_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)));
    strcpy(nom_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_nom)));
    strcpy(adresse_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_adresse)));
    strcpy(tel_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_tel)));
    strcpy(email_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_email)));

    GtkEntry *entry_ville = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_ville)));
    strcpy(ville_buf, (char*) gtk_entry_get_text(entry_ville));

    // Vérification des champs
    if (strlen(id_buf) == 0 || strlen(nom_buf) == 0 || strlen(adresse_buf) == 0 ||
        strlen(ville_buf) == 0 || strlen(tel_buf) == 0 || strlen(email_buf) == 0 ||
        !valider_telephone(tel_buf) || !valider_email(email_buf)) {

        GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error_ajouter");
        gtk_widget_show(dialog);
        return;
    }

    // Construction de la structure Centre
    Centre c;
    c.id = atoi(id_buf);
    strcpy(c.nom, nom_buf);
    strcpy(c.adresse, adresse_buf);
    strcpy(c.ville, ville_buf);
    strcpy(c.telephone, tel_buf);
    strcpy(c.email, email_buf);
    c.capacite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_capacite));
    c.ouvert_weekend = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk_weekend)) ? 1 : 0;
    c.parking_disponible = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chk_parking)) ? 1 : 0;
    c.type = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(rb_prive)) ? 0 : 1;

    // Mise à jour du centre
    modifierCentre(c);

    // Affichage du message de confirmation
    GtkWidget *message = lookup_widget(GTK_WIDGET(button), "imen_bm_message_6");
    gtk_widget_show(message);
}




void
on_im_annuler_modif_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entry_id      = lookup_widget(GTK_WIDGET(button), "im_id_modif");
    GtkWidget *entry_nom     = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
    GtkWidget *entry_adresse = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
    GtkWidget *entry_tel     = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
    GtkWidget *entry_email   = lookup_widget(GTK_WIDGET(button), "im_email_modif");

    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_nom), "");
    gtk_entry_set_text(GTK_ENTRY(entry_adresse), "");
    gtk_entry_set_text(GTK_ENTRY(entry_tel), "");
    gtk_entry_set_text(GTK_ENTRY(entry_email), "");

    g_print("Action annulée, champs réinitialisés.\n");

}


void
on_im_retour_modif_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_imen_bm_Gestion_des_centres(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);
}


void
on_im_supprimer_supp_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération du champ ID
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "im_id_supp_entry");

    // Buffer pour l’ID
    char id_buf[50];
    strcpy(id_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)));

    // Vérification du champ vide
    if (strlen(id_buf) == 0) {
        GtkWidget *dialog_err = lookup_widget(GTK_WIDGET(button), "imen_bm_message_7");
        gtk_widget_show(dialog_err);
        return;
    }

    // Affichage du message de confirmation
    GtkWidget *dialog_conf = lookup_widget(GTK_WIDGET(button), "imen_bm_Message_de_confirmation");
    gtk_widget_show(dialog_conf);

    // La suppression sera déclenchée après confirmation (OK/Cancel)
}



void
on_im_retour_supp_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_imen_bm_Gestion_des_centres(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);
}


void
on_im_rechercher_rech_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération du champ ID
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "im_id_recherche_entry");

    // Conversion de l’ID en entier
    char id_buf[20];
    strcpy(id_buf, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)));
    int id = atoi(id_buf);

    // Recherche du centre
    Centre c = rechercherCentre(id);

    // Récupération de la TreeView
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");

    // Nettoyage de la TreeView
    vider_treeview(treeview);

    // Affichage du centre s’il est trouvé
    if (c.id != -1) {
        afficher_centre_dans_treeview(treeview, c);
        g_print("Centre trouvé et affiché.\n");
    } else {
        g_print("Centre introuvable.\n");
    }
}




void
on_treeview1_row_activated(GtkTreeView *treeview,
                           GtkTreePath *path,
                           GtkTreeViewColumn *column,
                           gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    Centre c;

    gchar *nom, *adresse, *ville, *tel, *email, *type;
    gint capacite;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter,
                           0, &c.id,
                           1, &nom,
                           2, &adresse,
                           3, &ville,
                           4, &tel,
                           5, &email,
                           6, &capacite,
                           9, &type,
                           -1);

        // Remplissage de la structure
        strcpy(c.nom, nom);
        strcpy(c.adresse, adresse);
        strcpy(c.ville, ville);
        strcpy(c.telephone, tel);
        strcpy(c.email, email);
        c.capacite = capacite;
        c.type = (strcmp(type, "Privé") == 0) ? 0 : 1;

        // Suppression du centre
        supprimerCentre(c.id);

        // Mise à jour de l’affichage
        GtkWidget *treeview1 = lookup_widget(GTK_WIDGET(treeview), "treeview1");
        vider_treeview(treeview1);
        afficher_tous_les_centres(treeview1);
    }
}



void
on_im_export_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");
    exporter_resultats_vers_fichier(treeview);
    g_print("Résultats exportés.\n");
}




void
on_im_paratger_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");
    partager_resultats(treeview);
    g_print("Résultats partagés.\n");
}



void
on_im_retour_recherche_button_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_imen_bm_Gestion_des_centres(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);
}

void on_treeview2_row_activated(GtkTreeView     *treeview,
                                GtkTreePath     *path,
                                GtkTreeViewColumn *column,
                                gpointer         user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    gchar *nom, *adresse, *ville, *tel, *email, *type;
    gint capacite;

    // Vérifier si une ligne est activée (double clic)
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Récupérer les valeurs de la ligne sélectionnée
        gtk_tree_model_get(model, &iter,
                           0, &nom,
                           1, &adresse,
                           2, &ville,
                           3, &tel,
                           4, &email,
                           5, &capacite,
                           6, &type,
                           -1);

        // Ici, on ne supprime pas : on exploite les données
        g_print("Centre sélectionné : %s, %s, %s, %s, %s, Capacité=%d, Type=%s\n",
                nom, adresse, ville, tel, email, capacite, type);

        // Tu peux stocker ces infos dans une variable globale ou fichier temporaire
        // pour que le bouton \"S'inscrire\" les utilise ensuite.
    }
}

void
on_im_annuler_inscri_button_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    gtk_tree_selection_unselect_all(selection);
    g_print("Sélection annulée.\n");

}


void
on_im_retour_inscri_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window); // Ferme la fenêtre actuelle
    GtkWidget *main_window = create_Espace_Entraineur(); // Retour à la fenêtre principale
    gtk_widget_show(main_window);
}


void
on_im_inscri_button_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *combo_ville = lookup_widget(GTK_WIDGET(button), "im_inscri_ville_combobox");
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");

    char ville[50];
    GtkEntry *entry_ville = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_ville)));
    strncpy(ville, gtk_entry_get_text(entry_ville), sizeof(ville) - 1);
    ville[sizeof(ville) - 1] = '\0';

    // Vider et afficher les centres de la ville sélectionnée
    vider_treeview(treeview);

    FILE *f = fopen("centres.txt", "r");
    if (f == NULL) return;

    Centre c;
    GtkListStore *store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    GtkTreeIter iter;
    char ligne[512];

    while (fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d;%49[^;];%99[^;];%49[^;];%19[^;];%49[^;];%d;%d;%d;%d",
                   &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                   &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) == 10) {

            if (strcmp(c.ville, ville) == 0) {
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   0, c.nom,
                                   1, c.adresse,
                                   2, c.ville,
                                   3, c.telephone,
                                   4, c.email,
                                   5, c.capacite,
                                   6, (c.type == 0 ? "Privé" : "Public"),
                                   -1);
            }
        }
    }

    fclose(f);

    // Récupérer la ligne sélectionnée
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    if (gtk_tree_selection_get_selected(selection, NULL, &iter)) {
        gchar *nom, *ville_sel;
        gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &nom, 2, &ville_sel, -1);
        g_print("Inscription validée au centre : %s (%s)\n", nom, ville_sel);
        // Tu peux ici enregistrer l’inscription dans un fichier
    } else {
        g_print("Aucune ligne sélectionnée.\n");
    }


}


void
on_im_stat_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data)
{
    gboolean actif = gtk_toggle_button_get_active(togglebutton);
    g_print("Ouvert le week-end : %s\n", actif ? "Oui" : "Non");

    // Tu peux ici mettre à jour une variable globale ou relancer un filtrage
}



void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
    Centre c;

    gchar *nom, *adresse, *ville, *tel, *email, *type;
    gint capacite;

    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gtk_tree_model_get(model, &iter,
                           0, &nom,
                           1, &adresse,
                           2, &ville,
                           3, &tel,
                           4, &email,
                           5, &capacite,
                           6, &type,
                           -1);

        strcpy(c.nom, nom);
        strcpy(c.adresse, adresse);
        strcpy(c.ville, ville);
        strcpy(c.telephone, tel);
        strcpy(c.email, email);
        c.capacite = capacite;
        c.type = (strcmp(type, "Privé") == 0) ? 0 : 1;

        g_print("Centre sélectionné : %s (%s), Capacité : %d, Type : %s\n",
                c.nom, c.ville, c.capacite, type);

        // Tu peux stocker c dans une variable globale pour l’utiliser dans "S’inscrire"
    }

}


void
on_im_stat_checkbutton1_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
    gboolean actif = gtk_toggle_button_get_active(togglebutton);
    g_print("Parking disponible : %s\n", actif ? "Oui" : "Non");

    // Tu peux ici mettre à jour une variable globale ou relancer un filtrage


}


void
on_im_appliquer_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupération des widgets
    GtkWidget *combo_ville      = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_stat");
    GtkWidget *combo_type       = lookup_widget(GTK_WIDGET(button), "im_type_combobox_stat");
    GtkWidget *spin_min         = lookup_widget(GTK_WIDGET(button), "im_cmin_entry");
    GtkWidget *spin_max         = lookup_widget(GTK_WIDGET(button), "im_cmax_entry");
    GtkWidget *check_parking    = lookup_widget(GTK_WIDGET(button), "im_stat_checkbutton1");
    GtkWidget *check_weekend    = lookup_widget(GTK_WIDGET(button), "im_stat_checkbutton2"); // corrigé ici
    GtkWidget *combo_acces      = lookup_widget(GTK_WIDGET(button), "im_type2_combobox_stat");

    GtkWidget *treeview3        = lookup_widget(GTK_WIDGET(button), "treeview3"); // ajouté
    GtkWidget *label_total      = lookup_widget(GTK_WIDGET(button), "im_tot_label");
    GtkWidget *label_moyenne    = lookup_widget(GTK_WIDGET(button), "im_moy_label");
    GtkWidget *label_parking    = lookup_widget(GTK_WIDGET(button), "im_pourc_park_label");
    GtkWidget *label_weekend    = lookup_widget(GTK_WIDGET(button), "im_pourc_ouvert_label");

    // Récupération des valeurs
    char ville[50], type[20], acces[20];
    GtkEntry *entry_ville = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_ville)));
    GtkEntry *entry_type  = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_type)));
    GtkEntry *entry_acces = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo_acces)));

    strncpy(ville, (char*) gtk_entry_get_text(entry_ville), sizeof(ville) - 1);
    ville[sizeof(ville) - 1] = '\0';

    strncpy(type, (char*) gtk_entry_get_text(entry_type), sizeof(type) - 1);
    type[sizeof(type) - 1] = '\0';

    strncpy(acces, (char*) gtk_entry_get_text(entry_acces), sizeof(acces) - 1);
    acces[sizeof(acces) - 1] = '\0';

    int capacite_min = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_min));
    int capacite_max = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_max));
    int parking       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_parking));
    int weekend       = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_weekend));

    // Initialisation des compteurs
    int total = 0, somme = 0, avec_parking = 0, ouvert_weekend = 0;
    GtkListStore *store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    GtkTreeIter iter;

    FILE *f = fopen("centres.txt", "r");
    if (f == NULL) return;

    Centre c;
    char ligne[512];

    while (fgets(ligne, sizeof(ligne), f)) {
        if (sscanf(ligne, "%d;%49[^;];%99[^;];%49[^;];%19[^;];%49[^;];%d;%d;%d;%d",
                   &c.id, c.nom, c.adresse, c.ville, c.telephone, c.email,
                   &c.capacite, &c.ouvert_weekend, &c.parking_disponible, &c.type) == 10) {

            // Filtrage
            if ((strlen(ville) == 0 || strcmp(c.ville, ville) == 0) &&
                (strlen(type) == 0 || ((strcmp(type, "Privé") == 0 && c.type == 0) || (strcmp(type, "Public") == 0 && c.type == 1))) &&
                (c.capacite >= capacite_min && c.capacite <= capacite_max) &&
                (!parking || c.parking_disponible == 1) &&
                (!weekend || c.ouvert_weekend == 1)) {

                // Ajout dans la TreeView
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter,
                                   0, c.ville,
                                   1, c.nom,
                                   2, (c.type == 0 ? "Privé" : "Public"),
                                   -1);

                // Statistiques
                total++;
                somme += c.capacite;
                if (c.parking_disponible) avec_parking++;
                if (c.ouvert_weekend) ouvert_weekend++;
            }
        }
    }

    fclose(f);

    // Affichage dans la TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview3), GTK_TREE_MODEL(store));

    // Affichage des statistiques
    char buf[50];
    sprintf(buf, "%d", total);
    gtk_label_set_text(GTK_LABEL(label_total), buf);

    sprintf(buf, "%d", (total > 0 ? somme / total : 0));
    gtk_label_set_text(GTK_LABEL(label_moyenne), buf);

    sprintf(buf, "%.1f %%", (total > 0 ? (avec_parking * 100.0 / total) : 0));
    gtk_label_set_text(GTK_LABEL(label_parking), buf);

    sprintf(buf, "%.1f %%", (total > 0 ? (ouvert_weekend * 100.0 / total) : 0));
    gtk_label_set_text(GTK_LABEL(label_weekend), buf);
}



void
on_msg1_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg1 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_1");
    gtk_widget_hide(msg1);


}


void
on_msg2_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg2 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_2");
    gtk_widget_hide(msg2);

}


void
on_msg3_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg3 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_3");
    gtk_widget_hide(msg3);

}


void
on_error_id_cancel_button_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error");
    gtk_widget_destroy(dialog);
    g_print("Fenêtre d’erreur fermée sans action.\n");
   
}


void
on_error_id_ok_button_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    // Fermer la boîte de dialogue
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error");
    gtk_widget_destroy(dialog);


    g_print("Action confirmée : champs réinitialisés.\n");


}


void
on_confirmer_cancel_button_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Message_de_confirmation");
    gtk_widget_destroy(dialog);
    g_print("Suppression annulée.\n");

  
}


void
on_confirmer_ok_button_clicked(GtkButton *button, gpointer user_data)
{
    // Récupérer l’ID depuis le champ de saisie
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "im_id_supp_entry");
    char id[50];
    strncpy(id, (char*) gtk_entry_get_text(GTK_ENTRY(entry_id)), sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    // Fermer la boîte de confirmation
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Message_de_confirmation");
    gtk_widget_destroy(dialog);

    // Vérifier si l’ID est vide
    if (strlen(id) == 0) {
        GtkWidget *msg7 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_7");
        gtk_widget_show(msg7);
        return;
    }

    // Supprimer le centre avec la fonction de centre.h
    int identifiant = atoi(id);
    supprimerCentre(identifiant);

    g_print("Centre %d supprimé avec succès.\n", identifiant);

    // Vider le champ
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");

    // Mettre à jour l’affichage
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview1");
    vider_treeview(treeview);
    afficher_tous_les_centres(treeview);
}




void
on_error_ajout_cancel_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error_ajouter");
    gtk_widget_destroy(dialog);
    g_print("Erreur ignorée, boîte fermée.\n");
}



void
on_error_ajout_ok_button_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    // Fermer la boîte de dialogue
    GtkWidget *dialog = lookup_widget(GTK_WIDGET(button), "imen_bm_Error_ajouter");
    gtk_widget_destroy(dialog);


    g_print("Champs réinitialisés après erreur.\n");


}


void
on_msg4_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg4 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_4");
    gtk_widget_hide(msg4);

}


void
on_msg5_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg5 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_5");
    gtk_widget_hide(msg5);

}


void
on_msg6_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg6 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_6");
    gtk_widget_hide(msg6);

}


void
on_msg7_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *msg7 = lookup_widget(GTK_WIDGET(button), "imen_bm_message_7");
    gtk_widget_hide(msg7);

}



