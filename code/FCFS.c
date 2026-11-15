
#include <stdio.h>

int main() {
    int arrivee[3];
    int duree[3];
    int numero[3] = {1, 2, 3};

    int temps = 0;
    int debut, fin, attente;
    float total_attente = 0;

    // 1. Saisie des temps d'arrivee
    for (int i = 0; i < 3; i++) {
        printf("Arrivee de P%d : ", i + 1);
        scanf("%d", &arrivee[i]);
    }

    // 2. Saisie des durees
    for (int i = 0; i < 3; i++) {
        printf("Duree de P%d : ", i + 1);
        scanf("%d", &duree[i]);
    }

    // 3. Tri des processus par ordre d'arrivee
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (arrivee[j] > arrivee[j + 1]) {
                int temp;

                temp = arrivee[j];
                arrivee[j] = arrivee[j + 1];
                arrivee[j + 1] = temp;

                temp = duree[j];
                duree[j] = duree[j + 1];
                duree[j + 1] = temp;

                temp = numero[j];
                numero[j] = numero[j + 1];
                numero[j + 1] = temp;
            }
        }
    }

    // 4. Execution de FCFS
    printf("\n===== RESULTATS FCFS =====\n");

    for (int i = 0; i < 3; i++) {
        debut = temps;

        if (arrivee[i] > temps) {
            debut = arrivee[i];
        }

        fin = debut + duree[i];
        attente = debut - arrivee[i];

        printf("P%d : %d -> %d\n", numero[i], debut, fin);
        printf("Attente : %d\n", attente);

        total_attente += attente;
        temps = fin;
    }

    // 5. Calcul de la moyenne
    printf("\nAttente moyenne : %.2f\n", total_attente / 3);

    return 0;
}
