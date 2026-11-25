#include <stdio.h>
#include "tlb.h"

// Initialisation du TLB
void init_tlb(TLBEntry tlb[]) {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].page = -1;
        tlb[i].frame = -1;
    }
}

// Recherche d'une page dans le TLB
int search_tlb(TLBEntry tlb[], int page) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].page == page) {
            return tlb[i].frame;
        }
    }

    return -1;
}

// Mise a jour du TLB avec remplacement FIFO
void update_tlb(TLBEntry tlb[], int page,
                int frame, int *next) {

    tlb[*next].page = page;
    tlb[*next].frame = frame;

    *next = (*next + 1) % TLB_SIZE;
}

// Calcul du temps effectif d'acces
double calculate_eat(double hit_rate,
                     double tlb_time,
                     double memory_time) {

    return hit_rate * (tlb_time + memory_time)
         + (1.0 - hit_rate)
         * (tlb_time + 2 * memory_time);
}

// Affichage du contenu du TLB
static void afficher_tlb(TLBEntry tlb[]) {

    printf("\n===== CONTENU DU TLB =====\n");

    printf("%-10s %-10s %-10s\n",
           "Entree", "Page", "Cadre");

    for (int i = 0; i < TLB_SIZE; i++) {

        if (tlb[i].page == -1) {
            printf("%-10d %-10s %-10s\n",
                   i, "Vide", "Vide");
        } else {
            printf("%-10d %-10d %-10d\n",
                   i, tlb[i].page, tlb[i].frame);
        }
    }
}

// Simulation du TLB et calcul des performances
void menu_tlb(void) {

    TLBEntry tlb[TLB_SIZE];

    int page_table[NUM_PAGES];

    int next = 0;
    int hits = 0;
    int misses = 0;
    int faults = 0;
    int count;

    double tlb_time;
    double memory_time;

    init_tlb(tlb);
    init_page_table(page_table);

    // Table des pages fixe pour cette simulation
    map_page(page_table, 0, 2);
    map_page(page_table, 1, 0);
    map_page(page_table, 3, 1);

    printf("\n=================================\n");
    printf("       TLB ET PERFORMANCES\n");
    printf("=================================\n");

    printf("\nTable des pages initiale :\n");

    for (int i = 0; i < NUM_PAGES; i++) {
        if (page_table[i] == -1) {
            printf("Page %d : Absente\n", i);
        } else {
            printf("Page %d : Cadre %d\n",
                   i, page_table[i]);
        }
    }

    printf("\nTemps d'acces au TLB (ns) : ");

    if (scanf("%lf", &tlb_time) != 1 ||
        !(tlb_time > 0)) {
        printf("Temps invalide.\n");
        return;
    }

    printf("Temps d'acces a la RAM (ns) : ");

    if (scanf("%lf", &memory_time) != 1 ||
        !(memory_time > 0)) {
        printf("Temps invalide.\n");
        return;
    }

    printf("Nombre d'adresses a traduire (1-100) : ");

    if (scanf("%d", &count) != 1 ||
        count <= 0 || count > 100) {
        printf("Nombre invalide.\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        int logical_address;

        printf("\nAdresse logique %d (0-%d) : ",
               i + 1, NUM_PAGES * PAGE_SIZE - 1);

        if (scanf("%d", &logical_address) != 1) {
            return;
        }

        if (logical_address < 0 ||
            logical_address >= NUM_PAGES * PAGE_SIZE) {

            printf("Adresse invalide.\n");
            i--;
            continue;
        }

        int page = logical_address / PAGE_SIZE;
        int offset = logical_address % PAGE_SIZE;

        int frame = search_tlb(tlb, page);

        printf("Page   : %d\n", page);
        printf("Offset : %d\n", offset);

        if (frame != -1) {

            hits++;

            printf("TLB HIT\n");

        } else {

            misses++;

            printf("TLB MISS\n");

            frame = find_frame(page_table, page);

            if (frame == -1) {

                faults++;

                printf("PAGE FAULT : page absente.\n");

                afficher_tlb(tlb);

                continue;
            }

            update_tlb(tlb, page, frame, &next);
        }

        int physical_address =
            frame * PAGE_SIZE + offset;

        printf("Cadre            : %d\n", frame);
        printf("Adresse physique : %d\n",
               physical_address);

        afficher_tlb(tlb);
    }

    double hit_rate = (double) hits / count;
    double miss_rate = (double) misses / count;

    printf("\n=================================\n");
    printf("           RESULTATS\n");
    printf("=================================\n");

    printf("Nombre de demandes : %d\n", count);
    printf("TLB Hits           : %d\n", hits);
    printf("TLB Misses         : %d\n", misses);
    printf("Page Faults        : %d\n", faults);

    printf("TLB Hit Rate       : %.2f %%\n",
           hit_rate * 100);

    printf("TLB Miss Rate      : %.2f %%\n",
           miss_rate * 100);

    // EAT calcule uniquement pour les pages residentes
    int successful = count - faults;

    if (successful > 0) {

        double resident_hit_rate =
            (double) hits / successful;

        double eat = calculate_eat(
            resident_hit_rate,
            tlb_time,
            memory_time
        );

        printf("EAT                : %.2f ns\n", eat);

        printf("Sans TLB           : %.2f ns\n",
               2 * memory_time);

        printf("\nEAT hors cout des defauts de page.\n");

    } else {

        printf("EAT non calculable : aucune traduction reussie.\n");
    }
}