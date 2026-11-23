
#include <stdio.h>
#include "cpu.h"

int main(void) {

    int choix;
    int cpu_choix;

    do {
        printf("\n=================================\n");
        printf("          ESINOS SYSTEM\n");
        printf("=================================\n");
        printf("1. Ordonnancement CPU\n");
        printf("2. Gestion de la memoire\n");
        printf("3. Remplacement de pages\n");
        printf("4. TLB et performances\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf("Entree invalide.\n");
            return 1;
        }

        switch (choix) {

            case 1:

                do {
                    printf("\n===== ORDONNANCEMENT CPU =====\n");
                    printf("1. FCFS\n");
                    printf("2. SJF\n");
                    printf("3. Round Robin\n");
                    printf("4. Priority Scheduling\n");
                    printf("0. Retour\n");
                    printf("Votre choix : ");

                    if (scanf("%d", &cpu_choix) != 1) {
                        printf("Entree invalide.\n");
                        return 1;
                    }

                    switch (cpu_choix) {
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
                            printf("Retour au menu principal.\n");
                            break;

                        default:
                            printf("Choix invalide.\n");
                    }

                } while (cpu_choix != 0);

                break;

            case 2:
            case 3:
            case 4:
                printf("Module en cours de developpement.\n");
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
