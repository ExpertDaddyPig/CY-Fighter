#include "combatFunctions.h"
#include "baseFunctions.h"
#include "effectsFunctions.h"
#include "interfaceFunctions.h"
#include "movesFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkHealthy(Fighter champ) {
  if (champ.stats.hp > (int)(champ.stats.hpMax * 0.4))
    return 0;
  return 1;
}

void activeCooldown(ActiveTeam *activeFighter, int champIndex) {
  if (activeFighter->moveIndex != 4) {
    printf("La capacité %s est maintenant en cours de récupération.\n",
           activeFighter->move.name);
    activeFighter->cooldowns[activeFighter->moveIndex] =
        activeFighter->move.stats.cooldown;
  } else {
    printf("La capacité ultime %s est maintenant en cours de chargement.\n",
           activeFighter->move.name);
    activeFighter->cooldowns[activeFighter->moveIndex - 1] =
        activeFighter->move.stats.cooldown;
  }
}

void desactiveCooldown(ActiveTeam *activeFighter, int champIndex) {
  if (activeFighter->moveIndex != 4) {
    activeFighter->cooldowns[activeFighter->moveIndex] = -1;
  } else {
    activeFighter->cooldowns[activeFighter->moveIndex - 1] = -1;
  }
}

Move moveChoice(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam activeTeam[]) {
  Move move;
  Fighter champ;
  int targets, choice;
  int verif = 0;

  // Displaying the fighter's moves and asking the player to choose one
  do {
    champ = ally->team[*i];
    caraInterface(*ally, *i, activeTeam);
    printf("Choississez une attaque pour %s:\n", champ.name);
    verif = scanf("%d", &choice);
    printf("Vous avez choisi la capacité numéro %d.\n", choice);
    // If the player chooses the option 6, informations about the fighter's
    // moves are displayed and the player is asked to choose again
    if (choice == 0 && i != 0) {
      *i = *i - 1;
      strcpy(move.name, "Retour");
      strcpy(move.description, " ");
      strcpy(move.type, " ");
      move.stats.power = 0;
      move.stats.accuracy = 0;
      move.stats.duration = -1;
      move.stats.charge = -1;
      move.stats.turns = 0;
      move.stats.priority = 0;
      move.stats.cooldown = -1;
      move.stats.targets = 1;
      verif = 1;
    } else if (choice == 6) {
      movesInfos(champ);
      verif = 0;
    } else if (choice == 7) {
      buffsInfos(activeTeam[*i]);
      verif = 0;
    } else if (choice == 8) {
      champInfos(champ, activeTeam[*i]);
      verif = 0;
    } else if (choice == 9) {
      Interface(*ally, *enemy);
      verif = 0;
    } else {
      // If the player chooses a move, the move is returned else the basic
      // attack is returned
      if (choice <= 3) {
        if (activeTeam[*i].cooldowns[choice - 1] > -1) {
          printf("Cette capacité est en cours de récuperation. %d tours "
                 "restants.\nVeuillez en "
                 "choisir une autre.\n",
                 activeTeam[*i].cooldowns[choice - 1] + 1);
          verif = 0;
        } else {
          move = getMove(champ.specials[choice - 1]);
          verif = 1;
        }
      }
      if (choice == 4) {
        strcpy(move.name, "Attaque Basique");
        strcpy(move.description, "Une attaque basique.");
        strcpy(move.type, "Attack");
        move.stats.power = champ.stats.atk / 10;
        move.stats.accuracy = 50;
        move.stats.duration = -1;
        move.stats.charge = -1;
        move.stats.turns = 0;
        move.stats.priority = 0;
        move.stats.cooldown = 0;
        move.stats.targets = 1;
        verif = 1;
      }
      if (choice == 5) {
        if (activeTeam[*i].cooldowns[choice - 2] > -1) {
          printf("La capacité ultime n'est pas prête. %d tours "
                 "restants avant utilisation.\n",
                 activeTeam[*i].cooldowns[choice - 2] + 1);
          verif = 0;
        } else {
          move = getUltimate(champ.ultimate);
          verif = 1;
        }
      }
      if (choice < 0 || choice > 6) {
        verif = 0;
      }
      if (verif == 0) {
        printf("Veuillez saisir une option valide.\n");
      }
    }
  } while (verif == 0);
  *index = choice - 1;
  return move;
}

