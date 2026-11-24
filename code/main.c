#include <stdio.h>
#include "memory.h"

int main() {

    // Créer la table des pages
    int page_table[NUM_PAGES];

    // Initialiser la table
    init_page_table(page_table);

    // Suite des pages à utiliser
    int pages[] = {1, 2, 3, 1, 4, 2, 5};

    // Calculer le nombre de pages
    int page_count = sizeof(pages) / sizeof(pages[0]);

    // Exécuter l'algorithme FIFO
    int faults = fifo_page_replacement(page_table, pages, page_count);

    // Afficher le nombre de défauts de page
    printf("\nNombre total de défauts de page : %d\n", faults);

    // Afficher la table des pages finale
    printf("\nTable des pages finale :\n");

    for (int i = 0; i < NUM_PAGES; i++) {

        printf("Page %d : ", i);

        if (page_table[i] == -1) {
            printf("Absente\n");
        } else {
            printf("Cadre %d\n", page_table[i]);
        }
    }

    return 0;
}