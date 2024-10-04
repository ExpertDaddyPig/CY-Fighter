#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "baseFunctions.h"
#include "combatFunctions.h"
#include "interfaceFunctions.h"
#include "movesFunctions.h"

void main() {
  int choice, combatChoice, diffChoice;
  char teamName[200];
  int verif = 1;
  // Display the menu until the user choose to quit
  do {
    system("clear");
    printf("-----Bienvenue sur CY-Fighter !-----\n");
    do {
      printf("    ------------MENU------------    \n");
      printf("1: Jouer\n2: Afficher la liste des personnages\n3: Quitter\n");
      printf("\nChoisissez une option: ");
      scanf("%d", &choice);
      clear_scan();
    } while (choice < 1 || choice > 3);
    switch (choice) {
    case 1:
      do {
        system("clear");
        printf("    -----------COMBAT-----------    \n");
        printf("1: Jouer contre un adversaire\n2: Jouer contre un "
               "ordinateur\n3: Retour\n");
        printf("\nChoisissez une option: ");
        scanf("%d", &combatChoice);
        clear_scan();
      } while (combatChoice < 1 || combatChoice > 3);
      switch (combatChoice) {
      case 1:
        printChamps();
        // Getting the team 1 name
        do {
          printf("Joueur 1 :\nEntrez le nom de votre équipe (Appuyez sur "
                 "\"entrée\" pour choisir le nom par défaut): ");
          verif = scanf("%[^\n]%*c", teamName);
          if (verif == 0) {
            strcpy(teamName, "Equipe 1");
            verif = 1;
            clear_scan();
          }
        } while (verif == 0);

        // Creating the team 1
        Team team1 = createTeam(teamName);

        // Getting the team 2 name
        do {
          printf("Joueur 2 :\nEntrez le nom de votre équipe (Appuyez sur "
                 "\"entrée\" pour choisir le nom par défaut): ");
          verif = scanf("%[^\n]%*c", teamName);
          if (verif == 0) {
            strcpy(teamName, "Equipe 2");
            verif = 1;
            clear_scan();
          }
        } while (verif == 0);

        // Creating the team 2
        Team team2 = createTeam2(teamName, team1);

        // Starting the game
        // Display the teams
        printf("\n");
        Interface(team1, team2);
        printf("\nAppuyez sur entrée pour commencer le tour.\n");
        clear_scan();
        // Launch the fight until one team is dead
        fight(team1, team2, 0);
        break;

      case 2:
        do {
          system("clear");
          printf("    ---------DIFFICULTÉ--------    \n");
          printf("1: \033[92mEASY\033[0m\n2: \033[93mNORMAL\033[0m\n3: "
                 "\033[91mHARD\033[0m\n4: Retour\n");
          printf("\nChoisissez une option: ");
          scanf("%d", &diffChoice);
          clear_scan();
        } while (diffChoice < 1 || diffChoice > 4);
        if (diffChoice == 4) {
          combatChoice = 0;
        } else if (diffChoice != 3) {
          do {
            printf("Joueur 1 :\nEntrez le nom de votre équipe (Appuyez sur "
                   "\"entrée\" pour choisir le nom par défaut): ");
            verif = scanf("%[^\n]%*c", teamName);
            if (verif == 0) {
              strcpy(teamName, "Equipe 1");
              verif = 1;
              clear_scan();
            }
          } while (verif == 0);

          // Creating the team 1
          Team team1 = createTeam(teamName);

          strcpy(teamName,
                 (diffChoice == 1) ? "Baby Bot Team" : "Basic Bot Team");

          Team team2 = createNormalBotTeam(teamName, team1);

        } else {
          strcpy(teamName, "Evil Bot Team");
          Team team1 = createHardBotTeam(teamName);

          do {
            printf("Joueur 2 :\nEntrez le nom de votre équipe (Appuyez sur "
                   "\"entrée\" pour choisir le nom par défaut): ");
            verif = scanf("%[^\n]%*c", teamName);
            if (verif == 0) {
              strcpy(teamName, "Equipe 2");
              verif = 1;
              clear_scan();
            }
          } while (verif == 0);

          Team team2 = createTeam2(teamName, team1);
        }
        printf("\n");
        Interface(team1, team2);
        printf("\nAppuyez sur entrée pour commencer le tour.\n");
        clear_scan();
        fight(team1, team2, diffChoice);
        break;

      case 3:
        system("clear");
        choice = 0;
        break;
      }
      break;
    case 2:
      // Display the list of the fighters
      printChamps();
      char answer;
      do {
        // Ask the user if he wants to see the infos of a fighter
        printf("\nVoulez vous plus d'info sur un personnage ? (O/N): ");
        do {
          scanf("%c", &answer);
          clear_scan();
        } while (answer != 'O' && answer != 'N' && answer != 'o' &&
                 answer != 'n');

        // If the user wants to see the infos of a fighter
        if (answer == 'O' || answer == 'o') {
          char name[100];
          // Ask the user for the name of the fighter
          printf("Entrez le nom ou l'aliase du personnage: ");
          scanf("%[^\n]%*c", name);

          // Convert the name to lower case
          toLowerCase(name);

          // Verify if the fighter exists
          if (verifyChamp(name) == 1) {
            // Display the infos of the fighter
            fighterInfos(name);
          } else {
            // If the fighter doesn't exist, display an error message
            printf("Ce personnage n'existe pas.\n");
          }
        } else {
          printf("\nRetour au menu principal\n\n");
          choice = 0;
        }
      } while (answer == 'O' || answer == 'o');
      break;
    }
  } while (choice != 3);
  // Exit the program
  printf("Merci d'avoir joué à CY-Fighter !\n");
  exit(0);
}