Move moveChoiceBot(Team *ally, Team *enemy, int *i, int *index,
                   ActiveTeam activeTeam[], int bot) {
  Move move, strongestHealShield, strongestAttack, longestBuff;
  Fighter champ;
  int targets, choice, healthy, killable, statusMove[4] = {0, 0, 0, 0};
  int verif = 0;
  strcpy(strongestHealShield.name, "None");
  strcpy(strongestHealShield.description, "None.");
  strcpy(strongestHealShield.type, "None");
  strongestHealShield.stats.power = 0;
  strongestHealShield.stats.accuracy = 0;
  strongestHealShield.stats.duration = 0;
  strongestHealShield.stats.charge = 0;
  strongestHealShield.stats.turns = 0;
  strongestHealShield.stats.priority = 0;
  strongestHealShield.stats.cooldown = 0;
  strongestHealShield.stats.targets = 0;

  switch (bot) {
  case 1:
    do {
      champ = ally->team[*i];
      choice = rand() % 5;
      if (choice <= 3) {
        if (activeTeam[*i].cooldowns[choice - 1] > -1) {
          verif = 0;
        } else {
          move = getMove(champ.specials[choice - 1]);
          verif = 1;
        }
      }
      if (choice == 4) {
        strcpy(move.name, "Attaque Basique");
        strcpy(move.description, "Une attaque basique.");
        strcpy(move.type, "Attack");
        move.stats.power = champ.stats.atk / 10;
        move.stats.accuracy = 50;
        move.stats.duration = -1;
        move.stats.charge = -1;
        move.stats.turns = 0;
        move.stats.priority = 0;
        move.stats.cooldown = 0;
        move.stats.targets = 1;
        verif = 1;
      }
      if (choice == 5) {
        if (activeTeam[*i].cooldowns[choice - 2] > -1) {
          verif = 0;
        } else {
          move = getUltimate(champ.ultimate);
          verif = 1;
        }
      }
      if (choice < 0 || choice > 5) {
        verif = 0;
      }
    } while (verif == 0);
    *index = choice - 1;
    break;

  case 2:
    champ = ally->team[*i];
    if (strcmp(champ.type, "Support") == 0) {
      for (int j = 0; j < 3; j++) {
        if (activeTeam[*i].cooldowns[j] <= -1) {
          move = getMove(champ.specials[j]);
          if (strcmp(move.type, "Heal") == 0 ||
              strcmp(move.type, "Buff") == 0 ||
              strcmp(move.type, "Shield") == 0) {
            if (strcmp(move.type, "Heal") == 0) {
              if (move.stats.targets > 1) {
                statusMove[j] = 2;
              } else {
                statusMove[j] = 1;
              }
            } else if (strcmp(move.type, "Shield") == 0) {
              if (move.stats.targets > 1) {
                statusMove[j] = 4;
              } else {
                statusMove[j] = 3;
              }
            } else {
              if (move.stats.targets > 1) {
                statusMove[j] = 6;
              } else {
                statusMove[j] = 5;
              }
            }
          }
        }
      }
      if (activeTeam[*i].cooldowns[3] <= -1) {
        move = getMove(champ.ultimate);
        if (strcmp(move.type, "Heal") == 0 || strcmp(move.type, "Buff") == 0 ||
            strcmp(move.type, "Shield") == 0) {
          if (strcmp(move.type, "Heal") == 0) {
            if (move.stats.targets > 1) {
              statusMove[3] = 2;
            } else {
              statusMove[3] = 1;
            }
          } else if (strcmp(move.type, "Shield") == 0) {
            if (move.stats.targets > 1) {
              statusMove[3] = 4;
            } else {
              statusMove[3] = 3;
            }
          } else {
            if (move.stats.targets > 1) {
              statusMove[3] = 6;
            } else {
              statusMove[3] = 5;
            }
          }
        }
      }
      if (statusMove[0] + statusMove[1] + statusMove[2] + statusMove[3] > 0) {
        for (int j = 0; j < 4; j++) {
          if (j != 3) {
            if (statusMove[j] != 0 && statusMove[j] <= 2) {
              if (getMove(champ.specials[j]).stats.power >
                  strongestHealShield.stats.power) {
                strongestHealShield = getMove(champ.specials[j]);
              }
            } else if (statusMove[j] <= 4) {
              if (getMove(champ.specials[j]).stats.power > 0) {
                if (getMove(champ.specials[j]).stats.power >
                    strongestHealShield.stats.power) {
                  strongestHealShield = getMove(champ.specials[j]);
                }
              } else {
                if ((int)((-getMove(champ.specials[j]).stats.power / 100.0) *
                          champ.stats.hpMax) >
                    strongestHealShield.stats.power) {
                  strongestHealShield = getMove(champ.specials[j]);
                }
              }
            }
          } else {
            if (statusMove[j] != 0 && statusMove[j] <= 2) {
              if (getMove(champ.ultimate).stats.power >
                  strongestHealShield.stats.power) {
                strongestHealShield = getMove(champ.ultimate);
              }
            } else if (statusMove[j] <= 4) {
              if (getMove(champ.ultimate).stats.power > 0) {
                if (getMove(champ.ultimate).stats.power >
                    strongestHealShield.stats.power) {
                  strongestHealShield = getMove(champ.ultimate);
                }
              } else {
                if ((int)((-getMove(champ.ultimate).stats.power / 100.0) * champ.stats.hpMax) >
                    strongestHealShield.stats.power) {
                  strongestHealShield = getMove(champ.ultimate);
                }
              }
            }
          }
        }
      }
    }
    break;

  case 3:

    break;

  default:
    do {
      champ = ally->team[*i];
      choice = rand() % 5;
      if (choice <= 3) {
        if (activeTeam[*i].cooldowns[choice - 1] > -1) {
          verif = 0;
        } else {
          move = getMove(champ.specials[choice - 1]);
          verif = 1;
        }
      }
      if (choice == 4) {
        strcpy(move.name, "Attaque Basique");
        strcpy(move.description, "Une attaque basique.");
        strcpy(move.type, "Attack");
        move.stats.power = champ.stats.atk / 10;
        move.stats.accuracy = 50;
        move.stats.duration = -1;
        move.stats.charge = -1;
        move.stats.turns = 0;
        move.stats.priority = 0;
        move.stats.cooldown = 0;
        move.stats.targets = 1;
        verif = 1;
      }
      if (choice == 5) {
        if (activeTeam[*i].cooldowns[choice - 2] > -1) {
          verif = 0;
        } else {
          move = getUltimate(champ.ultimate);
          verif = 1;
        }
      }
      if (choice < 0 || choice > 5) {
        verif = 0;
      }
    } while (verif == 0);
    *index = choice - 1;
    break;
  }

  // Displaying the fighter's moves and asking the player to choose one
  do {
    champ = ally->team[*i];
    choice = rand() % 5;
    if (choice <= 3) {
      if (activeTeam[*i].cooldowns[choice - 1] > -1) {
        printf("Cette capacité est en cours de récuperation. %d tours "
               "restants.\nVeuillez en "
               "choisir une autre.\n",
               activeTeam[*i].cooldowns[choice - 1] + 1);
        verif = 0;
      } else {
        move = getMove(champ.specials[choice - 1]);
        verif = 1;
      }
    }
    if (choice == 4) {
      strcpy(move.name, "Attaque Basique");
      strcpy(move.description, "Une attaque basique.");
      strcpy(move.type, "Attack");
      move.stats.power = champ.stats.atk / 10;
      move.stats.accuracy = 50;
      move.stats.duration = -1;
      move.stats.charge = -1;
      move.stats.turns = 0;
      move.stats.priority = 0;
      move.stats.cooldown = 0;
      move.stats.targets = 1;
      verif = 1;
    }
    if (choice == 5) {
      if (activeTeam[*i].cooldowns[choice - 2] > -1) {
        printf("La capacité ultime n'est pas prête. %d tours "
               "restants avant utilisation.\n",
               activeTeam[*i].cooldowns[choice - 2] + 1);
        verif = 0;
      } else {
        move = getUltimate(champ.ultimate);
        verif = 1;
      }
    }
    if (choice < 0 || choice > 5) {
      verif = 0;
    }
  } while (verif == 0);
  *index = choice - 1;
  return move;
}

