/*
 * CALLBACKS.H - Header file for all callbacks
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>

/* ========== CALLBACKS FENÊTRE PRINCIPALE ========== */
void on_g_entraineur_clicked(GtkButton *button, gpointer user_data);
void on_g_centre_clicked(GtkButton *button, gpointer user_data);
void on_g_membre_clicked(GtkButton *button, gpointer user_data);
void on_g_cours_clicked(GtkButton *button, gpointer user_data);
void on_g_equipment_clicked(GtkButton *button, gpointer user_data);
void on_g_evenment_clicked(GtkButton *button, gpointer user_data);
void on_window_destroy(GtkObject *object, gpointer user_data);

/* ========== CALLBACKS GESTION ÉVÉNEMENTS ========== */
void on_SarraK_button_Eventadd_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Eventaffiche_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Eventstat_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Gest_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button___quip_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS AJOUT ÉVÉNEMENT ========== */
void on_SarraK_button_Add_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Del_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Ajoutretour_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS AFFICHER ÉVÉNEMENT ========== */
void on_satreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_SarraK_button_actualiser_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Find_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Retour_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS SUPPRESSION/MODIFICATION ÉVÉNEMENT ========== */
void on_SarraK_button_Supp_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_modifier_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_Return_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MODIFICATION ÉVÉNEMENT ========== */
void on_SarraK_button_Misajour_clicked(GtkButton *button, gpointer user_data);
void on_Modif_button_Deletemod_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_ModifRetour_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS INSCRIPTION ÉVÉNEMENT ========== */
void on_SarraK_button_Inscrip_clicked(GtkButton *button, gpointer user_data);
void on_Inscrip_button_Inscripdel_clicked(GtkButton *button, gpointer user_data);
void on_SarraK_button_InscripRetour_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS STATISTIQUES ÉVÉNEMENT ========== */
void on_SarraK_radiobutton_Jour_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_SarraK_radiobutton_Soir_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* ========== CALLBACKS GESTION ENTRAÎNEURS ========== */
void on_ajouter_clicked(GtkButton *button, gpointer user_data);
void on_afiicher_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS AJOUTER ENTRAÎNEUR ========== */
void on_abbuttonenrigister_clicked(GtkButton *objet, gpointer user_data);
void on_abbuttonretour_clicked(GtkButton *objet, gpointer user_data);

/* ========== CALLBACKS AFFICHER ENTRAÎNEUR ========== */
void on_abtreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_abbuttonactualiser_clicked(GtkButton *objet, gpointer user_data);
void on_abbuttonrechercher_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS SUPPRIMER/MODIFIER ENTRAÎNEUR ========== */
void on_supprimer_clicked(GtkButton *button, gpointer user_data);
void on_modifier_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS CONFIRMATION ========== */
void on_oui_clicked(GtkButton *button, gpointer user_data);
void on_non_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS GESTION MEMBRES ========== */
void on_emna_button_ajou2_clicked(GtkButton *b, gpointer d);
void on_emna_button_supp1_clicked(GtkButton *b, gpointer d);
void on_emna_button_rech2_clicked(GtkButton *b, gpointer d);
void on_emna_button_filtre2_clicked(GtkButton *b, gpointer d);
void on_emna_button_tri2_clicked(GtkButton *b, gpointer d);
void on_emna_button_retour_clicked(GtkButton *b, gpointer d);
void on_emna_button_modif1_clicked(GtkButton *b, gpointer d);
void on_emna_button_statistique_clicked(GtkButton *b, gpointer d);

