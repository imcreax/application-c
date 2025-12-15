#include <stdio.h>
#include <string.h>
#include "centre.h"
#include "inscription.h"

int ajouter_inscription(Inscription i) {
    FILE *f = fopen("inscriptions.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d;%s;%s\n", i.idCentre, i.nomEntraineur, i.emailEntraineur);
        fclose(f);
        return 1;
    }
    return 0;
}
