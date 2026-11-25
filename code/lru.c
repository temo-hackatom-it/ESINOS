
#include <stdio.h>
#include "memory.h"

int lru_page_replacement(int page_table[], const int pages[], int page_count) {

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
    int last_used[NUM_FRAMES];

    // Initialiser les cadres
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

    printf("\n========== LRU ==========\n\n");

    // Parcourir les pages demandées
    for (int i = 0; i < page_count; i++) {

        int page = pages[i];
        int found = 0;

        // Vérifier si la page est déjà en mémoire
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                last_used[j] = i;
                break;
            }
        }

        // Si la page est absente
        if (found == 0) {

            page_faults++;

            int frame_to_use = -1;

            // Chercher un cadre libre
            for (int j = 0; j < NUM_FRAMES; j++) {
                if (frames[j] == -1) {
                    frame_to_use = j;
                    break;
                }
            }

            // Si tous les cadres sont occupés
            if (frame_to_use == -1) {

                frame_to_use = 0;

                // Chercher la page la moins récemment utilisée
                for (int j = 1; j < NUM_FRAMES; j++) {
                    if (last_used[j] < last_used[frame_to_use]) {
                        frame_to_use = j;
                    }
                }

                // Retirer l'ancienne page
                int old_page = frames[frame_to_use];
                page_table[old_page] = -1;
            }

            // Charger la nouvelle page
            frames[frame_to_use] = page;
            page_table[page] = frame_to_use;
            last_used[frame_to_use] = i;
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
