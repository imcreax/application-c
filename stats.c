#include "stats.h"
#include "admin.h"
#include "support.h"
#include <string.h>
#include <stdlib.h>

void afficher_statistiques_globales(GtkWidget *window) {
    char txt[100];
   
    // Nombre total des cours dans label7
    int total_cours = get_total_cours();
    sprintf(txt, "%d", total_cours);
    gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label7")), txt);
   
    // Cours disponibles dans label77
    int cours_disponibles = get_cours_disponibles();
    sprintf(txt, "%d", cours_disponibles);
    gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label77")), txt);
   
    // Cours complets dans label777
    int cours_complets = get_cours_complets();
    sprintf(txt, "%d", cours_complets);
    gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label777")), txt);
   
    // Taux d'occupation total dans label7777
    float taux_occupation = get_taux_occupation();
    sprintf(txt, "%.2f%%", taux_occupation);
    gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label7777")), txt);
   
    // Nombre total d'inscrits dans label77777
    int total_inscrits = get_total_inscrits();
    sprintf(txt, "%d", total_inscrits);
    gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label77777")), txt);
}

void afficher_statistiques_filtre(GtkWidget *window) {
    char txt[100];
   
    // Récupérer le centre sélectionné
    GtkWidget *combo_centre = lookup_widget(window, "comboboxentry66");
    const char *centre_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_centre));
   
    if (centre_text && strlen(centre_text) > 0) {
        // Cours disponibles pour le centre dans label6666
        int cours_disponibles_centre = get_cours_disponibles_par_centre((char*)centre_text);
        sprintf(txt, "%d", cours_disponibles_centre);
        gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label6666")), txt);
    } else {
        gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label6666")), "0");
    }
   
    // Récupérer l'entraîneur sélectionné
    GtkWidget *combo_entraineur = lookup_widget(window, "comboboxentry66666");
    const char *entraineur_text = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_entraineur));
   
    if (entraineur_text && strlen(entraineur_text) > 0) {
        // Places disponibles pour l'entraîneur dans label666666
        int places_disponibles_entraineur = get_places_disponibles_par_entraineur((char*)entraineur_text);
        sprintf(txt, "%d", places_disponibles_entraineur);
        gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label666666")), txt);
    } else {
        gtk_label_set_text(GTK_LABEL(lookup_widget(window, "label666666")), "0");
    }
}
void afficher_statistiques(GtkWidget *window) {
    // Afficher les statistiques dans les labels appropriés
    GtkWidget *label = lookup_widget(window, "label_stats");
    if (label) {
        gtk_label_set_text(GTK_LABEL(label), "Statistiques mises à jour");
    }
}	

