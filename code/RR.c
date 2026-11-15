#include <stdio.h>

int main() {
    int duree[3];
    int restant[3];
    int quantum;

    for (int i = 0; i < 3; i++) {
        printf("Duree de P%d : ", i + 1);
        scanf("%d", &duree[i]);

        restant[i] = duree[i];
    }

    printf("Entrer le quantum : ");
    scanf("%d", &quantum);

    int temps = 0;
    int nb_termines = 0;

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
                }

                    printf("P%d : %d -> %d\n", i + 1, debut, temps);
                }
            }
        }
    
    return 0;
}
