
#include <stdio.h>
#include "memory.h"

int fifo_page_replacement(int page_table[], const int pages[], int page_count) {

    // Vérifier les paramètres
    if (page_table == NULL || pages == NULL || page_count <= 0) {
        printf("Parametres invalides.\n");
        return -1;
    }

    // Vérifier tous les numéros de pages
    for (int i = 0; i < page_count; i++) {
        if (pages[i] < 0 || pages[i] >= NUM_PAGES) {
            printf("Numero de page invalide : %d\n", pages[i]);
            return -1;
        }
    }

    // Initialiser la table des pages
    init_page_table(page_table);

    int frames[NUM_FRAMES];

    // Initialiser les cadres à vide
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
    }

    int next_to_replace = 0;
    int page_faults = 0;

    printf("\n========== FIFO ==========\n\n");

    // Parcourir les pages demandées
    for (int i = 0; i < page_count; i++) {

        int page = pages[i];
        int found = 0;

        // Vérifier si la page est déjà en mémoire
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        // Si la page est absente
        if (found == 0) {

            page_faults++;

            int old_page = frames[next_to_replace];

            // Retirer l'ancienne page
            if (old_page != -1) {
                page_table[old_page] = -1;
            }

            // Charger la nouvelle page
            frames[next_to_replace] = page;
            page_table[page] = next_to_replace;

            // Passer au cadre suivant
            next_to_replace = (next_to_replace + 1) % NUM_FRAMES;
        }

        // Afficher l'état des cadres
        printf("Page %d : [ ", page);

        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        printf("]");

        if (found == 1)
            printf("  HIT\n");
        else
            printf("  PAGE FAULT\n");
    }

    return page_faults;
}
