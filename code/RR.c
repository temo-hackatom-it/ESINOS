
#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int arrivee;
    int duree;
    int restant;
    int fin;
    int attente;
    int sejour;
} Processus;

typedef struct {
    int id;
    int debut;
    int fin;
} Execution;

int RR() {

    Processus p[MAX];
    int n, quantum;

    printf("===== ESINOS : ROUND ROBIN =====\n");

    printf("Nombre de processus (1-%d) : ", MAX);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Erreur : nombre invalide.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {

        p[i].id = i + 1;

        printf("\n--- Processus P%d ---\n", i + 1);

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

        p[i].restant = p[i].duree;
        p[i].fin = 0;
    }

    printf("\nQuantum : ");
    if (scanf("%d", &quantum) != 1 || quantum <= 0) {
        printf("Erreur : quantum invalide.\n");
        return 1;
    }

    // Trier par arrivee (stable pour les egalites)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].arrivee < p[i].arrivee) {
                Processus temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // File circulaire : au maximum n processus en attente
    int file[MAX + 1];
    int tete = 0, queue = 0;
    int prochain = 0;
    int termines = 0;
    int temps = 0;

    double total_attente = 0;
    double total_sejour = 0;

    printf("\n========== GANTT ROUND ROBIN ==========\n");

    while (termines < n) {

        // Ajouter les processus deja arrives
        while (prochain < n && p[prochain].arrivee <= temps) {
            file[queue] = prochain;
            queue = (queue + 1) % (MAX + 1);
            prochain++;
        }

        // Aucun processus disponible
        if (tete == queue) {

            if (prochain < n) {
                printf("[%d - %d : IDLE] ",
                       temps, p[prochain].arrivee);

                temps = p[prochain].arrivee;
                continue;
            }

            break;
        }

        // Retirer le premier processus de la file
        int i = file[tete];
        tete = (tete + 1) % (MAX + 1);

        int debut = temps;

        // Execution pendant un quantum au maximum
        int execution = p[i].restant;

        if (execution > quantum) {
            execution = quantum;
        }

        temps += execution;
        p[i].restant -= execution;

        printf("[%d - %d : P%d] ",
               debut, temps, p[i].id);

        // Ajouter les nouvelles arrivees avant de remettre
        // le processus interrompu en fin de file
        while (prochain < n && p[prochain].arrivee <= temps) {
            file[queue] = prochain;
            queue = (queue + 1) % (MAX + 1);
            prochain++;
        }

        if (p[i].restant > 0) {

            // Processus non termine : retour en fin de file
            file[queue] = i;
            queue = (queue + 1) % (MAX + 1);

        } else {

            // Processus termine
            p[i].fin = temps;
            p[i].sejour = p[i].fin - p[i].arrivee;
            p[i].attente = p[i].sejour - p[i].duree;

            total_attente += p[i].attente;
            total_sejour += p[i].sejour;

            termines++;
        }
    }

    printf("\n\n========== RESULTATS ROUND ROBIN ==========\n");

    printf("PID\tArr\tDuree\tFin\tAtt\tSejour\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivee,
               p[i].duree,
               p[i].fin,
               p[i].attente,
               p[i].sejour);
    }

    printf("\nAttente moyenne : %.2f\n",
           total_attente / n);

    printf("Sejour moyen : %.2f\n",
           total_sejour / n);

    return 0;
}