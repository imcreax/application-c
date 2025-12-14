/*
 * Callbacks implementation with standard GTK dialogs
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"
#include "inscription.h"
#include "utilisateur.h"


// Variables globales
int ouvert_weekend = 0;
int parking_disponible = 0;
char type[10] = "";
int selected_centre_id = -1;
int filtre_parking = -1;
int filtre_weekend = -1;

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
/* ========== CALLBACKS ESPACE ADMIN ========== */
void on_g_membre_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Gestion des membres à implémenter");
}

void on_g_entraineur_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Gestion des entraîneurs à implémenter");
}

void on_g_cours_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Gestion des cours sportifs à implémenter");
}

void on_g_equipement_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Gestion des équipements à implémenter");
}

void on_g_centre_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *gestion_window = create_imen_bm_Gestion_des_centres();
    gtk_widget_show(gestion_window);
}

void on_g_evenement_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Gestion des événements à implémenter");
}

void on_im_retour_EA_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_destroy(current_window);
    gtk_main_quit();
}

/* ========== CALLBACKS ESPACE ENTRAINEUR ========== */
void on_inscri1_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Inscription cours sportif à implémenter");
}

void on_reserver_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    show_error_dialog(GTK_WIDGET(button), "Fonctionnalité Réservation équipements à implémenter");
}

void on_inscri2_ent_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *inscri_window = create_imen_bm_Inscription____un_centre();
    gtk_widget_show(inscri_window);
}

void on_im_retour_EE_button_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *current_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    gtk_widget_hide(current_window);
   
    GtkWidget *admin_window = create_Espace_Admin();
    gtk_widget_show(admin_window);
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
   // Vider tous les champs
    GtkWidget *input;
    
    input = lookup_widget(GTK_WIDGET(button), "im_id_centre_entry");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_nom_entry");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_adresse_entry");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_telephone_entry");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_email_entry");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_capacit___spinbutton");
    if (input) gtk_spin_button_set_value(GTK_SPIN_BUTTON(input), 0);
    
    // Réinitialiser les checkboxes
    input = lookup_widget(GTK_WIDGET(button), "im_ajout_checkbutton1");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), FALSE);
    
    input = lookup_widget(GTK_WIDGET(button), "im_ajout_checkbutton2");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), FALSE);
    
    // Réinitialiser les radio buttons (sélectionner "privé" par défaut)
    input = lookup_widget(GTK_WIDGET(button), "im_ajout_radiobutton1");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), TRUE);
    
    // Réinitialiser le combobox ville (index -1 = rien de sélectionné)
    input = lookup_widget(GTK_WIDGET(button), "im_ville_combobox");
    if (input) gtk_combo_box_set_active(GTK_COMBO_BOX(input), -1);
    
    // Réinitialiser les variables globales
    ouvert_weekend = 0;
    parking_disponible = 0;
    strcpy(type, "Prive");
    
    show_success_dialog(GTK_WIDGET(button), "Formulaire réinitialisé");

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
    // Vider tous les champs
    GtkWidget *input;
    
    input = lookup_widget(GTK_WIDGET(button), "im_id_modif");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_nom_modif");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_adresse_modif");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_tel_modif");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_email_modif");
    if (input) gtk_entry_set_text(GTK_ENTRY(input), "");
    
    input = lookup_widget(GTK_WIDGET(button), "im_capacite_modif");
    if (input) gtk_spin_button_set_value(GTK_SPIN_BUTTON(input), 0);
    
    // Réinitialiser les checkboxes
    input = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton1");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), FALSE);
    
    input = lookup_widget(GTK_WIDGET(button), "im_modif_checkbutton2");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), FALSE);
    
    // Réinitialiser les radio buttons
    input = lookup_widget(GTK_WIDGET(button), "im_modif_radiobutton1");
    if (input) gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(input), TRUE);
    
    // Réinitialiser le combobox ville
    input = lookup_widget(GTK_WIDGET(button), "im_ville_combobox_modif");
    if (input) gtk_combo_box_set_active(GTK_COMBO_BOX(input), -1);
    
    // Réinitialiser les variables globales
    ouvert_weekend = 0;
    parking_disponible = 0;
    strcpy(type, "Prive");
    
    show_success_dialog(GTK_WIDGET(button), "Formulaire réinitialisé");
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
   
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview3");
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
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview3");
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

void on_treeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(treeview);
   
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gint id;
        gtk_tree_model_get(model, &iter, 0, &id, -1);
        selected_centre_id = id;
    }
}

void on_treeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    on_treeview2_row_activated(treeview, path, column, user_data);
}

void on_treeview3_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    on_treeview2_row_activated(treeview, path, column, user_data);
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
    GtkWidget *input;
    
    // Réinitialiser le combobox ville
    input = lookup_widget(GTK_WIDGET(button), "im_inscri_ville_combobox");
    if (input) gtk_combo_box_set_active(GTK_COMBO_BOX(input), -1);
    
    // Vider le treeview
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview2");
    if (treeview) {
        vider_treeview(treeview);
    }
    
    // Réinitialiser la sélection
    selected_centre_id = -1;
    
    show_success_dialog(GTK_WIDGET(button), "Sélection annulée");
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
