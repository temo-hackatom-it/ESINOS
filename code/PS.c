
#include <stdio.h>

int main() {

    int arrivee[3];
    int duree[3];
    int priorite[3];

    // Saisie des processus
    for (int i = 0; i < 3; i++) {

        printf("\nProcessus P%d\n", i + 1);

        printf("Temps d'arrivee : ");
        scanf("%d", &arrivee[i]);

        printf("Duree d'execution : ");
        scanf("%d", &duree[i]);

        printf("Priorite : ");
        scanf("%d", &priorite[i]);

        if (arrivee[i] < 0 || duree[i] <= 0) {
            printf("Erreur : arrivee >= 0 et duree > 0.\n");
            return 1;
        }
    }

    // Variables d'ordonnancement
    int termine[3] = {0, 0, 0};
    int attente[3] = {0, 0, 0};
    int sejour[3] = {0, 0, 0};

    int temps = 0;
    int nb_termines = 0;

    float total_attente = 0;
    float total_sejour = 0;

    printf("\n--- Ordonnancement Priority ---\n");

    // Ordonnancement non preemptif
    while (nb_termines < 3) {

        int choix = -1;

        // Chercher le processus avec la meilleure priorite
        for (int i = 0; i < 3; i++) {

            if (termine[i] == 0 && arrivee[i] <= temps) {

                if (choix == -1 ||
                    priorite[i] < priorite[choix]) {

                    choix = i;
                }
            }
        }

        // Aucun processus disponible
        if (choix == -1) {
            temps++;
        }
        else {

            int debut = temps;

            // Execution du processus
            temps = temps + duree[choix];

            printf("P%d : %d -> %d\n",
                   choix + 1, debut, temps);

            // Calcul des temps
            sejour[choix] = temps - arrivee[choix];

            attente[choix] = sejour[choix] - duree[choix];

            total_attente += attente[choix];
            total_sejour += sejour[choix];

            // Marquer le processus comme termine
            termine[choix] = 1;
            nb_termines++;
        }
    }

    // Affichage des resultats
    printf("\n--- Resultats Priority Scheduling ---\n");

    for (int i = 0; i < 3; i++) {

        printf("P%d : Attente = %d, Sejour = %d\n",
               i + 1, attente[i], sejour[i]);
    }

    printf("\nAttente moyenne : %.2f\n",
           total_attente / 3);

    printf("Sejour moyen : %.2f\n",
           total_sejour / 3);

    return 0;
}

