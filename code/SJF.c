
#include <stdio.h>

int main() {
    int arrivee[3];
    int duree[3];
    int termine[3] = {0, 0, 0};

    int temps = 0;
    int nb_termines = 0;

    float total_attente = 0;
    float total_sejour = 0;
    
    // Saisie des processus
    for (int i = 0; i < 3; i++) {
        printf("Arrivee de P%d : ", i + 1);
        scanf("%d", &arrivee[i]);

        printf("Duree de P%d : ", i + 1);
        scanf("%d", &duree[i]);
    }

    while (nb_termines < 3) {
    int choix = -1;

    for (int i = 0; i < 3; i++) {
        if (termine[i] == 0 && arrivee[i] <= temps) {
            if (choix == -1 || duree[i] < duree[choix]) {
                choix = i;
            }
        }
    }


    if (choix == -1) {
    temps++;
    }

    else {
        int debut = temps;
        int fin = debut + duree[choix];
        int attente = debut - arrivee[choix];

        // NOUVEAU : calcul du sejour
        int sejour = fin - arrivee[choix];

        printf("P%d : %d -> %d\n", choix + 1, debut, fin);
        printf("Attente : %d\n", attente);

        // NOUVEAU : affichage du sejour
        printf("Sejour : %d\n", sejour);

        // NOUVEAU : addition des valeurs
        total_attente += attente;
        total_sejour += sejour;

        temps = fin;
        termine[choix] = 1;
        nb_termines++;
    }
    }
        
    printf("\nAttente moyenne : %.2f\n", total_attente / 3);
    printf("Sejour moyen : %.2f\n", total_sejour / 3);
    
    return 0;
}
