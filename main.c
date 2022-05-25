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
    do {
        printf("Joueur 2 :\nEntrez le nom de votre équipe: ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            printf("Entrez un nom d'équipe valide.\n");
            clear_scan();
        }
    } while (verif == 0);
    team team2 = createTeam(teamName);
    Interface(team1, team2);
    /*Move move;
    move = getMove("amaterasu");
    printf("\nMove Name: %s\n", move.name);
    printf("Description:");
    char *strToken1 = strtok(move.description, "|");
    char *strToken2 = strtok(NULL, "|");
    char *strToken3 = strtok(NULL, "|");
    printf(" %s\n",strToken1);
    if (strToken2 != NULL) {
    	printf("             %s\n",strToken2);
    }
    if (strToken3 != NULL) {
    	printf("             %s\n",strToken3);
    }
    printf("Move Type: %s\n", move.type);
    printf("Power: %d\n", move.stats.power);
    printf("Accuracy: %d\n", move.stats.accuracy);
    printf("Duration: %d\n", move.stats.duration);
    printf("Cooldown: %d\n", move.stats.cooldown);
    printf("Targets: %d\n", move.stats.targets);*/
}
