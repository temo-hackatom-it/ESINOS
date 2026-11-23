#include <stdio.h>
#include "memory.h"

int fifo_page_replacement(int page_table[], const int pages[], int page_count) {

    int frames[NUM_FRAMES];

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
    }

    int next_to_replace = 0;
    int page_faults = 0;

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

        // Si la page n'est pas en mémoire
        if (found == 0) {

            page_faults++;

            int old_page = frames[next_to_replace];

            // Si le cadre contient déjà une ancienne page
            if (old_page != -1) {
                page_table[old_page] = -1;
            }

            // Charger la nouvelle page
            frames[next_to_replace] = page;
            page_table[page] = next_to_replace;

            next_to_replace = (next_to_replace + 1) % NUM_FRAMES;
        }

        printf("Page %d : ", page);

        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        printf("\n");
    }

    return page_faults;
}