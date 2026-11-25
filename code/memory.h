
#ifndef MEMORY_H
#define MEMORY_H

// Configuration de la memoire
#define PAGE_SIZE 100
#define NUM_FRAMES 3
#define NUM_PAGES 6

// Gestion de la table des pages
void init_page_table(int page_table[]);

int find_frame(int page_table[], int page);

void map_page(int page_table[], int page, int frame);

// Traduction d'adresse
int translate_address(int page_table[], int logical_address);

// Algorithme FIFO
int fifo_page_replacement(int page_table[],
                          const int pages[],
                          int page_count);

// Algorithme LRU
int lru_page_replacement(int page_table[],
                         const int pages[],
                         int page_count);

// Algorithme Optimal
int optimal_page_replacement(int page_table[],
                             const int pages[],
                             int page_count);

#endif
