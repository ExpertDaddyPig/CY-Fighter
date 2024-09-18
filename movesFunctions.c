#include "movesFunctions.h"
#include "attacksFunctions.h"
#include "ultimateFunctions.h"
#include "baseFunctions.h"
#include "effectsFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void useMove(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy,
             int moveIndex, int pos1, int pos2) {
  if (moveIndex == 3) {
    basic(fighters, fighter, ally, enemy);
    return;
  }
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
      marteau(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      expert(fighters, fighter, ally, enemy);
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
      instant(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      saiyan(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Hinata") == 0) {
    if (moveIndex == 0) {
      chakra(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      paume(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      poings(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      byakugan(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Knuckles") == 0) {
    if (moveIndex == 0) {
      hook(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      heat(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      spinattack(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      meteor(fighters, fighter, ally, enemy);
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
      green(fighters, fighter, ally, enemy, pos1);
    }
    if (moveIndex == 4) {
      star(fighters, fighter, ally, enemy);
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
      red(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      star(fighters, fighter, ally, enemy);
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
      rasenshuriken(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      kyubi(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Princess Peach") == 0) {
    if (moveIndex == 0) {
      golf(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      vegetable(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      toad(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      blossom(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Saitama") == 0) {
    if (moveIndex == 0) {
      sneeze(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      punch(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      headbutt(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      serious(fighters, fighter, ally, enemy);
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
      rebirth(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      blizzard(fighters, fighter, ally, enemy);
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
      amaterasu(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      susano(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Scooby") == 0) {
    if (moveIndex == 0) {
      croque(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      repos(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      charge(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      mystery(fighters, fighter, ally, enemy);
    }
  }
  if (strcmp(name, "Shaggy") == 0) {
    if (moveIndex == 0) {
      croque(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 1) {
      kamehameha(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 2) {
      flick(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      ultra(fighters, fighter, ally, enemy);
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
      lightspeed(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      super(fighters, fighter, ally, enemy);
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
      tails(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      laser(fighters, fighter, ally, enemy);
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
      pride(fighters, fighter, ally, enemy);
    }
    if (moveIndex == 4) {
      saiyan(fighters, fighter, ally, enemy);
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
    move.stats.charge = chr;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  if (strcmp(move.type, "Heal") == 0) {
    fscanf(data,
           "charge: %d;\nduration: %d;\nheal: %d;\naccuracy: %d;\ncooldown: "
           "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
           &chr, &dur, &pow, &acc, &cd, &prio, &tur, &tar);
    move.stats.power = pow;
    move.stats.charge = chr;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  if (strcmp(move.type, "Buff") == 0) {
    fscanf(data,
           "power: %d;\ncharge: %d;\nduration: %d;\naccuracy: %d;\ncooldown: "
           "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
           &pow, &chr, &dur, &acc, &cd, &prio, &tur, &tar);
    move.stats.power = pow;
    move.stats.charge = chr;
    move.stats.duration = dur;
    move.stats.accuracy = acc;
    move.stats.cooldown = cd;
    move.stats.priority = prio;
    move.stats.turns = tur;
    move.stats.targets = tar;
  }
  if (strcmp(move.type, "Debuff") == 0) {
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
  fclose(data);
  return move;
}

Move getUltimate(char *moveName) {
  FILE *data;
  Move move;
  char file[50];
  sprintf(file, "ultimate_abilities/%s.txt", moveName);
  // Open the file
  fflush(stdout);
  data = fopen(file, "r");

  // Read the file if it exists, else print an error message
  if (data == NULL) {
    printf("%s n'est pas une capacité ultime disponible.\nVeuillez réessayez "
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
  fscanf(data,
         "power: %d;\ncharge: %d;\nduration: %d;\naccuracy: %d;\ncooldown: "
         "%d;\npriority: %d;\nturn: %d;\ntargets: %d;\n",
         &pow, &chr, &dur, &acc, &cd, &prio, &tur, &tar);
  move.stats.power = pow;
  move.stats.charge = chr;
  move.stats.duration = dur;
  move.stats.accuracy = acc;
  move.stats.cooldown = cd;
  move.stats.priority = prio;
  move.stats.turns = tur;
  move.stats.targets = tar;
  fclose(data);
  return move;
}

ActiveTeam *actions(ActiveTeam *fighters, Team *ally, Team *enemy) {
  int target1, target2, verif, pos1 = 0, pos2 = 0, freeze, sleep, charge;
  Effect *effect;
  srand(time(NULL));
  // Executing all the actions of the active team
  for (int i = 0; i < 6; i++) {
    if (fighters[i].alive == 1) {
      // Check if the fighter is alive to use his move
      freeze = searchEffect(&fighters[i], "Gel");
      sleep = searchEffect(&fighters[i], "Sommeil");
      charge = searchEffect(&fighters[i], "Charge");
      if (charge == 0) {
        effect = returnEffect(fighters[i].debuffs, "Charge");
        if (effect->duration == -1) {
          fighters[i].debuffs = deleteEffect(&fighters[i].debuffs, "Charge");
          charge = 1;
        }
      }
      if (freeze != 0 && sleep != 0 && charge != 0) {
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
          } else if (fighters[i].targets == -2) {
            // If the targets value is -2, it means that the move
            // a special move that affect two random targets in
            // the enemy team
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
            if (fighters[i].targets == -3) {
              printf("%s utilise %s.\n", fighters[i].champ.name,
                     fighters[i].move.name);
            } else {
              if (strcmp(fighters[i].move.type, "Attack") == 0) {
                printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                       fighters[i].move.name,
                       enemy->team[fighters[i].targets].name);
              } else {
                if (strcmp(ally->team[fighters[i].targets].name, fighters[i].champ.name) != 0) {
                  printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                         fighters[i].move.name,
                         ally->team[fighters[i].targets].name);
                } else {
                  printf("%s utilise %s.\n", fighters[i].champ.name,
                         fighters[i].move.name);
                }
              }
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
            if (strcmp(fighters[i].move.name, "Thunder Flower") != 0)
              printf("%s utilise %s sur %s et %s.\n", fighters[i].champ.name,
                     fighters[i].move.name, ally->team[target1].name,
                     ally->team[target2].name);
          } else {
            if (fighters[i].targets == -3) {
              printf("%s utilise %s.\n", fighters[i].champ.name,
                     fighters[i].move.name);
            } else {
              if (strcmp(fighters[i].move.type, "Attack") == 0) {
                printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                       fighters[i].move.name,
                       ally->team[fighters[i].targets].name);
              } else {
                if (strcmp(enemy->team[fighters[i].targets].name, fighters[i].champ.name) != 0) {
                  printf("%s utilise %s sur %s.\n", fighters[i].champ.name,
                         fighters[i].move.name,
                         enemy->team[fighters[i].targets].name);
                } else {
                  printf("%s utilise %s.\n", fighters[i].champ.name,
                         fighters[i].move.name);
                }
              }
            }
          }
        }
        // Use the move of the fighter on his targets
        useMove(fighters, &fighters[i], ally, enemy, fighters[i].moveIndex,
                pos1, pos2);
        printf("\n");
      } else {
        (charge != 0)
            ? printf("%s est %s et ne peut pas agir.\n\n",
                     fighters[i].champ.name,
                     sleep == 0 ? "endormi(e)" : "gelé(e)")
            : printf("%s charge son attaque.\n\n", fighters[i].champ.name);
      }
    } else {
      printf("%s est K.O. et ne peut plus agir.\n\n", fighters[i].champ.name);
    }
  }
  return fighters;
}