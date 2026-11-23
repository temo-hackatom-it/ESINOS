
#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int arrivee;
    int duree;
    int debut;
    int fin;
    int attente;
    int sejour;
} Processus;

int FCFS() {

    Processus p[MAX];
    int n;

    double total_attente = 0;
    double total_sejour = 0;

    printf("===== ESINOS : FCFS =====\n");

    // 1. Nombre de processus
    printf("Nombre de processus (1-%d) : ", MAX);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Erreur : nombre de processus invalide.\n");
        return 1;
    }

    // 2. Saisie des processus
    for (int i = 0; i < n; i++) {

        p[i].id = i + 1;

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
    }

    // 3. Trier par temps d'arrivee
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (p[j].arrivee < p[i].arrivee) {
                Processus temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // 4. Ordonnancement FCFS
    int temps = 0;

    for (int i = 0; i < n; i++) {

        // Si aucun processus n'est encore disponible
        if (temps < p[i].arrivee) {
            temps = p[i].arrivee;
        }

        p[i].debut = temps;
        p[i].fin = p[i].debut + p[i].duree;

        p[i].sejour = p[i].fin - p[i].arrivee;
        p[i].attente = p[i].debut - p[i].arrivee;

        total_attente += p[i].attente;
        total_sejour += p[i].sejour;

        temps = p[i].fin;
    }

    // 5. Tableau des resultats
    printf("\n========== RESULTATS FCFS ==========\n");

    printf("PID\tArr\tDuree\tDebut\tFin\tAtt\tSejour\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id,
               p[i].arrivee,
               p[i].duree,
               p[i].debut,
               p[i].fin,
               p[i].attente,
               p[i].sejour);
    }

    // 6. Moyennes
    printf("\nAttente moyenne : %.2f\n",
           total_attente / n);

    printf("Sejour moyen : %.2f\n",
           total_sejour / n);

    // 7. Diagramme de Gantt
    printf("\n========== GANTT FCFS ==========\n");

    int precedent = 0;

    for (int i = 0; i < n; i++) {

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