void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam) {
  Effect *effect = NULL;
  Fighter allyFighter;
  Move allyMove;
  int targets, choice = 0, index;
  int verif = 0, freeze, sleep, charge;

  // Starting the turn
  printf("Au tour de l'équipe %s de choisir ses attaques:\n\n", ally->teamName);
  for (int i = 0; i < 3; i++) {
    // Check if the fighter is alive
    if (ally->team[i].stats.hp > 0) {
      freeze = searchEffect(&activeTeam[i], "Gel");
      sleep = searchEffect(&activeTeam[i], "Sommeil");
      if (freeze != 0 && sleep != 0) {
        charge = searchEffect(&activeTeam[i], "Charge");
        if (charge != 0) {
          // If the fighter is alive, the player is asked to choose his move
          activeTeam[i].champ = ally->team[i];
          allyMove = moveChoice(ally, enemy, &i, &index, activeTeam);
          printf("L'option choisie est %s.\n", allyMove.name);
          verif = 0;
          // If the move has a single target, the player is asked to choose the
          // target
          if (allyMove.stats.targets != 3) {
            if (strcmp(allyMove.type, "Attack") == 0) {
              if (strcmp(allyMove.name, "Thunder Flower") != 0 &&
                  strcmp(allyMove.name, "Green Shell") != 0) {
                do {
                  SoloTeamInterface(*enemy);
                  printf("Choississez la cible de %s:\n", ally->team[i].name);
                  verif = scanf("%d", &targets);
                  if (targets > 3 || targets < 1) {
                    printf("Veuillez saisir un numéro de cible valide.\n");
                    verif = 0;
                  } else {
                    verif = 1;
                    targets--;
                    if (enemy->team[targets].stats.hp <= 0) {
                      printf("%s est K.O. Veuillez en choisir une "
                             "autre cible.\n",
                             enemy->team[targets].name);
                      verif = 0;
                    }
                  }
                } while (verif == 0);
                printf("La cible choisie est %s.\n", enemy->team[targets].name);
              } else {
                targets = -2;
              }
            }
            if (strcmp(allyMove.type, "Heal") == 0 ||
                strcmp(allyMove.type, "Buff") == 0 ||
                strcmp(allyMove.type, "Shield") == 0) {
              if (allyMove.stats.targets != -4) {
                SoloTeamInterface(*ally);
                printf("Choississez la cible de %s:\n", ally->team[i].name);
                do {
                  verif = scanf("%d", &targets);
                  if (targets > 3 || targets < 1) {
                    printf("Veuillez saisir un numéro de cible valide.\n");
                    verif = 0;
                  }
                  targets--;
                  if (ally->team[targets].stats.hp <= 0) {
                    printf("%s est K.O. Veuillez en choisir une "
                           "autre cible.\n",
                           ally->team[targets].name);
                    verif = 0;
                  }
                } while (verif == 0);
                printf("La cible choisie est %s.\n", ally->team[targets].name);
              } else if (allyMove.stats.targets == -4) {
                targets = i;
              } else {
                targets = -3;
              }
            }
          } else {
            targets = -1;
          }
          if (index != -1) {
            // Store the move and the target in the active team, a structure
            // containing the fighter and the move which's reloaded every turn
            activeTeam[i].move = allyMove;
            activeTeam[i].champIndex = i;
            activeTeam[i].moveIndex = index;
            activeTeam[i].targets = targets;
            if (activeTeam[i].cooldowns[activeTeam[i].moveIndex] == -1) {
              activeCooldown(&activeTeam[i], activeTeam[i].champIndex);
            } else if (activeTeam[i].cooldowns[activeTeam[i].moveIndex - 1] ==
                       -1) {
              activeCooldown(&activeTeam[i], activeTeam[i].champIndex);
            }
            if (activeTeam[i].move.stats.charge != -1) {
              printf(
                  "%s charge son attaque \"%s\". %d tour(s) de chargement.\n",
                  activeTeam[i].champ.name, allyMove.name,
                  allyMove.stats.charge + 1);
              activeTeam[i].debuffs = addEffect(activeTeam[i].debuffs, "charge",
                                                allyMove.stats.charge);
            }
          } else {
            if (activeTeam,
                activeTeam[i].cooldowns[activeTeam[i].moveIndex] != -1) {
              desactiveCooldown(&activeTeam[i], activeTeam[i].champIndex);
            } else if (activeTeam[i].cooldowns[activeTeam[i].moveIndex - 1] !=
                       -1) {
              desactiveCooldown(&activeTeam[i], activeTeam[i].champIndex);
            }
            printf("Retour sur %s.\n", ally->team[i].name);
            i = i - 1;
          }
        } else {
          effect = returnEffect(activeTeam[i].debuffs, "Charge");
          if (effect->duration > 0) {
            printf("%s charge son attaque \"%s\". %d tour(s) restants.\n",
                   activeTeam[i].champ.name, activeTeam[i].move.name,
                   effect->duration + 1);
          } else {
            printf("%s charge son attaque \"%s\". %s attaquera au prochain "
                   "tour.\n",
                   activeTeam[i].champ.name, activeTeam[i].move.name,
                   activeTeam[i].champ.name);
          }
        }
      } else {
        printf("%s est %s et ne peut pas agir.\n", activeTeam[i].champ.name,
               sleep == 0 ? "endormi(e)" : "gelé(e)");
      }
    } else {
      printf("%s est K.O.\n", ally->team[i].name);
    }
  }
  printf("\n");
}

