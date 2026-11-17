
#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int arrivee;
    int duree;
    int priorite;
    int debut;
    int fin;
    int attente;
    int sejour;
    int termine;
} Processus;

int PS() {

    Processus p[MAX];
    int n;

    double total_attente = 0;
    double total_sejour = 0;

    printf("===== ESINOS : PRIORITY SCHEDULING =====\n");

    // 1. Nombre de processus
    printf("Nombre de processus (1-%d) : ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Erreur : nombre invalide.\n");
        return 1;
    }

    // 2. Saisie des processus
    for (int i = 0; i < n; i++) {

        p[i].id = i + 1;
        p[i].termine = 0;

        printf("\n--- Processus P%d ---\n", p[i].id);

        printf("Temps d'arrivee : ");
        if (scanf("%d", &p[i].arrivee) != 1 ||
            p[i].arrivee < 0) {
            printf("Erreur : arrivee invalide.\n");
            return 1;
        }

        printf("Duree d'execution : ");
        if (scanf("%d", &p[i].duree) != 1 ||
            p[i].duree <= 0) {
            printf("Erreur : duree invalide.\n");
            return 1;
        }

        printf("Priorite (1 = plus elevee) : ");
        if (scanf("%d", &p[i].priorite) != 1 ||
            p[i].priorite < 1) {
            printf("Erreur : priorite invalide.\n");
            return 1;
        }
    }

    // 3. Variables d'ordonnancement
    int temps = 0;
    int nb_termines = 0;

    int ordre[MAX];
    int nb_executions = 0;

    // 4. Ordonnancement Priority non preemptif
    while (nb_termines < n) {

        int choix = -1;

        // Chercher le processus disponible
        // ayant la meilleure priorite
        for (int i = 0; i < n; i++) {

            if (!p[i].termine && p[i].arrivee <= temps) {

                if (choix == -1 ||
                    p[i].priorite < p[choix].priorite ||
                    (p[i].priorite == p[choix].priorite &&
                     p[i].arrivee < p[choix].arrivee)) {

                    choix = i;
                }
            }
        }

        // Aucun processus disponible
        if (choix == -1) {

            int prochaine_arrivee = -1;

            for (int i = 0; i < n; i++) {

                if (!p[i].termine &&
                    (prochaine_arrivee == -1 ||
                     p[i].arrivee < prochaine_arrivee)) {

                    prochaine_arrivee = p[i].arrivee;
                }
            }

            temps = prochaine_arrivee;
            continue;
        }

        // 5. Execution du processus choisi
        p[choix].debut = temps;
        p[choix].fin = temps + p[choix].duree;

        p[choix].sejour =
            p[choix].fin - p[choix].arrivee;

        p[choix].attente =
            p[choix].debut - p[choix].arrivee;

        total_attente += p[choix].attente;
        total_sejour += p[choix].sejour;

        ordre[nb_executions++] = choix;

        temps = p[choix].fin;

        p[choix].termine = 1;
        nb_termines++;
    }

    // 6. Tableau des resultats
    printf("\n========== RESULTATS PRIORITY ==========\n");

    printf("PID\tArr\tDuree\tPrio\tDebut\tFin\tAtt\tSejour\n");

    for (int i = 0; i < n; i++) {

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivee,
               p[i].duree,
               p[i].priorite,
               p[i].debut,
               p[i].fin,
               p[i].attente,
               p[i].sejour);
    }

    // 7. Moyennes
    printf("\nAttente moyenne : %.2f\n",
           total_attente / n);

    printf("Sejour moyen : %.2f\n",
           total_sejour / n);

    // 8. Diagramme de Gantt
    printf("\n========== GANTT PRIORITY ==========\n");

    int precedent = 0;

    for (int k = 0; k < nb_executions; k++) {

        int i = ordre[k];

        if (precedent < p[i].debut) {

            printf("[%d - %d : IDLE] ",
                   precedent, p[i].debut);
        }

        printf("[%d - %d : P%d] ",
               p[i].debut,
               p[i].fin,
               p[i].id);

        precedent = p[i].fin;
    }

    printf("\n");

    return 0;
}
