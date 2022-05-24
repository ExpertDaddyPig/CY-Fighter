#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "baseFunctions.h"
#include "combatFunctions.h"
#include "movesFunctions.h"

void main() {
    int choice;
    char teamName[200];
    printf("-----Bienvenue sur CY-Fighter !-----\n");
    printf("    ------------MENU------------    \n");
    printf("1: Jouer contre un adversaire\n");
    printf("2: Jouer contre un adversaire en mode IA\n");
    printf("3: Afficher la liste des personnages\n");
    printf("4: Quitter\n");
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
    /*do {
        printf("Joueur 2 :\nEntrez le nom de votre équipe: ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            printf("Entrez un nom d'équipe valide.\n");
            clear_scan();
        }
    } while (verif == 0);
    team team2 = createTeam(teamName);*/
    Interface(team1);
    Move move;
    move = getMove("spiked shield");
    printf("\n%s\n", move.name);
    printf("%s\n", move.description);
    printf("%s\n", move.type);
    printf("%d\n", move.power);
    printf("%d\n", move.accuracy);
    printf("%d\n", move.duration);
    printf("%d\n", move.cooldown);
    printf("%d\n", move.targets);
    const char * separators = "|";
    char * strToken = strtok (move.description, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
        strToken = strtok ( NULL, separators );
    }
}
