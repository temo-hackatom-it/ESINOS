
#include <stdio.h>
#include "memory.h"

// Initialiser la table des pages
void init_page_table(int page_table[]) {

    if (page_table == NULL)
        return;

    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i] = -1;
    }
}

// Chercher le cadre correspondant a une page
int find_frame(int page_table[], int page) {

    if (page_table == NULL ||
        page < 0 || page >= NUM_PAGES) {
        return -1;
    }

    return page_table[page];
}

// Placer une page dans un cadre
void map_page(int page_table[], int page, int frame) {

    // Verifier les parametres
    if (page_table == NULL ||
        page < 0 || page >= NUM_PAGES ||
        frame < 0 || frame >= NUM_FRAMES) {

        printf("Page ou cadre invalide.\n");
        return;
    }

    // Verifier si le cadre est deja occupe
    for (int i = 0; i < NUM_PAGES; i++) {

        if (i != page && page_table[i] == frame) {
            printf("Ce cadre est deja occupe.\n");
            return;
        }
    }

    // Associer la page au cadre
    page_table[page] = frame;
}

// Traduire une adresse logique en adresse physique
int translate_address(int page_table[], int logical_address) {

    // Verifier l'adresse logique
    if (page_table == NULL ||
        logical_address < 0 ||
        logical_address >= NUM_PAGES * PAGE_SIZE) {

        return -1;
    }

    // Calculer le numero de page et le deplacement
    int page = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    // Chercher le cadre correspondant
    int frame = find_frame(page_table, page);

    // Verifier si la page est presente en memoire
    if (frame < 0 || frame >= NUM_FRAMES) {
        return -1;
    }

    // Calculer l'adresse physique
    int physical_address = frame * PAGE_SIZE + offset;

    return physical_address;
}
