
#include <stdio.h>
#include "memory.h"

int optimal_page_replacement(int page_table[],
                             const int pages[],
                             int page_count) {

    // Verifier les parametres
    if (page_table == NULL || pages == NULL || page_count <= 0) {
        printf("Parametres invalides.\n");
        return -1;
    }

    // Verifier les numeros de pages
    for (int i = 0; i < page_count; i++) {
        if (pages[i] < 0 || pages[i] >= NUM_PAGES) {
            printf("Numero de page invalide : %d\n", pages[i]);
            return -1;
        }
    }

    init_page_table(page_table);

    int frames[NUM_FRAMES];
    int page_faults = 0;

    // Initialiser les cadres
    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
    }

    printf("\n========== OPTIMAL ==========\n\n");

    // Parcourir les pages demandees
    for (int i = 0; i < page_count; i++) {

        int page = pages[i];
        int found = 0;

        // Verifier si la page existe deja
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
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

            // Si tous les cadres sont occupes
            if (frame_to_use == -1) {

                int farthest = -1;

                // Examiner chaque cadre
                for (int j = 0; j < NUM_FRAMES; j++) {

                    int k;

                    // Chercher la prochaine utilisation
                    for (k = i + 1; k < page_count; k++) {
                        if (pages[k] == frames[j]) {
                            break;
                        }
                    }

                    // Si la page ne sera plus utilisee
                    if (k == page_count) {
                        frame_to_use = j;
                        break;
                    }

                    // Chercher la page utilisee le plus tard
                    if (k > farthest) {
                        farthest = k;
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
        }

        // Afficher les cadres
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