void turnBot(Team *ally, Team *enemy, ActiveTeam *activeTeam, int diff) {
  Effect *effect = NULL;
  Fighter allyFighter;
  Move allyMove;
  int targets, choice = 0, index;
  int verif = 0, freeze, sleep, charge;

  switch (diff) {
  case 1:

    break;

  case 2:

    break;

  case 3:

    break;

  default:

    break;
  }

  // Starting the turn
  printf("Au tour de l'équipe %s de choisir ses attaques:\n\n", ally->teamName);
  for (int i = 0; i < 3; i++) {
    // Check if the fighter is alive
    if (ally->team[i].stats.hp > 0) {
      freeze = searchEffect(&activeTeam[i], "Gel");
      sleep = searchEffect(&activeTeam[i], "Sommeil");
      if (freeze != 0 && sleep != 0) {
        charge = searchEffect(&activeTeam[i], "Charge");
        if (charge != 0) {
          // If the fighter is alive, the player is asked to choose his move
          activeTeam[i].champ = ally->team[i];
          allyMove = moveChoice(ally, enemy, &i, &index, activeTeam);
          printf("L'option choisie est %s.\n", allyMove.name);
          verif = 0;
          // If the move has a single target, the player is asked to choose the
          // target
          if (allyMove.stats.targets != 3) {
            if (strcmp(allyMove.type, "Attack") == 0) {
              if (strcmp(allyMove.name, "Thunder Flower") != 0 &&
                  strcmp(allyMove.name, "Green Shell") != 0) {
                do {
                  SoloTeamInterface(*enemy);
                  printf("Choississez la cible de %s:\n", ally->team[i].name);
                  verif = scanf("%d", &targets);
                  if (targets > 3 || targets < 1) {
                    printf("Veuillez saisir un numéro de cible valide.\n");
                    verif = 0;
                  } else {
                    verif = 1;
                    targets--;
                    if (enemy->team[targets].stats.hp <= 0) {
                      printf("%s est K.O. Veuillez en choisir une "
                             "autre cible.\n",
                             enemy->team[targets].name);
                      verif = 0;
                    }
                  }
                } while (verif == 0);
                printf("La cible choisie est %s.\n", enemy->team[targets].name);
              } else {
                targets = -2;
              }
            }
            if (strcmp(allyMove.type, "Heal") == 0 ||
                strcmp(allyMove.type, "Buff") == 0 ||
                strcmp(allyMove.type, "Shield") == 0) {
              if (allyMove.stats.targets != -4) {
                SoloTeamInterface(*ally);
                printf("Choississez la cible de %s:\n", ally->team[i].name);
                do {
                  verif = scanf("%d", &targets);
                  if (targets > 3 || targets < 1) {
                    printf("Veuillez saisir un numéro de cible valide.\n");
                    verif = 0;
                  }
                  targets--;
                  if (ally->team[targets].stats.hp <= 0) {
                    printf("%s est K.O. Veuillez en choisir une "
                           "autre cible.\n",
                           ally->team[targets].name);
                    verif = 0;
                  }
                } while (verif == 0);
                printf("La cible choisie est %s.\n", ally->team[targets].name);
              } else if (allyMove.stats.targets == -4) {
                targets = i;
              } else {
                targets = -3;
              }
            }
          } else {
            targets = -1;
          }
          if (index != -1) {
            // Store the move and the target in the active team, a structure
            // containing the fighter and the move which's reloaded every turn
            activeTeam[i].move = allyMove;
            activeTeam[i].champIndex = i;
            activeTeam[i].moveIndex = index;
            activeTeam[i].targets = targets;
            if (activeTeam[i].cooldowns[activeTeam[i].moveIndex] == -1) {
              activeCooldown(&activeTeam[i], activeTeam[i].champIndex);
            } else if (activeTeam[i].cooldowns[activeTeam[i].moveIndex - 1] ==
                       -1) {
              activeCooldown(&activeTeam[i], activeTeam[i].champIndex);
            }
            if (activeTeam[i].move.stats.charge != -1) {
              printf(
                  "%s charge son attaque \"%s\". %d tour(s) de chargement.\n",
                  activeTeam[i].champ.name, allyMove.name,
                  allyMove.stats.charge + 1);
              activeTeam[i].debuffs = addEffect(activeTeam[i].debuffs, "charge",
                                                allyMove.stats.charge);
            }
          } else {
            if (activeTeam,
                activeTeam[i].cooldowns[activeTeam[i].moveIndex] != -1) {
              desactiveCooldown(&activeTeam[i], activeTeam[i].champIndex);
            } else if (activeTeam[i].cooldowns[activeTeam[i].moveIndex - 1] !=
                       -1) {
              desactiveCooldown(&activeTeam[i], activeTeam[i].champIndex);
            }
            printf("Retour sur %s.\n", ally->team[i].name);
            i = i - 1;
          }
        } else {
          effect = returnEffect(activeTeam[i].debuffs, "Charge");
          if (effect->duration > 0) {
            printf("%s charge son attaque \"%s\". %d tour(s) restants.\n",
                   activeTeam[i].champ.name, activeTeam[i].move.name,
                   effect->duration + 1);
          } else {
            printf("%s charge son attaque \"%s\". %s attaquera au prochain "
                   "tour.\n",
                   activeTeam[i].champ.name, activeTeam[i].move.name,
                   activeTeam[i].champ.name);
          }
        }
      } else {
        printf("%s est %s et ne peut pas agir.\n", activeTeam[i].champ.name,
               sleep == 0 ? "endormi(e)" : "gelé(e)");
      }
    } else {
      printf("%s est K.O.\n", ally->team[i].name);
    }
  }
  printf("\n");
}

