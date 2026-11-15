
#include <stdio.h>

int main() {
    int duree[3];
    int restant[3];
    int quantum;

    // Saisie des durees
    for (int i = 0; i < 3; i++) {
        printf("Duree de P%d : ", i + 1);
        scanf("%d", &duree[i]);

        restant[i] = duree[i];
    }

    // Saisie du quantum
    printf("Entrer le quantum : ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Erreur : le quantum doit etre positif.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        if (duree[i] <= 0) {
            printf("Erreur : les durees doivent etre positives.\n");
            return 1;
        }
    }

    int temps = 0;
    int nb_termines = 0;

    int attente[3] = {0, 0, 0};
    float total_attente = 0;

    // Ordonnancement Round Robin
    while (nb_termines < 3) {
        for (int i = 0; i < 3; i++) {

            if (restant[i] > 0) {
                int debut = temps;

                if (restant[i] > quantum) {
                    temps += quantum;
                    restant[i] -= quantum;
                } else {
                    temps += restant[i];
                    restant[i] = 0;
                    nb_termines++;

                    attente[i] = temps - duree[i];
                    total_attente += attente[i];
                }

                printf("P%d : %d -> %d\n",
                       i + 1, debut, temps);
            }
        }
    }

    // Affichage des temps d'attente
    printf("\n--- Resultats ---\n");

    for (int i = 0; i < 3; i++) {
        printf("Attente P%d : %d\n",
               i + 1, attente[i]);
    }

    printf("Attente moyenne : %.2f\n",
           total_attente / 3);

    return 0;
}

