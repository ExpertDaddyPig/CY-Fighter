#include "movesFunctions.h"
#include "attacksFunctions.h"
#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void useMove(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy, int moveIndex,
             int pos1, int pos2) {
  char *name = fighter->champ.name;
  // Use the move of the fighter depending of his
  if (strcmp(name, "Expert Daddy Pig") == 0) {
    if (moveIndex == 0) {
      pizza(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      avion(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Son Goku") == 0) {
    if (moveIndex == 0) {
      kamehameha(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      kaioken(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Hinata") == 0) {
    if (moveIndex == 0) {
      ramen(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      paume(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Knuckles") == 0) {
    if (moveIndex == 0) {
      acier(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      seisme(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Luigi") == 0) {
    if (moveIndex == 0) {
      thunder(fighters, fighter, ally, enemy, pos1, pos2);
    }
    if (moveIndex == 1) {
      boomerang(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Mario") == 0) {
    if (moveIndex == 0) {
      fire(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      ice(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Naruto") == 0) {
    if (moveIndex == 0) {
      rasengan(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      clone(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Princess Peach") == 0) {
    if (moveIndex == 0) {
      golf(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      peche(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Saitama") == 0) {
    if (moveIndex == 0) {
      boule(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      punch(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Sakura") == 0) {
    if (moveIndex == 0) {
      cherry(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      heal(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Sasuke") == 0) {
    if (moveIndex == 0) {
      katon(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      chidori(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Scooby-Doo") == 0) {
    if (moveIndex == 0) {
      croque(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      repos(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Shaggy (Sammy)") == 0) {
    if (moveIndex == 0) {
      croque(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      kamehameha(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Sonic") == 0) {
    if (moveIndex == 0) {
      spinattack(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      homming(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Tails") == 0) {
    if (moveIndex == 0) {
      hand(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      bots(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Vegeta") == 0) {
    if (moveIndex == 0) {
      flash(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      garrick(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      basic(fighters, fighter, ally, enemy);
    }
  }
}

Move getMove(char *moveName) {
  FILE *data;
  Move move;
  char file[50];
  sprintf(file, "specials_attacks/%s.txt", moveName);
  // Open the file
  fflush(stdout);
  data = fopen(file, "r");

  // Read the file if it exists, else print an error message
  if (data == NULL) {
    printf("%s n'est pas une capacité spéciale disponible.\nVeuillez réessayez "
           "avec une capacité figurant dans la liste.",
           moveName);
    exit(1);
  }
  char *name, *desc, *type, line[500];
  int pow, dur, acc, chr, tur, cd, prio, tar;
  int i = 0;

  // Store the name of the move
  fgets(line, sizeof(line), data);
  name = getValue(line);

  // Store the description of the move
  fgets(line, sizeof(line), data);
  desc = getValue(line);

  // Store the type of the move
  fgets(line, sizeof(line), data);
  type = getValue(line);

  strcpy(move.name, name);
  strcpy(move.description, desc);
  strcpy(move.type, type);

  // Store the stats of the move depending on its type
  if (strcmp(move.type, "Attack") == 0) {
    fscanf(data,
           "power: %d;\ncharge: %d;\nduration: %d;\naccuracy: %d;\ncooldown: "
           "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
           &pow, &chr, &dur, &acc, &cd, &prio, &tur, &tar);
    move.stats.power = pow;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  if (strcmp(move.type, "Status") == 0) {
    fscanf(data,
           "charge: %d;\nduration: %d;\nheal: %d;\naccuracy: %d;\ncooldown: "
           "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
           &chr, &dur, &pow, &acc, &cd, &prio, &tur, &tar);
    move.stats.power = pow;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  if (strcmp(move.type, "Buff") == 0) {
    fscanf(data,
           "charge: %d;\nduration: %d;\naccuracy: %d;\ncooldown: "
           "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
           &chr, &dur, &acc, &cd, &prio, &tur, &tar);
    move.stats.power = 0;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  fclose(data);
  return move;
}

void actions(ActiveTeam *fighters, Team *ally, Team *enemy) {
  int target1, target2, verif, pos1 = 0, pos2 = 0;
  srand(time(NULL));
  // Executing all the actions of the active team
  for (int i = 0; i < 6; i++) {
    if (fighters[i].alive == 1) {
      // Check if the fighter is alive to use his move
      printf("Tour de %s.\n", fighters[i].champ.name);
      verif = verifyTeam(fighters[i].champ, *enemy);
      // Check in which team the fighter is to display the correct targets
      if (verif == 0) {
        // If the targets value is -1, it means that the move affect all the
        // enemies or all the allies
        if (fighters[i].targets == -1) {
          if (strcmp(fighters[i].move.type, "Attack") == 0) {
            printf("%s utilise %s sur l'équipe adverse.\n",
                   fighters[i].champ.name, fighters[i].move.name);
          } else {
            printf("%s utilise %s sur son équipe.\n", fighters[i].champ.name,
                   fighters[i].move.name);
          }
        } else if (fighters[i].targets ==
                   -2) { // If the targets value is -2, it means that the move a
                         // special move that affect two random targets in the
                         // enemy team
          target1 = rand() % 3;
          pos1 = target1;
          do {
            target2 = rand() % 3;
          } while (target1 == target2);
          pos2 = target2;
          printf("%s utilise %s sur %s et %s.\n", fighters[i].champ.name,
                 fighters[i].move.name, enemy->team[target1].name,
                 enemy->team[target2].name);
        } else {
          // Check if the target is the fighter itself
          if (strcmp(fighters[i].champ.name,
                     enemy->team[fighters[i].targets].name) == 0) {
            printf("%s utilise %s.\n", fighters[i].champ.name,
                   fighters[i].move.name);
          } else {
            printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                   fighters[i].move.name,
                   enemy->team[fighters[i].targets].name);
          }
        }
      } else {
        // Same as above but if the fighter is in the enemy team
        if (fighters[i].targets == -1) {
          if (strcmp(fighters[i].move.type, "Attack") == 0) {
            printf("%s utilise %s sur l'équipe adverse.\n",
                   fighters[i].champ.name, fighters[i].move.name);
          } else {
            printf("%s utilise %s sur son équipe.\n", fighters[i].champ.name,
                   fighters[i].move.name);
          }
        } else if (fighters[i].targets == -2) {
          target1 = rand() % 3;
          pos1 = target1;
          do {
            target2 = rand() % 3;
          } while (target1 == target2);
          pos2 = target2;
          printf("%s utilise %s sur %s et %s.\n", fighters[i].champ.name,
                 fighters[i].move.name, ally->team[target1].name,
                 ally->team[target2].name);
        } else {
          if (strcmp(fighters[i].champ.name,
                     ally->team[fighters[i].targets].name) == 0) {
            printf("%s utilise %s.\n", fighters[i].champ.name,
                   fighters[i].move.name);
          } else {
            printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                   fighters[i].move.name, ally->team[fighters[i].targets].name);
          }
        }
      }
      // Use the move of the fighter on his targets
      useMove(fighters, &fighters[i], ally, enemy, fighters[i].moveIndex, pos1, pos2);
      printf("\n");
    } else {
      printf("%s est K.O. et ne peut plus agir.\n\n", fighters[i].champ.name);
    }
  }
}