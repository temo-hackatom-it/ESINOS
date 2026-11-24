
#include <stdio.h>
#include "memory.h"

int lru_page_replacement(int page_table[],
                         const int pages[],
                         int page_count) {

    int frames[NUM_FRAMES];
    int last_used[NUM_FRAMES];

    // Initialiser les cadres
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }

    int page_faults = 0;

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

        // Si la page n'est pas en mémoire
        if (found == 0) {

            page_faults++;

            int frame_to_use = -1;

            // Chercher un cadre vide
            for (int j = 0; j < NUM_FRAMES; j++) {
                if (frames[j] == -1) {
                    frame_to_use = j;
                    break;
                }
            }

            // Si aucun cadre n'est vide, chercher le moins récent
            if (frame_to_use == -1) {

                frame_to_use = 0;

                for (int j = 1; j < NUM_FRAMES; j++) {
                    if (last_used[j] < last_used[frame_to_use]) {
                        frame_to_use = j;
                    }
                }

                int old_page = frames[frame_to_use];
                page_table[old_page] = -1;
            }

            // Charger la nouvelle page
            frames[frame_to_use] = page;
            page_table[page] = frame_to_use;
            last_used[frame_to_use] = i;
        }

        // Afficher l'état des cadres
        printf("Page %d : ", page);

        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found == 1)
            printf("(déjà présente)\n");
        else
            printf("(défaut de page)\n");
    }

    return page_faults;
}
