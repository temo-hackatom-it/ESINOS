# ESINOS — Simulateur de système d'exploitation

> **Projet semestriel — Systèmes d'Exploitation | UIR — ESIN**  
> **Langage :** C · **Environnement cible :** Linux · **Statut :** développement en équipe

## Présentation

**ESINOS** est un mini-noyau **simulé en espace utilisateur**. Il permet d'étudier plusieurs mécanismes fondamentaux des systèmes d'exploitation à travers un programme en C et une interface en ligne de commande : l'ordonnancement des processus, la gestion de la mémoire virtuelle et, en option, un mini système de fichiers.

ESINOS **n'est pas un véritable noyau amorçable** : il simule le fonctionnement de certains de ses sous-systèmes à des fins pédagogiques.

## Fonctionnalités et avancement

| Module | Fonctionnalité | État actuel |
|---|---|---|
| CPU | FCFS (First Come, First Served) | Intégré au menu |
| CPU | SJF (Shortest Job First, non préemptif) | Intégré au menu |
| CPU | RR (Round Robin) | Intégré au menu |
| CPU | Priority Scheduling (non préemptif) | Intégré au menu |
| CPU | Diagrammes de Gantt et temps d'attente / séjour moyens | Intégrés aux algorithmes CPU |
| Mémoire | Table des pages et traduction logique → physique | Code initial présent ; intégration au menu en attente |
| Mémoire | Remplacement FIFO | Code initial présent ; intégration au menu en attente |
| Mémoire | LRU et Optimal | En développement / à intégrer |
| Mémoire | TLB et EAT (Effective Access Time) | En développement / à intégrer |
| Bonus | Mini système de fichiers à base d'inodes | Optionnel ; non intégré |

> **Attention :** dans la version actuelle, les choix 2, 3 et 4 du menu principal affichent « Module en cours de developpement. » Le code mémoire existant n'est pas encore relié à l'interface générale.

## Organisation du dépôt

```text
ESINOS/
├── code/
│   ├── main.c       # Menu principal et navigation
│   ├── cpu.h        # Déclarations des fonctions CPU
│   ├── FCFS.c       # Ordonnancement FCFS
│   ├── SJF.c        # Ordonnancement SJF
│   ├── RR.c         # Ordonnancement Round Robin
│   ├── PS.c         # Ordonnancement par priorité
│   ├── memory.h     # Interface du module mémoire (version initiale)
│   ├── memory.c     # Pagination et traduction d'adresses
│   └── FIFO.c       # Remplacement FIFO
└── .gitignore
```

Les autres modules et les livrables seront ajoutés au fil de l'avancement du projet.

## Prérequis

- Un environnement **Linux** (Ubuntu, WSL Ubuntu ou équivalent).
- Un compilateur C, par exemple **GCC**.
- Un terminal.

Vérifier GCC :

```bash
gcc --version
```

Sur Ubuntu, si GCC n'est pas installé :

```bash
sudo apt update
sudo apt install build-essential
```

## Installation et exécution

**1. Cloner le dépôt :**

```bash
git clone https://github.com/temo-hackatom-it/ESINOS.git
cd ESINOS/code
```

**2. Compiler la version CPU actuellement intégrée :**

```bash
gcc -std=c11 -Wall -Wextra main.c FCFS.c SJF.c RR.c PS.c -o esinos
```

**3. Lancer ESINOS :**

```bash
./esinos
```

La commande ci-dessus compile le menu et les quatre algorithmes CPU. Elle **n'intègre pas encore les fichiers mémoire**, car ceux-ci ne sont pas appelés depuis `main.c`.

## Utilisation

Le menu principal actuel propose :

```text
=================================
          ESINOS SYSTEM
=================================
1. Ordonnancement CPU
2. Gestion de la memoire
3. Remplacement de pages
4. TLB et performances
0. Quitter
```

Choisir **1** pour accéder aux algorithmes CPU :

```text
===== ORDONNANCEMENT CPU =====
1. FCFS
2. SJF
3. Round Robin
4. Priority Scheduling
0. Retour
```

Suivre les indications du programme pour saisir les processus et, selon l'algorithme, leurs temps d'arrivée, durées, priorités ou quantum. Le programme affiche les résultats et les diagrammes de Gantt. Choisir **0** pour revenir au menu précédent, puis **0** dans le menu principal pour quitter.

## Principes étudiés

- **FCFS :** exécuter les processus dans l'ordre d'arrivée.
- **SJF :** choisir parmi les processus disponibles celui dont la durée est la plus courte.
- **Round Robin :** partager le processeur par tranches de temps (quantum).
- **Priority Scheduling :** choisir parmi les processus disponibles celui dont la priorité est la plus élevée (dans notre implémentation, la plus petite valeur numérique).
- **Pagination :** découper la mémoire virtuelle en pages et la mémoire physique en cadres.
- **FIFO / LRU / Optimal :** comparer différentes politiques de remplacement de pages.
- **TLB et EAT :** étudier l'accélération de la traduction des adresses et le temps moyen d'accès mémoire.

## Démonstration prévue

Conformément au sujet du projet :

1. Afficher les diagrammes de Gantt **FCFS, SJF et RR**.
2. Montrer l'éviction des pages **FIFO étape par étape**, puis comparer avec **LRU**.
3. Si le bonus est réalisé, démontrer la création, la lecture et la suppression de fichiers ainsi que la table d'inodes.

Les autres fonctionnalités obligatoires (Priority, Optimal, TLB, EAT et traduction d'adresses) doivent également être maîtrisées et peuvent être présentées à la demande.

## Livrables du projet

Le dépôt final doit comprendre :

- `code/` — sources C commentées ;
- `README.md` — présentation et instructions d'exécution ;
- `report.pdf` — rapport de **2 à 4 pages** : approche, difficultés, résultats et liens avec le cours ;
- `demo.mp4` — démonstration vidéo **avec caméra ouverte**, présentation du travail et explication du code.

## Travail en équipe

Projet réalisé en groupe dans le cadre du module **Systèmes d'Exploitation** à l'**Université Internationale de Rabat (UIR), ESIN**.

Les contributions sont organisées autour de l'ordonnancement CPU, de la gestion mémoire, du TLB/EAT, de l'intégration et du système de fichiers optionnel.

## Évolution du projet

Ce README décrit l'état du dépôt au moment de sa rédaction. Il sera mis à jour après l'intégration des algorithmes mémoire, des TLB/EAT et, le cas échéant, du mini système de fichiers. Les commandes de compilation définitives seront alors adaptées.
