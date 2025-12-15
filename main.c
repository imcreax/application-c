#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "utilisateur.h"
#include "membre.h"

int main(int argc, char *argv[])
{
    GtkWidget *window;

    gtk_set_locale();
    gtk_init(&argc, &argv);

    // Charger les données au démarrage
    charger_membres_depuis_fichier();
    
    // AFFICHER LA FENÊTRE D'AUTHENTIFICATION EN PREMIER
    window = create_Athentification();  // NOM CORRIGÉ
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
