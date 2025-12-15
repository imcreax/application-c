#include <gtk/gtk.h>

void on_im_modifier_button_clicked(GtkButton *button, gpointer user_data);
void on_im_supprimer_button_clicked(GtkButton *button, gpointer user_data);
void on_im_rechercher_button_clicked(GtkButton *button, gpointer user_data);
void on_im_stat_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_gc_button_clicked(GtkButton *button, gpointer user_data);
void on_im_ajouter_button_clicked(GtkButton *button, gpointer user_data);

void on_im_ajout_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_radiobutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_ajout_radiobutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);

void on_im_enrigistrer_button_clicked(GtkButton *button, gpointer user_data);
void on_im_annuler_ajout_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_ajout_button_clicked(GtkButton *button, gpointer user_data);
void on_im_rechercher_modif_button_clicked(GtkButton *button, gpointer user_data);

void on_im_modif_checkbutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_checkbutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_radiobutton1_clicked(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_modif_radiobutton2_clicked(GtkToggleButton *togglebutton, gpointer user_data);

void on_im_mettreajour_button_clicked(GtkButton *button, gpointer user_data);
void on_im_annuler_modif_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_modif_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_supp_button_clicked(GtkButton *button, gpointer user_data);

void on_treeview1_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_im_export_button_clicked(GtkButton *button, gpointer user_data);
void on_im_paratger_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_recherche_button_clicked(GtkButton *button, gpointer user_data);
void on_treeview2_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);

void on_im_annuler_inscri_button_clicked(GtkButton *button, gpointer user_data);
void on_im_retour_inscri_button_clicked(GtkButton *button, gpointer user_data);
void on_im_inscri_button_clicked(GtkButton *button, gpointer user_data);

void on_im_stat_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_treeview3_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data);
void on_im_stat_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_im_appliquer_button_clicked(GtkButton *button, gpointer user_data);

void on_msg1_button_clicked(GtkButton *button, gpointer user_data);
void on_msg2_button_clicked(GtkButton *button, gpointer user_data);
void on_msg3_button_clicked(GtkButton *button, gpointer user_data);
void on_msg4_button_clicked(GtkButton *button, gpointer user_data);
void on_msg5_button_clicked(GtkButton *button, gpointer user_data);
void on_msg6_button_clicked(GtkButton *button, gpointer user_data);
void on_msg7_button_clicked(GtkButton *button, gpointer user_data);

void on_error_id_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_error_id_ok_button_clicked(GtkButton *button, gpointer user_data);
void on_confirmer_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_confirmer_ok_button_clicked(GtkButton *button, gpointer user_data);
void on_error_ajout_cancel_button_clicked(GtkButton *button, gpointer user_data);
void on_error_ajout_ok_button_clicked(GtkButton *button, gpointer user_data);

void on_im_supprimer_supp_button_clicked(GtkButton *button, gpointer user_data);
void on_im_rechercher_rech_button_clicked(GtkButton *button, gpointer user_data);
