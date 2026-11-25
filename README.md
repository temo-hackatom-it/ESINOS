# ESINOS — Operating System Simulator

Simulateur de systèmes d'exploitation en C, développé dans le cadre du projet semestriel de Systems Engineering à l'Université Internationale de Rabat (ESIN).

## Fonctionnalités

- **Ordonnancement CPU** : FCFS, SJF, Round Robin, Priority Scheduling, diagrammes de Gantt, temps moyens d'attente et de rotation.
- **Gestion mémoire** : pagination, table des pages, association page-cadre et traduction des adresses logiques en adresses physiques.
- **Remplacement de pages** : FIFO, LRU, Optimal, comparaison des hits et défauts de page.
- **TLB et EAT** : cache de deux entrées avec remplacement FIFO, taux de réussite et temps effectif d'accès.

## Installation et exécution

Prérequis : Linux ou WSL, Git et GCC (C11).

```bash
git clone https://github.com/temo-hackatom-it/ESINOS.git
cd ESINOS/code
gcc -std=c11 -Wall -Wextra main.c FCFS.c SJF.c RR.c PS.c memory.c FIFO.c lru.c optimal.c tlb.c -o esinos
./esinos
```

## Menu principal

```text
1. Ordonnancement CPU
2. Gestion de la memoire
3. Remplacement de pages
4. TLB et performances (EAT)
0. Quitter
```

## Architecture du code

| Fichier | Rôle |
|---|---|
| `main.c` | Menu principal et intégration |
| `cpu.h` | Prototypes CPU |
| `FCFS.c` | First Come First Served |
| `SJF.c` | Shortest Job First |
| `RR.c` | Round Robin |
| `PS.c` | Priority Scheduling |
| `memory.h` | Constantes et prototypes mémoire |
| `memory.c` | Table des pages et traduction |
| `FIFO.c` | Remplacement FIFO |
| `lru.c` | Remplacement LRU |
| `optimal.c` | Remplacement Optimal |
| `tlb.h` | Structure et prototypes TLB |
| `tlb.c` | Simulation TLB et calcul EAT |

## Configuration mémoire

| Paramètre | Valeur |
|---|---:|
| Pages virtuelles | 6 |
| Cadres physiques | 3 |
| Taille d'une page | 100 octets |
| Mémoire virtuelle | 600 octets |
| Mémoire physique | 300 octets |
| Entrées TLB | 2 |

Le TLB utilise une table des pages fixe. L'EAT est calculé pour les accès aux pages résidentes, sans inclure le coût des défauts de page. ESINOS simule ces mécanismes en espace utilisateur : il ne constitue pas un véritable noyau.

## Objectifs pédagogiques

Comprendre les mécanismes des systèmes d'exploitation, comparer les algorithmes, développer des compétences en C et collaborer avec Git et GitHub.

## Cadre académique

- Université Internationale de Rabat — ESIN
- Module : Systems Engineering
- Projet 4 : ESINOS
- Enseignant : Pr. Ilias Tougui
- Année universitaire : 2026-2027
