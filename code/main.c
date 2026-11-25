#include <stdio.h>
#include "cpu.h"
#include "memory.h"
#include "tlb.h"

#define MAX_REQUESTS 100

// Affichage de la table des pages
void afficher_table(int page_table[]) {

    printf("\n===== TABLE DES PAGES =====\n");

    for (int i = 0; i < NUM_PAGES; i++) {

        printf("Page %d : ", i);

        if (page_table[i] == -1)
            printf("Absente\n");
        else
            printf("Cadre %d\n", page_table[i]);
    }
}

// Menu ordonnancement CPU
void menu_cpu(void) {

    int choix;

    do {
        printf("\n===== ORDONNANCEMENT CPU =====\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Round Robin\n");
        printf("4. Priority Scheduling\n");
        printf("0. Retour\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
            return;

        switch (choix) {

            case 1:
                FCFS();
                break;

            case 2:
                SJF();
                break;

            case 3:
                RR();
                break;

            case 4:
                PS();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);
}

// Menu gestion de la memoire
void menu_memoire(void) {

    int page_table[NUM_PAGES];

    int choix;
    int page;
    int frame;
    int adresse_logique;
    int adresse_physique;

    init_page_table(page_table);

    do {
        printf("\n===== GESTION DE LA MEMOIRE =====\n");
        printf("1. Associer une page a un cadre\n");
        printf("2. Traduire une adresse logique\n");
        printf("3. Afficher la table des pages\n");
        printf("4. Reinitialiser la table\n");
        printf("0. Retour\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
            return;

        switch (choix) {

            case 1:

                printf("Numero de page (0-%d) : ",
                       NUM_PAGES - 1);

                if (scanf("%d", &page) != 1)
                    return;

                printf("Numero de cadre (0-%d) : ",
                       NUM_FRAMES - 1);

                if (scanf("%d", &frame) != 1)
                    return;

                map_page(page_table, page, frame);

                afficher_table(page_table);

                break;

            case 2:

                printf("Adresse logique (0-%d) : ",
                       NUM_PAGES * PAGE_SIZE - 1);

                if (scanf("%d", &adresse_logique) != 1)
                    return;

                adresse_physique = translate_address(
                    page_table, adresse_logique
                );

                if (adresse_physique == -1) {

                    printf("Adresse invalide ou page absente.\n");

                } else {

                    printf("Numero de page : %d\n",
                           adresse_logique / PAGE_SIZE);

                    printf("Offset : %d\n",
                           adresse_logique % PAGE_SIZE);

                    printf("Adresse physique : %d\n",
                           adresse_physique);
                }

                break;

            case 3:

                afficher_table(page_table);
                break;

            case 4:

                init_page_table(page_table);

                printf("Table reinitialisee.\n");
                break;

            case 0:
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);
}

// Affichage des performances
void afficher_resultats(int faults, int page_count) {

    if (faults < 0 || page_count <= 0 ||
        faults > page_count) {

        printf("Erreur de simulation.\n");
        return;
    }

    int hits = page_count - faults;

    double hit_rate = 100.0 * hits / page_count;
    double fault_rate = 100.0 * faults / page_count;

    printf("\n===== RESULTATS =====\n");

    printf("Nombre de demandes : %d\n", page_count);
    printf("Defauts de page    : %d\n", faults);
    printf("Hits               : %d\n", hits);
    printf("Hit Rate           : %.2f %%\n", hit_rate);
    printf("Fault Rate         : %.2f %%\n", fault_rate);
}

// Menu remplacement de pages
void menu_remplacement(void) {

    int choix;
    int pages[MAX_REQUESTS];
    int page_count;
    int page_table[NUM_PAGES];

    int faults;
    int fifo_faults;
    int lru_faults;
    int optimal_faults;

    do {
        printf("\n===== REMPLACEMENT DE PAGES =====\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Comparer FIFO, LRU et Optimal\n");
        printf("0. Retour\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
            return;

        if (choix == 0)
            break;

        if (choix < 1 || choix > 4) {

            printf("Choix invalide.\n");
            continue;
        }

        printf("Nombre de pages demandees (1-%d) : ",
               MAX_REQUESTS);

        if (scanf("%d", &page_count) != 1)
            return;

        if (page_count <= 0 ||
            page_count > MAX_REQUESTS) {

            printf("Nombre invalide.\n");
            continue;
        }

        // Saisie des pages
        for (int i = 0; i < page_count; i++) {

            do {
                printf("Page %d (0-%d) : ",
                       i + 1, NUM_PAGES - 1);

                if (scanf("%d", &pages[i]) != 1)
                    return;

                if (pages[i] < 0 ||
                    pages[i] >= NUM_PAGES) {

                    printf("Numero de page invalide.\n");
                }

            } while (pages[i] < 0 ||
                     pages[i] >= NUM_PAGES);
        }

        init_page_table(page_table);

        switch (choix) {

            case 1:

                faults = fifo_page_replacement(
                    page_table, pages, page_count
                );

                afficher_resultats(faults, page_count);

                if (faults >= 0)
                    afficher_table(page_table);

                break;

            case 2:

                faults = lru_page_replacement(
                    page_table, pages, page_count
                );

                afficher_resultats(faults, page_count);

                if (faults >= 0)
                    afficher_table(page_table);

                break;

            case 3:

                faults = optimal_page_replacement(
                    page_table, pages, page_count
                );

                afficher_resultats(faults, page_count);

                if (faults >= 0)
                    afficher_table(page_table);

                break;

            case 4: {

                // Simulation FIFO
                fifo_faults = fifo_page_replacement(
                    page_table, pages, page_count
                );

                init_page_table(page_table);

                // Simulation LRU
                lru_faults = lru_page_replacement(
                    page_table, pages, page_count
                );

                init_page_table(page_table);

                // Simulation Optimal
                optimal_faults = optimal_page_replacement(
                    page_table, pages, page_count
                );

                if (fifo_faults < 0 ||
                    lru_faults < 0 ||
                    optimal_faults < 0) {

                    printf("Erreur de simulation.\n");
                    break;
                }

                printf("\n========== COMPARAISON ==========\n");

                printf("%-10s %10s %10s %12s\n",
                       "Algo", "Faults", "Hits", "Hit Rate");

                printf("---------------------------------------------\n");

                printf("%-10s %10d %10d %11.2f%%\n",
                       "FIFO",
                       fifo_faults,
                       page_count - fifo_faults,
                       100.0 * (page_count - fifo_faults)
                       / page_count);

                printf("%-10s %10d %10d %11.2f%%\n",
                       "LRU",
                       lru_faults,
                       page_count - lru_faults,
                       100.0 * (page_count - lru_faults)
                       / page_count);

                printf("%-10s %10d %10d %11.2f%%\n",
                       "Optimal",
                       optimal_faults,
                       page_count - optimal_faults,
                       100.0 * (page_count - optimal_faults)
                       / page_count);

                // Recherche du meilleur algorithme
                int minimum = fifo_faults;

                if (lru_faults < minimum)
                    minimum = lru_faults;

                if (optimal_faults < minimum)
                    minimum = optimal_faults;

                printf("\nMeilleur(s) algorithme(s) : ");

                if (fifo_faults == minimum)
                    printf("FIFO ");

                if (lru_faults == minimum)
                    printf("LRU ");

                if (optimal_faults == minimum)
                    printf("Optimal ");

                printf("\nMinimum de defauts : %d\n",
                       minimum);

                break;
            }
        }

    } while (choix != 0);
}

// Programme principal
int main(void) {

    int choix;

    do {
        printf("\n=================================\n");
        printf("          ESINOS SYSTEM\n");
        printf("=================================\n");
        printf("1. Ordonnancement CPU\n");
        printf("2. Gestion de la memoire\n");
        printf("3. Remplacement de pages\n");
        printf("4. TLB et performances (EAT)\n");
        printf("0. Quitter\n");
        printf("=================================\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {

            printf("Entree invalide.\n");
            return 1;
        }

        switch (choix) {

            case 1:
                menu_cpu();
                break;

            case 2:
                menu_memoire();
                break;

            case 3:
                menu_remplacement();
                break;

            case 4:
                menu_tlb();
                break;

            case 0:
                printf("Fermeture de ESINOS.\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}