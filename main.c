#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "baseFunctions.h"
#include "combatFunctions.h"
#include "movesFunctions.h"

void main() {
    int choice;
    printf("-----Bienvenue sur CY-Fighter !-----\n");
    printf("    ------------MENU------------    \n");
    printf("1: Jouer contre un adversaire\n");
    printf("2: Jouer contre un adversaire en mode IA\n");
    printf("3: Afficher la liste des personnages\n");
    printf("4: Quitter\n");
    char teamName[200];
    int verif = 1;
    do {
        printf("Joueur 1 :\nEntrez le nom de votre équipe: ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            printf("Entrez un nom d'équipe valide.\n");
            clear_scan();
        }
    } while (verif == 0);
    team team1 = createTeam(teamName);
    do {
        printf("Joueur 2 :\nEntrez le nom de votre équipe: ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            printf("Entrez un nom d'équipe valide.\n");
            clear_scan();
        }
    } while (verif == 0);
    team team2 = createTeam(teamName);
    Interface(team1);
    Move move = getMove("spiked shield");
    printf("%s", move.name);
    printf("%s", move.description);
    printf("%s", move.type);
    printf("%d", move.power);
    printf("%d", move.accuracy);
    printf("%d", move.duration);
    printf("%d", move.cooldown);
    printf("%d", move.targets);
}