void fight(Team team1, Team team2, int bot) {
  int pos1 = 0, pos2 = 0, win = 0;
  ActiveTeam *activeTeam1 = malloc(3 * sizeof(ActiveTeam)),
             *activeTeam2 = malloc(3 * sizeof(ActiveTeam)),
             *fusedTeams = malloc(6 * sizeof(ActiveTeam));
  Move ulti;
  for (int j = 0; j < 3; j++) {
    activeTeam1[j].alive = 1;
    activeTeam2[j].alive = 1;
    activeTeam1[j].buffs = NULL;
    activeTeam2[j].buffs = NULL;
    activeTeam1[j].debuffs = NULL;
    activeTeam2[j].debuffs = NULL;
    for (int i = 0; i < 4; i++) {
      if (i != 3) {
        activeTeam1[j].cooldowns[i] = -1;
        activeTeam2[j].cooldowns[i] = -1;
      } else {
        ulti = getUltimate(team1.team[j].ultimate);
        activeTeam1[j].cooldowns[i] = ulti.stats.cooldown - 1;
        ulti = getUltimate(team2.team[j].ultimate);
        activeTeam2[j].cooldowns[i] = ulti.stats.cooldown - 1;
      }
    }
  }
  printf("\n");
  do {
    pos1 = 0;
    pos2 = 0;

    // Creating the active teams for the two teams
    if (bot == 0) {
      turn(&team1, &team2, activeTeam1);
      turn(&team2, &team1, activeTeam2);
    } else if (bot == 3) {
      turn(&team2, &team1, activeTeam2);
      turnBot(&team1, &team2, activeTeam1, bot);
    } else {
      turn(&team1, &team2, activeTeam1);
      turnBot(&team2, &team1, activeTeam2, bot);
    }

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
    printf("\n");
    fusedTeams = actions(fusedTeams, &team1, &team2);

    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        if (activeTeam1[j].alive != 0) {
          if (strcmp(activeTeam1[j].champ.name, fusedTeams[i].champ.name) ==
              0) {
            activeTeam1[j].buffs = fusedTeams[i].buffs;
            activeTeam1[j].debuffs = fusedTeams[i].debuffs;
            updateEffects(&activeTeam1[j].buffs, activeTeam1[j].buffs,
                          &activeTeam1[j], &team1);
            updateEffects(&activeTeam1[j].debuffs, activeTeam1[j].debuffs,
                          &activeTeam1[j], &team1);
            fusedTeams[i].buffs = activeTeam1[j].buffs;
            fusedTeams[i].debuffs = activeTeam1[j].debuffs;
            activeTeam1[j] = fusedTeams[i];
          }
        }
        if (activeTeam2[j].alive != 0) {
          if (strcmp(activeTeam2[j].champ.name, fusedTeams[i].champ.name) ==
              0) {
            activeTeam2[j].buffs = fusedTeams[i].buffs;
            activeTeam2[j].debuffs = fusedTeams[i].debuffs;
            updateEffects(&activeTeam2[j].buffs, activeTeam2[j].buffs,
                          &activeTeam2[j], &team2);
            updateEffects(&activeTeam2[j].debuffs, activeTeam2[j].debuffs,
                          &activeTeam2[j], &team2);
            fusedTeams[i].buffs = activeTeam2[j].buffs;
            fusedTeams[i].debuffs = activeTeam2[j].debuffs;
            activeTeam2[j] = fusedTeams[i];
          }
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      if (team1.team[i].stats.hp == 0) {
        activeTeam1[i].alive = 0;
      }
      if (team2.team[i].stats.hp == 0) {
        activeTeam2[i].alive = 0;
      }
      for (int j = 0; j < 4; j++) {
        if (activeTeam1[i].cooldowns[j] > -1) {
          activeTeam1[i].cooldowns[j] = activeTeam1[i].cooldowns[j] - 1;
        }
        if (activeTeam2[i].cooldowns[j] > -1) {
          activeTeam2[i].cooldowns[j] = activeTeam2[i].cooldowns[j] - 1;
        }
      }
    }

    // Displaying the updated teams
    Interface(team1, team2);

    printf("\nAppuyez sur entrée pour continuer.\n");
    clear_scan();

    // Checking if a team is dead or not
    if (team1.team[0].stats.hp <= 0 && team1.team[1].stats.hp <= 0 &&
        team1.team[2].stats.hp <= 0) {
      if (team2.team[0].stats.hp > 0 || team2.team[1].stats.hp > 0 ||
          team2.team[2].stats.hp > 0) {
        win = 2;
      } else {
        win = 3;
      }
    }
    if (team2.team[0].stats.hp <= 0 && team2.team[1].stats.hp <= 0 &&
        team2.team[2].stats.hp <= 0) {
      if (team1.team[0].stats.hp > 0 || team1.team[1].stats.hp > 0 ||
          team1.team[2].stats.hp > 0) {
        win = 1;
      } else {
        win = 3;
      }
    }
    // Repeat the fight if a team is not dead
  } while (win == 0);
  // Displaying the winner, if both teams are dead, it's a draw
  if (win == 1) {
    printf("--------------------------%s REMPORTE LE "
           "COMBAT--------------------------\n",
           team1.teamName);
  } else if (win == 2) {
    printf("--------------------------%s REMPORTE LE "
           "COMBAT--------------------------\n",
           team2.teamName);
  } else {
    printf("---------------------------------EGALITE---------------------------"
           "------\n");
  }
}