#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "combatFunctions.h"
#include "movesFunctions.h"

#define couleur(param) printf("\033[%sm",param)

void Interface(Team ally, Team enemy) {
  int space, namespace, spaceleft;
  float percent;
  char *heros1, *heros2, *heros3, *heros4, *heros5, *heros6, *allyName, *enemyName;
  allyName = ally.teamName;
  enemyName = enemy.teamName;
  heros1 = ally.team[0].name;
  heros2 = ally.team[1].name;
  heros3 = ally.team[2].name;
  heros4 = enemy.team[0].name;
  heros5 = enemy.team[1].name;
  heros6 = enemy.team[2].name;

  // Display the two teams with their names and their fighters + their health bar. If the fighter is dead, it's displayed next to a red K.O.
  printf("┏[%s]", allyName);
  space = strlen(allyName);
  namespace = 0;
  spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros1) + strlen(heros2) + strlen(heros3) + strlen("|1|") * 3);
  for (int i = space; i < 78; i++) {
    printf("━");
  }
  printf("┓\n");
  printf("┃    ");
  printf("%s", heros1);
  for (int i = strlen(heros1); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (ally.team[0].stats.hp == 0) {
    couleur("31");
    printf("K.O.     ");
    couleur("0");
  } else {
    printf("|1|      ");
  }
  printf("%s", heros2);
  for (int i = strlen(heros2); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (ally.team[1].stats.hp == 0) {
    couleur("31");
    printf("K.O.     ");
    couleur("0");
  } else {
    printf("|2|      ");
  }
  printf("%s", heros3);
  for (int i = strlen(heros3); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (ally.team[2].stats.hp == 0) {
    couleur("31");
    printf("K.O.");
    couleur("0");
  } else {
    printf("|3| ");
  }
  printf("   ┃\n");
  printf("┃    ");
  for (int i = 0; i < 72; i++) {
    printf(" ");
  }
  printf("    ┃\n");
  printf("┃   [");
  couleur("32");
  percent = ((float)ally.team[0].stats.hp / (float)ally.team[0].stats.hpMax) * 20.0;
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]    [");
  couleur("32");
  percent = ((float)ally.team[1].stats.hp / (float)ally.team[1].stats.hpMax) * 20.0;
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]    [");
  couleur("32");
  percent = ((float)ally.team[2].stats.hp / (float)ally.team[2].stats.hpMax) * 20.0;
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]   ┃\n");
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
  printf("┏[%s]", enemyName);
  space = strlen(enemyName);
  namespace = 0;
  spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros4) + strlen(heros5) + strlen(heros6) + strlen("|1|") * 3);
  for (int i = space; i < 78; i++) {
    printf("━");
  }
  printf("┓\n");
  printf("┃    ");
  printf("%s", heros4);
  for (int i = strlen(heros4); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (enemy.team[0].stats.hp == 0) {
    couleur("31");
    printf("K.O.     ");
    couleur("0");
  } else {
    printf("|1|      ");
  }
  printf("%s", heros5);
  for (int i = strlen(heros5); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (enemy.team[1].stats.hp == 0) {
    couleur("31");
    printf("K.O.     ");
    couleur("0");
  } else {
    printf("|2|      ");
  }
  printf("%s", heros6);
  for (int i = strlen(heros6); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (enemy.team[2].stats.hp == 0) {
    couleur("31");
    printf("K.O.");
    couleur("0");
  } else {
    printf("|3| ");
  }
  printf("   ┃\n");
  printf("┃    ");
  for (int i = 0; i < 72; i++) {
    printf(" ");
  }
  printf("    ┃\n");
  percent = ((float)enemy.team[0].stats.hp / (float)enemy.team[0].stats.hpMax) * 20.0;
  printf("┃   [");
  couleur("32");
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]    [");
  percent = ((float)enemy.team[1].stats.hp / (float)enemy.team[1].stats.hpMax) * 20.0;
  couleur("32");
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]    [");
  percent = ((float)enemy.team[2].stats.hp / (float)enemy.team[2].stats.hpMax) * 20.0;
  couleur("32");
  for (int i = 0; i < 20; i++) {
    if (percent < 10) {
      couleur("33");
    }
    if (percent < 5) {
      couleur("31");
    }
    if (i < percent) {
      printf("\u25A0");
    } else {
      printf(" ");
    }
  }
  couleur("0");
  printf("]   ┃\n");
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
}

void caraInterface(Team equipe, int cara) {
  Fighter hero;
  Move move;
  int space;
  hero = equipe.team[cara];
  // Displaying the fighter's name and his moves
  printf("┏");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┓\n");
  printf("┃    ");
  printf("[%s]", hero.name);
  for (int i = strlen(hero.name) + 5; i < 79; i++) {
    printf(" ");
  }
  printf("┃\n");
  for (int j = 0; j < 2; j++) {
    printf("┃      ");
    move = getMove(hero.specials[j]);
    printf("{%d} %s | Type: %s ", j + 1, move.name, move.type);
    space = strlen(move.name) + strlen(move.type) + 1 + 17;
    for (int i = space; i < 78; i++) {
      printf(" ");
    }
    printf("┃\n");
  }
  printf("┃      ");
  printf("{3} Attaque Basique | Type: Attack");
  space = strlen("{3} Attaque Basique | Type: Attack");
  for (int i = space; i < 74; i++) {
    printf(" ");
  }
  printf("┃\n");
  printf("┃    ");
  for (int i = 0; i < 76; i++) {
    printf(" ");
  }
  printf("┃\n");
  printf("┃     ");
  couleur("33");
  printf("Pour plus d'information à propos d'une attaque, saisissez \"5\".");
  couleur("0");
  for (int i = strlen("Pour plus d'information à propos d'une attaque, saisissez \"5\".") + 6; i < 79; i++) {
    printf(" ");
  }
  printf("   ┃\n");
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
}

void movesInfos(Fighter champ) {
  Move move;
  int space;
  char buffer[100];

  // Displaying the fighter's moves, their description and their stats
  printf("[Capacités spéciales de %s]\n-------------------\n", champ.name);
  for (int j = 0; j < 2; j++) {
    printf("    ");
    Move move = getMove(champ.specials[j]);
    char *strToken1 = strtok(move.description, "|");
    char *strToken2 = strtok(NULL, "|");
    char *strToken3 = strtok(NULL, "|");
    printf("{%d} %s | Type: %s\n", j + 1, move.name, move.type);
    printf("      Statistiques:                         Description:\n");
    printf("        Puissance: %d", move.stats.power);
    sprintf(buffer, "%d", move.stats.power);
    space = strlen(buffer);
    for (int i = space; i < 30; i++) {
      printf(" ");
    }
    printf("%s\n", strToken1);
    printf("        Précision: %d", move.stats.accuracy);
    if (strToken2 != NULL) {
      sprintf(buffer, "%d", move.stats.accuracy);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n",strToken2);
    } else {
      printf("\n");
    }
    printf("        Cibles:    %d", move.stats.targets);
    if (strToken3 != NULL) {
      sprintf(buffer, "%d", move.stats.duration);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n",strToken3);
    } else {
      printf("\n");
    }
    printf("\n-------------------\n");
  }
}

Move moveChoice(Team *ally, Team *enemy, Fighter champ, int i, int *index) {
  Move move;
  int targets, choice;
  int verif = 0;
  // Displaying the fighter's moves and asking the player to choose one
  do {
    caraInterface(*ally, i);
    printf("Choississez une attaque pour %s:\n", champ.name);
    verif = scanf("%d", &choice);
    printf("Vous avez choisi la capacité numéro %d.\n", choice);
    // If the player chooses the option 4, informations about the fighter's moves are displayed and the player is asked to choose again
    if (choice == 4) {
      movesInfos(champ);
      verif = 0;
    } else {
      // If the player chooses a move, the move is returned else the basic attack is returned
      if (choice == 1) {
        move = getMove(champ.specials[0]);
        verif = 1;
      } 
      if (choice == 2) {
        move = getMove(champ.specials[1]);
        verif = 1;
      } 
      if (choice == 3) {
        strcpy(move.name, "Attaque Basique");
        strcpy(move.description, "Une attaque basique.");
        strcpy(move.type, "Attack");
        move.stats.power = champ.stats.atk;
        move.stats.accuracy = 95;
        move.stats.duration = 0;
        move.stats.turns = 0;
        move.stats.priority = 0;
        move.stats.cooldown = 0;
        move.stats.targets = 1;
        verif = 1;
      }
      if (choice <= 0 || choice > 4) {
        verif = 0;
      }
      if (verif == 0) {
        printf("Veuillez saisir un numéro de capacité spéciale valide.\n");
      }
    }
  } while (verif == 0);  
  *index = choice - 1;
  return move;
}

void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam) {
  Fighter allyFighter1, allyFighter2, allyFighter3;
  Move allyMove1, allyMove2, allyMove3;
  int targets, choice = 0, index;
  int verif = 0;
  allyFighter1 = ally->team[0];
  allyFighter2 = ally->team[1];
  allyFighter3 = ally->team[2];
  // Starting the turn
  printf("Au tour de l'équipe %s de choisir ses attaques:\n", ally->teamName);
  // Check if the fighter is alive
  if (allyFighter1.stats.hp > 0) {
    // If the fighter is alive, the player is asked to choose his move
    allyMove1 = moveChoice(ally, enemy, allyFighter1, 0, &index);
    printf("La capacité choisie est %s.\n", allyMove1.name);
    verif = 0;

    // If the move has a single target, the player is asked to choose the target
    if (allyMove1.stats.targets != 3) {
      if (strcmp(allyMove1.type, "Attack") == 0 ) {
      if (strcmp(allyMove1.name, "Thunder Flower") != 0) {
        do {
          printf("Choississez la cible de %s:\n", allyFighter1.name);
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          } else {
            verif = 1;
          }
          targets--;
          if (enemy->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        printf("La cible choisie est %s.\n", enemy->team[targets].name);
      } else {
        targets = -2;
      }
    }
      if (strcmp(allyMove1.type, "Status") == 0 || strcmp(allyMove1.type, "Buff") == 0 ) {
      if (strcmp(allyMove1.name, "Pizza") != 0 && strcmp(allyMove1.name, "Repos") != 0 && strcmp(allyMove1.name, "Croque-Scooby") != 0 && strcmp(allyMove1.name, "Kaioken") != 0) {
        printf("Choississez la cible de %s:\n", allyFighter1.name);
        do {
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          }
          targets--;
          if (ally->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        printf("La cible choisie est %s.\n", ally->team[targets].name);
      } else {
        targets = 0;
      }
    }
    } else {
      targets = -1;
    }
  }
  verif = 0;
  // Store the move and the target in the active team, a structure containing the fighter and the move which's reloaded every turn
  activeTeam[0].champ = allyFighter1;
  activeTeam[0].move = allyMove1;
  activeTeam[0].moveIndex = index;
  activeTeam[0].targets = targets;

  // Same steps for other fighters
  if (allyFighter2.stats.hp > 0) {
    allyMove2 = moveChoice(ally, enemy, allyFighter2, 1, &index);
    printf("La capacité choisie est %s.\n", allyMove2.name);
    verif = 0;
    if (allyMove2.stats.targets != 3) {
    if (strcmp(allyMove2.type, "Attack") == 0 ) {
      if (strcmp(allyMove2.name, "Thunder Flower") != 0) {
        do {
          printf("Choississez la cible de %s:\n", allyFighter2.name);
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          } else {
            verif = 1;
          }
          targets--;
          if (enemy->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        printf("La cible choisie est %s.\n", enemy->team[targets].name);
      } else {
        targets = -2;
      }
    }
    if (strcmp(allyMove2.type, "Status") == 0 || strcmp(allyMove2.type, "Buff") == 0 ) {
      if (strcmp(allyMove2.name, "Pizza") != 0 && strcmp(allyMove2.name, "Repos") != 0 && strcmp(allyMove2.name, "Croque-Scooby") != 0 && strcmp(allyMove2.name, "Kaioken") != 0) {
        printf("Choississez la cible de %s:\n", allyFighter2.name);
        do {
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          }
          if (ally->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        targets--;
        printf("La cible choisie est %s.\n", ally->team[targets].name);
      } else {
        targets = 1;
      }
    }
    } else {
      targets = -1;
    }
  }
  verif = 0;
  activeTeam[1].champ = allyFighter2;
  activeTeam[1].move = allyMove2;
  activeTeam[1].moveIndex = index;
  activeTeam[1].targets = targets;
  if (allyFighter3.stats.hp > 0) {
    allyMove3 = moveChoice(ally, enemy, allyFighter3, 2, &index);
    printf("La capacité choisie est %s.\n", allyMove3.name);
    verif = 0;
    if (allyMove3.stats.targets != 3) {
    if (strcmp(allyMove3.type, "Attack") == 0 ) {
      if (strcmp(allyMove3.name, "Thunder Flower") != 0) {
        do {
          printf("Choississez la cible de %s:\n", allyFighter3.name);
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          } else {
            verif = 1;
          }
          if (enemy->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        targets--;
        printf("La cible choisie est %s.\n", enemy->team[targets].name);
      } else {
        targets = -2;
      }
    }
    if (strcmp(allyMove3.type, "Status") == 0 || strcmp(allyMove3.type, "Buff") == 0 ) {
      if (strcmp(allyMove3.name, "Pizza") != 0 && strcmp(allyMove3.name, "Repos") != 0 && strcmp(allyMove3.name, "Croque-Scooby") != 0 && strcmp(allyMove3.name, "Kaioken") != 0) {
        printf("Choississez la cible de %s:\n", allyFighter3.name);
        do {
          verif = scanf("%d", &targets);
          if (targets > 3 || targets < 1) {
            printf("Veuillez saisir un numéro de cible valide.\n");
            verif = 0;
          }
          if (ally->team[targets].stats.hp <= 0) {
            printf("Cette cible est K.O. Veuillez en choisir une autre.\n");
            verif = 0;
          }
        } while (verif == 0);
        targets--;
        printf("La cible choisie est %s.\n", ally->team[targets].name);
      } else {
        targets = 2;
      }
    }
    } else {
      targets = -1;
    }
  }
  verif = 0;
  activeTeam[2].champ = allyFighter3;
  activeTeam[2].move = allyMove3;
  activeTeam[2].moveIndex = index;
  activeTeam[2].targets = targets;
}

void fight(Team team1, Team team2) {
  int pos1 = 0, pos2 = 0, win = 0;
  ActiveTeam activeTeam1[3], activeTeam2[3], fusedTeams[6];
  do {
    pos1 = 0;
    pos2 = 0;

    // Creating the active teams for the two teams
    turn(&team1, &team2, activeTeam1);
    turn(&team2, &team1, activeTeam2);

    // Fusing the active teams
    for (int i = 0; i < 6; i++) {
      if (i < 3) {
        fusedTeams[i] = activeTeam1[pos1];
        pos1++;
      } else {
        fusedTeams[i] = activeTeam2[pos2];
        pos2++;
      }
    }

    // Making the order for every fighter
    makeOrder(fusedTeams);

    // Affecting moves effects to targets
    actions(fusedTeams, &team1, &team2);

    // Displaying the updated teams
    Interface(team1, team2);

    // Checking if a team is dead or not
    if (team1.team[0].stats.hp <= 0 && team1.team[1].stats.hp <= 0 && team1.team[2].stats.hp <= 0) {
      if (team2.team[0].stats.hp > 0 || team2.team[1].stats.hp > 0 || team2.team[2].stats.hp > 0) {
        win = 2;
      } else {
        win = 3;
      }
    }
    if (team2.team[0].stats.hp <= 0 && team2.team[1].stats.hp <= 0 && team2.team[2].stats.hp <= 0) {
      if (team1.team[0].stats.hp > 0 || team1.team[1].stats.hp > 0 || team1.team[2].stats.hp > 0) {
        win = 1;
      } else {
        win = 3;
      }
    }
    // Repeat the fight if a team is not dead
  } while (win == 0);
  // Displaying the winner, if both teams are dead, it's a draw
  if (win == 1) {
    printf("--------------------------%s REMPORTE LE COMBAT--------------------------\n", team1.teamName);
  } else if (win == 2) {
    printf("--------------------------%s REMPORTE LE COMBAT--------------------------\n", team2.teamName);
  } else {
    printf("---------------------------------EGALITE---------------------------------\n");
  }
}