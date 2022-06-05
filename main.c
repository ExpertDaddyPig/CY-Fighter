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
        printf("Joueur 1 :\nEntrez le nom de votre équipe (Appuyez sur \"entrée\" pour choisir le nom par défaut): ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            strcpy(teamName, "Equipe 1");
            verif = 1;
            clear_scan();
        }
    } while (verif == 0);
    Team team1 = createTeam(teamName);
    do {
        printf("Joueur 2 :\nEntrez le nom de votre équipe (Appuyez sur \"entrée\" pour choisir le nom par défaut): ");
        verif = scanf("%[^\n]%*c", teamName);
        if (verif == 0) {
            strcpy(teamName, "Equipe 2");
            verif = 1;
            clear_scan();
        }
    } while (verif == 0);
    Team team2 = createTeam2(teamName, team1);
    Interface(team1, team2);
    fight(team1, team2);
}
