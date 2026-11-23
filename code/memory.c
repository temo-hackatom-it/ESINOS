#include "memory.h"

// Initialiser la table des pages
void init_page_table(int page_table[]) {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i] = -1;
    }
}

// Chercher dans quel cadre se trouve une page
int find_frame(int page_table[], int page) {
    if (page < 0 || page >= NUM_PAGES) {
        return -1;
    }

    return page_table[page];
}

// Placer une page dans un cadre
void map_page(int page_table[], int page, int frame) {
    if (page < 0 || page >= NUM_PAGES ||
        frame < 0 || frame >= NUM_FRAMES) {
        return;
    }

    // Vérifier que le cadre n'est pas déjà utilisé
    for (int i = 0; i < NUM_PAGES; i++) {
        if (i != page && page_table[i] == frame) {
            return;
        }
    }

    page_table[page] = frame;
}

// Traduire une adresse logique en adresse physique
int translate_address(int page_table[], int logical_address) {

    if (logical_address < 0 ||
        logical_address >= NUM_PAGES * PAGE_SIZE) {
        return -1;
    }

    int page = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    int frame = find_frame(page_table, page);

    if (frame == -1) {
        return -1;
    }

    int physical_address = frame * PAGE_SIZE + offset;

    return physical_address;
}