/* ========== CALLBACKS AJOUTER MEMBRE ========== */
void on_emna_button_entre2_clicked(GtkButton *button, gpointer user_data);
void on_button_annu2_clicked(GtkButton *b, gpointer d);
void on_cancelbutton_emna_clicked(GtkButton *button, gpointer user_data);
void on_okbutton1_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS SUPPRIMER MEMBRE ========== */
void on_emna_button_supp6_clicked(GtkButton *button, gpointer user_data);
void on_emna_button_retour5_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS RECHERCHER MEMBRE ========== */
void on_emna_button24_rech_clicked(GtkButton *button, gpointer user_data);
void on_emna_button25_expoo_clicked(GtkButton *button, gpointer user_data);
void on_emna_button26_ret_clicked(GtkButton *button, gpointer user_data);
void on_emtreeview1_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d);
void on_emna_button_actualiser_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MODIFIER MEMBRE ========== */
void on_emna_entry_iddiii_activate(GtkEntry *entry, gpointer user_data);
void on_emna_button40_annu_clicked(GtkButton *button, gpointer user_data);
void on_emna_on41_mod_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS TRIER MEMBRE ========== */
void on_emna_button44_trier44_clicked(GtkButton *button, gpointer user_data);
void on_button45_clicked(GtkButton *button, gpointer user_data);
void on_treeview3_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d);
void on_emna_button464_expo_clicked(GtkButton *button, gpointer user_data);
void on_emna_button_actualiser_tri_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS FILTRER MEMBRE ========== */
void on_emna_button_rouuu_clicked(GtkButton *button, gpointer user_data);
void on_emna_button_fil2_clicked(GtkButton *button, gpointer user_data);
void on_treeview4_row_activated(GtkTreeView *tv, GtkTreePath *p, GtkTreeViewColumn *c, gpointer d);
void on_emna_button_xxxx_clicked(GtkButton *button, gpointer user_data);
void on_emna_button_actualiser_filtre_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS STATISTIQUES MEMBRE ========== */
void on_emna_button_ret_statis_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS ESPACE ADMIN ========== */
void on_g_membre_button_clicked(GtkButton *button, gpointer user_data);
void on_g_entraineur_button_clicked(GtkButton *button, gpointer user_data);
void on_g_cours_button_clicked(GtkButton *button, gpointer user_data);
void on_g_equipement_button_clicked(GtkButton *button, gpointer user_data);
void on_g_centre_button_clicked(GtkButton *button, gpointer user_data);
void on_g_evenement_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_EA_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS ESPACE ENTRAÎNEUR ========== */
void on_inscri1_ent_button_clicked(GtkButton *button, gpointer user_data);
void on_reserver_ent_button_clicked(GtkButton *button, gpointer user_data);
void on_inscri2_ent_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_EE_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS GESTION CENTRES ========== */
void on_im_ajouter_button_clicked(GtkButton *button, gpointer user_data);
void on_im_modifier_button_clicked(GtkButton *button, gpointer user_data);
void on_im_supprimer_button_clicked(GtkButton *button, gpointer user_data);
void on_im_rechercher_button_clicked(GtkButton *button, gpointer user_data);
void on_im_stat_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_gc_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS AJOUT CENTRE ========== */
void on_im_ajout_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_radiobutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_radiobutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_enrigistrer_button_clicked(GtkButton *button, gpointer user_data);
void on_im_annuler_ajout_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_ajout_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MODIFIER CENTRE ========== */
void on_im_rechercher_modif_button_clicked(GtkButton *button, gpointer user_data);
void on_im_modif_checkbutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_checkbutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_radiobutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_radiobutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_mettreajour_button_clicked(GtkButton *button, gpointer user_data);
void on_im_annuler_modif_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_modif_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS SUPPRIMER CENTRE ========== */
void on_im_suppmod_supp_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_supp_button_clicked(GtkButton *button, gpointer user_data);
void on_im_suppmod_mod_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS RECHERCHER CENTRE ========== */
void on_im_rechercher_rech_button_clicked(GtkButton *button, gpointer user_data);
void on_im_paratger_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_recherche_button_clicked(GtkButton *button, gpointer user_data);
void on_imtreeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_imtreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_im_export_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS INSCRIPTION CENTRE ========== */
void on_im_inscri_button_clicked(GtkButton *button, gpointer user_data);
void on_im_annuler_inscri_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_inscri_button_clicked(GtkButton *button, gpointer user_data);
void on_rechercher_inscri_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS STATISTIQUES CENTRE ========== */
void on_im_stat_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_stat_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_appliquer_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_stat_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS CONFIRMATION CENTRE ========== */
void on_confirmer_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_confirmer_ok_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS AUTHENTIFICATION ========== */
void on_se_connecter_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS ÉQUIPEMENTS ========== */
void on_notreeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_btngotoaj_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_btngotomodif_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_gotosupp_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_actualiser_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_checkbuttonconfaj_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_buttonrtaj_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_btnajagent_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_radiobuttonhommeaj_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radiobuttonfemmeaj_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_buttonrechidmodif_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_radiobuttonfemmodif_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_radiobuttonhommemodif_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_btnmodifieragent_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_buttonrtmodi_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_buttonrtsupp_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_buttonsupprimeagent_clicked(GtkWidget *objet_graphique, gpointer user_data);

/* ========== CALLBACKS RÉSERVATIONS ========== */
void on_calendar_res_day_selected(GtkCalendar *calendar, gpointer user_data);
void on_btn_chercher_res_clicked(GtkWidget *button, gpointer user_data);
void on_btn_reserver_clicked(GtkWidget *button, gpointer user_data);
void on_btn_annuler_res_clicked(GtkWidget *button, gpointer user_data);
void on_btn_stats_clicked(GtkWidget *button, gpointer user_data);
void on_btn_actualiser_stats_clicked(GtkWidget *button, gpointer user_data);
void on_btn_fermer_stats_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS COURS SPORTIFS ========== */
void on_tasnim_button0_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button16_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1616_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button161616_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button16161616_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1616161616_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button161616161616_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button16161616161616_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS AJOUT COURS ========== */
void on_tasnim_radiobutton15_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_radiobutton1515_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_radiobutton151515_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton15_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton1515_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton151515_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_button15_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1515_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_spinbutton15_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_tasnim_comboboxentry151515_changed(GtkComboBox *combobox, gpointer user_data);

