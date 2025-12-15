#!/bin/bash

# Sauvegarder
cp callbacks.c callbacks.c.old

# Extraire seulement la première occurrence de chaque fonction
awk '
BEGIN { in_function = 0; function_name = ""; seen_functions[""]=0; }

# Détecter le début d'une fonction
/^[a-zA-Z].*\(.*\)$/ {
    function_name = $0;
    if (seen_functions[function_name] == 0) {
        seen_functions[function_name] = 1;
        in_function = 1;
        print;
        next;
    } else {
        in_function = 0;
        next;
    }
}

# Si on est dans une fonction non-dupliquée, imprimer
in_function == 1 { print; next; }

# Pour les variables globales, garder seulement la première
/^int duree_selectionnee/ || /^int niveau_checked/ || /^char id_membre_courant/ {
    if (seen_functions[$0] == 0) {
        seen_functions[$0] = 1;
        print;
    }
    next;
}

# Garder tout le reste sauf les lignes vides consécutives
{ print }
' callbacks.c.old > callbacks.c.temp

mv callbacks.c.temp callbacks.c