/* ========== CALLBACKS MODIFICATION COURS ========== */
void on_tasnim_radiobutton14_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_radiobutton1414_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_radiobutton141414_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton14_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton1414_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_checkbutton141414_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_tasnim_button14_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1414_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS SUPPRESSION COURS ========== */
void on_tasnim_button13_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1313_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS RECHERCHE COURS ========== */
void on_tasnim_button12_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1212_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button121212_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_treeview12_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);

/* ========== CALLBACKS INSCRIPTION COURS ========== */
void on_tasnim_button10_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_treeview10_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_tasnim_button1010_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button101010_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS STATISTIQUES COURS ========== */
void on_tasnim_button7_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button6_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS DIALOGUES COURS ========== */
void on_tasnim_okbutton11_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_cancelbutton8_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_okbutton8_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_cancelbutton4_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_okbutton4_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_cancelbutton2_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_okbutton2_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS SUCCÈS COURS ========== */
void on_tasnim_button5_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button3_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_button1_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS MANQUANTS CENTRE ========== */
void on_im_supprimer_supp_button_clicked(GtkButton *button, gpointer user_data);
void on_im_stat_checknutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_msg1_button_clicked(GtkButton *button, gpointer user_data);
void on_msg2_button_clicked(GtkButton *button, gpointer user_data);
void on_msg3_button_clicked(GtkButton *button, gpointer user_data);
void on_msg4_button_clicked(GtkButton *button, gpointer user_data);
void on_msg5_button_clicked(GtkButton *button, gpointer user_data);
void on_msg6_button_clicked(GtkButton *button, gpointer user_data);
void on_msg7_button_clicked(GtkButton *button, gpointer user_data);
void on_error_id_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_error_id_ok_button_clicked(GtkButton *button, gpointer user_data);
void on_error_ajout_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_error_ajout_ok_button_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MANQUANTS MEMBRES ========== */
void on_emtreeview3_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_emtreeview4_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);

/* ========== CALLBACKS MANQUANTS AUTHENTIFICATION ========== */
void on_button_auth_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MANQUANTS COACH ========== */
void on_treeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_button46_clicked(GtkButton *button, gpointer user_data);
void on_emna_button43__ret_clicked(GtkButton *button, gpointer user_data);

/* ========== CALLBACKS MANQUANTS TASNIM ========== */
void on_tasnim_spinbutton4_capacit__max_changed(GtkSpinButton *spinbutton, gpointer user_data);
void on_tasnim_comboboxentry1_entra__neur_changed(GtkComboBox *combobox, gpointer user_data);
void on_tasnim_buttonretour_clicked(GtkWidget *button, gpointer user_data);
void on_tasnim_buttonretour1_clicked(GtkWidget *button, gpointer user_data);

/* ========== CALLBACKS MANQUANTS ENTRAÎNEURS ========== */
void on_treeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
/* ========== INITIALISATION ========== */
void initialiser_toutes_fenetres_cachees(void);
void on_button_connexion_clicked(GtkButton *button, gpointer user_data);
void on_treeviewcentre_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_recherchercentre_clicked(GtkButton *button, gpointer user_data);
void on_treeviewequipment_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_rechercherequipment_clicked(GtkButton *button, gpointer user_data);
void on_retourge_clicked(GtkButton *button, gpointer user_data);
void on_retourcours_clicked(GtkButton *button, gpointer user_data);
void on_retourequipment_clicked(GtkButton *button, gpointer user_data);
void on_retourcentres_clicked(GtkButton *button, gpointer user_data);

/* ========== FONCTIONS UTILITAIRES ========== */
void afficher_message(GtkWindow *parent, const gchar *message, GtkMessageType type);
void cacher_toutes_fenetres(void);
void afficher_fenetre(const gchar *nom_f);
void initialiser_donnees(void);
void charger_membre_dans_formulaire_modification(const gchar *id);
void show_error_dialog(GtkWidget *parent, const char *message);
void show_success_dialog(GtkWidget *parent, const char *message);
int show_confirmation_dialog(GtkWidget *parent, const char *message);
void on_button_inscrire_cours_clicked(GtkButton *button, gpointer user_data);
void on_treeviewcourssportif_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_recherchercourssportif_clicked(GtkButton *button, gpointer user_data);


#endif /* CALLBACKS_H */




