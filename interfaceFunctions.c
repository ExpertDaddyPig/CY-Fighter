#include "interfaceFunctions.h"
#include "baseFunctions.h"
#include "effectsFunctions.h"
#include "movesFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define color(param) printf("\033[%sm", param)

void SoloTeamInterface(Team team) {
  int space, namespace, spaceleft;
  float percent, shieldPercent;
  char *heros1, *heros2, *heros3, *teamName;
  teamName = team.teamName;
  heros1 = team.team[0].name;
  heros2 = team.team[1].name;
  heros3 = team.team[2].name;

  // Display the two teams with their names and their fighters + their health
  // bar. If the fighter is dead, it's displayed next to a red K.O.
  printf("┏[%s]", teamName);
  space = strlen(teamName);
  namespace = 0;
  spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros1) + strlen(heros2) +
                    strlen(heros3) + strlen("|1|") * 3);
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
  if (team.team[0].stats.hp == 0) {
    color("41");
    printf("K.O.");
    color("0");
    printf("     ");
  } else {
    printf("|1|      ");
  }
  printf("%s", heros2);
  for (int i = strlen(heros2); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (team.team[1].stats.hp == 0) {
    color("41");
    printf("K.O.");
    color("0");
    printf("     ");

  } else {
    printf("|2|      ");
  }
  printf("%s", heros3);
  for (int i = strlen(heros3); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  if (team.team[2].stats.hp == 0) {
    color("41");
    printf("K.O.");
    color("0");
  } else {
    printf("|3| ");
  }
  printf("   ┃\n");
  printf("┃    ");
  for (int i = 0; i < 72; i++) {
    printf(" ");
  }
  printf("    ┃\n");
  printf("┃   ");
  for (int i = 0; i < 3; i++) {
    if (team.team[i].stats.hp < 10) {
      printf("[ 00%d/%d ] ", team.team[i].stats.hp, team.team[i].stats.hpMax);
    } else if (team.team[i].stats.hp < 100) {
      printf("[ 0%d/%d ] ", team.team[i].stats.hp, team.team[i].stats.hpMax);
    } else {
      printf("[ %d/%d ] ", team.team[i].stats.hp, team.team[i].stats.hpMax);
    }
    if (team.team[i].stats.shield < 10) {
      printf(" [ \u26E8 00%d ]", team.team[i].stats.shield);
    } else if (team.team[i].stats.shield < 100) {
      printf(" [ \u26E8 0%d ]", team.team[i].stats.shield);
    } else {
      printf(" [ \u26E8 %d ]", team.team[i].stats.shield);
    }
    if (i != 2) {
      for (int i = 22; i < 26; i++) {
        printf(" ");
      }
    }
  }
  printf("   ┃\n");
  printf("┃   [");
  for (int i = 0; i < 3; i++) {
    percent =
        ((float)team.team[i].stats.hp / (float)team.team[i].stats.hpMax) * 20.0;
    shieldPercent =
        ((float)team.team[i].stats.shield / (float)team.team[i].stats.hpMax) *
        20.0;
    for (int i = 0; i < 20; i++) {
      color("92");
      if (i < shieldPercent) {
        color("96");
      } else {
        if (percent < 10) {
          color("93");
        }
        if (percent < 5) {
          color("91");
        }
      }
      if (i < shieldPercent || i < percent) {
        printf("\u25A0");
      } else {
        printf(" ");
      }
    }
    color("0");
    if (i != 2) {
      printf("]    [");
    } else {
      printf("]   ┃\n");
    }
  }
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
}

void Interface(Team ally, Team enemy) {
  int space, namespace, spaceleft;
  float percent;
  char *heros1, *heros2, *heros3, *heros4, *heros5, *heros6, *allyName,
      *enemyName;
  SoloTeamInterface(ally);
  SoloTeamInterface(enemy);
}

void champInfos(Fighter champ, ActiveTeam fighter) {
  Fighter baseChamp = getFighter(champ.name);
  int space, bots, broken, byakugan, kyubi, paralyze, pride, stun, star, super,
      susano, ui;
  int atk = baseChamp.stats.atk, def = baseChamp.stats.def,
      spd = baseChamp.stats.spd, agi = baseChamp.stats.agi, bonus_atk = 0,
      bonus_def = 0, bonus_spd = 0, bonus_agi = 0;
  char buffer[100];

  bots = searchEffect(&fighter, "Defense Bots");
  broken = searchEffect(&fighter, "Brisage");
  byakugan = searchEffect(&fighter, "Byakugan");
  kyubi = searchEffect(&fighter, "Mode Chakra de Kyubi");
  paralyze = searchEffect(&fighter, "Paralysie");
  pride = searchEffect(&fighter, "Saiyan Pride");
  stun = searchEffect(&fighter, "Stun");
  super = searchEffect(&fighter, "Super Sonic");
  star = searchEffect(&fighter, "Super Star");
  susano = searchEffect(&fighter, "Susano");
  ui = searchEffect(&fighter, "Ultra Instinct");
  if (bots == 0)
    bonus_def += 50;
  if (star == 0)
    bonus_spd += 30;
  if (broken == 0)
    bonus_def -= 20;
  if (byakugan == 0) {
    bonus_atk += 20;
    bonus_def += 20;
    bonus_agi += 20;
  }
  if (super == 0) {
    bonus_atk += 30;
    bonus_def += 50;
    bonus_spd += 50;
  }
  if (kyubi == 0) {
    bonus_atk += 30;
    bonus_spd += 30;
    bonus_agi += 20;
  }
  if (paralyze == 0)
    bonus_spd -= baseChamp.stats.spd * 0.25;
  if (pride == 0)
    bonus_atk += 40;
  if (stun == 0) {
    bonus_spd -= baseChamp.stats.spd / 2;
    bonus_agi -= baseChamp.stats.agi / 2;
  }
  if (susano == 0) {
    bonus_atk += 30;
    bonus_def += 50;
  }
  if (ui == 0) {
    bonus_spd += 10;
    bonus_agi += 60;
  }
  printf("\n[Stats de %s]\n-------------------\n\tHP Actuels/HP Max: %d / %d [ "
         "Shield: %d ]",
         champ.name, baseChamp.stats.hp, baseChamp.stats.hpMax,
         baseChamp.stats.shield);
  if (bonus_atk != 0) {
    printf("\n\tAttaque: %d", baseChamp.stats.atk);
    if (bonus_atk < 0) {
      color("31");
      printf("\t(%d)", bonus_atk);
    } else {
      color("32");
      printf("\t(+%d)", bonus_atk);
    }
    color("0");
  } else {
    printf("\n\tAttaque: %d", baseChamp.stats.atk);
  }
  if (bonus_def != 0) {
    printf("\n\tDefense: %d", baseChamp.stats.def);
    if (bonus_def < 0) {
      color("31");
      printf("\t(%d)", bonus_def);
    } else {
      color("32");
      printf("\t(+%d)", bonus_def);
    }
    color("0");
  } else {
    printf("\n\tDéfense: %d", baseChamp.stats.def);
  }
  if (bonus_spd != 0) {
    printf("\n\tVitesse: %d", baseChamp.stats.spd);
    if (bonus_spd < 0) {
      color("31");
      printf("\t(%d)", bonus_spd);
    } else {
      color("32");
      printf("\t(+%d)", bonus_spd);
    }
    color("0");
  } else {
    printf("\n\tVitesse: %d", baseChamp.stats.spd);
  }
  if (bonus_agi != 0) {
    printf("\n\tAgilité: %d", baseChamp.stats.agi);
    if (bonus_agi < 0) {
      color("31");
      printf("\t(%d)", bonus_agi);
    } else {
      color("32");
      printf("\t(+%d)", bonus_agi);
    }
    color("0");
  } else {
    printf("\n\tAgilité: %d", baseChamp.stats.agi);
  }
  printf("\n-------------------\n");
}

void movesInfos(Fighter champ) {
  Move move;
  int space;
  char buffer[100];

  // Displaying the fighter's moves, their description and their stats
  printf("\n[Capacités spéciales de %s]\n-------------------\n", champ.name);
  for (int j = 0; j < 3; j++) {
    printf("    ");
    Move move = getMove(champ.specials[j]);
    char *strToken1 = strtok(move.description, "|");
    char *strToken2 = strtok(NULL, "|");
    char *strToken3 = strtok(NULL, "|");
    printf("{%d} %s | Type: %s\n", j + 1, move.name, move.type);
    printf("      Statistiques:                         Description:\n");
    if (move.stats.power > 0) {
      printf("        Puissance: %d", move.stats.power);
      sprintf(buffer, "%d", move.stats.power);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n", strToken1);
      printf("        Précision: %d", move.stats.accuracy);
    } else {
      printf("        Précision: %d", move.stats.accuracy);
      sprintf(buffer, "%d", move.stats.power);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n", strToken1);
    }
    if (strToken2 != NULL) {
      sprintf(buffer, "%d", move.stats.accuracy);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n", strToken2);
    } else {
      printf("\n");
    }
    if (move.stats.targets != -4 && move.stats.targets != -2) {
      printf("        Cibles:    %d", move.stats.targets);
    } else if (move.stats.targets == -4) {
      printf("        Cibles:    Soi-même");
    } else {
      printf("        Cibles:    Aléatoire");
    }
    if (strToken3 != NULL) {
      sprintf(buffer, "%d", move.stats.targets);
      space = strlen(buffer);
      for (int i = space; i < 30; i++) {
        printf(" ");
      }
      printf("%s\n", strToken3);
    } else {
      printf("\n");
    }
    if (move.stats.duration > 0)
      printf("        Durée de l'effet:\t%d tour(s)\n", move.stats.duration);
    printf("        Cooldown:\t\t%d tour(s)\n", move.stats.cooldown);
    printf("\n-------------------\n\n");
  }
  printf("[Capacité Ultime de %s]\n-------------------\n", champ.name);
  Move ulti = getUltimate(champ.ultimate);
  char *strToken1 = strtok(ulti.description, "|");
  char *strToken2 = strtok(NULL, "|");
  char *strToken3 = strtok(NULL, "|");
  printf("[5] %s | Type: %s\n", ulti.name, ulti.type);
  printf("      Statistiques:                         Description:\n");
  if (ulti.stats.power > 0) {
    printf("        Puissance: %d", ulti.stats.power);
    sprintf(buffer, "%d", ulti.stats.power);
    space = strlen(buffer);
    for (int i = space; i < 30; i++) {
      printf(" ");
    }
    printf("%s\n", strToken1);
    printf("        Précision: %d", ulti.stats.accuracy);
  } else {
    printf("        Précision: %d", ulti.stats.accuracy);
    sprintf(buffer, "%d", ulti.stats.power);
    space = strlen(buffer);
    for (int i = space; i < 30; i++) {
      printf(" ");
    }
    printf("%s\n", strToken1);
  }
  if (strToken2 != NULL) {
    sprintf(buffer, "%d", ulti.stats.accuracy);
    space = strlen(buffer);
    for (int i = space; i < 30; i++) {
      printf(" ");
    }
    printf("%s\n", strToken2);
  } else {
    printf("\n");
  }
  if (ulti.stats.targets != -4 && ulti.stats.targets != -2) {
    printf("        Cibles:    %d", ulti.stats.targets);
  } else if (ulti.stats.targets == -4) {
    printf("        Cibles:    Soi-même");
  } else {
    printf("        Cibles:    Aléatoire");
  }
  if (strToken3 != NULL) {
    sprintf(buffer, "%d", ulti.stats.targets);
    space = strlen(buffer);
    for (int i = space; i < 30; i++) {
      printf(" ");
    }
    printf("%s\n", strToken3);
  } else {
    printf("\n");
  }
  if (ulti.stats.duration > 0)
    printf("        Durée de l'effet:\t%d tour(s)\n", ulti.stats.duration);
  printf("        Chargement:\t\t%d tour(s)\n", ulti.stats.cooldown);
  printf("\n------------------------\n\n");
}

void buffsInfos(ActiveTeam activeChamp) {
  Fighter champ = activeChamp.champ;
  Effect *temp = NULL;
  int space;
  char buffer[100];
  // Displaying the fighter's moves, their description and their stats
  printf(
      "\n[ Effets actifs sur %s ]\n---------------------------------------\n",
      activeChamp.champ.name);
  color("32");
  printf("\tBuffs: ");
  color("0");
  temp = activeChamp.buffs;
  if (temp != NULL) {
    while (temp != NULL) {
      if (temp->duration + 1 != -1) {
        printf(
            "\n\t   [ %s ]\n\t     %s\n\t     %d tours restants avant la fin "
            "de l'effet.",
            temp->name, temp->description, temp->duration + 1);
      } else if (temp->duration == -2) {
        printf("\n\t   [ %s ]\n\t     %s\n\t     Fin de l'effet à la prochaine "
               "attaque.",
               temp->name, temp->description);
      } else if (temp->duration == -3) {
        printf("\n\t   [ %s ]\n\t     %s\n\t", temp->name, temp->description);
      } else {
        printf("\n\t   [ %s ]\n\t     %s\n\t     Fin de l'effet au prochain "
               "tour.",
               temp->name, temp->description);
      }
      temp = temp->next;
    }
  } else {
    printf("Aucun Buff actif.\n");
  }
  color("31");
  printf("\n\tDebuffs: ");
  color("0");
  temp = activeChamp.debuffs;
  if (temp != NULL) {
    while (temp != NULL) {
      if (temp->duration == -2) {
        printf("\n\t   [ %s ]\n\t     %s\n\t     Fin de l'effet à la prochaine "
               "attaque.",
               temp->name, temp->description);
      } else if (temp->duration + 1 != -1) {
        if (temp->luck > -1) {
          printf(
              "\n\t   [ %s ]\n\t     %s\n\t     %d tours restants avant la fin "
              "de l'effet. (%d%% de chance de s'en libérer)",
              temp->name, temp->description, temp->duration + 1, temp->luck);
        } else {
          printf(
              "\n\t   [ %s ]\n\t     %s\n\t     %d tours restants avant la fin "
              "de l'effet.",
              temp->name, temp->description, temp->duration + 1);
        }
      } else {
        if (temp->luck > -1) {
          printf("\n\t   [ %s ]\n\t     %s\n\t     Fin de l'effet au prochain "
                 "tour. (%d%% de chance de s'en libérer)",
                 temp->name, temp->description, temp->luck);
        } else {
          printf("\n\t   [ %s ]\n\t     %s\n\t     Fin de l'effet au prochain "
                 "tour.",
                 temp->name, temp->description);
        }
      }
      temp = temp->next;
    }
  } else {
    printf("Aucun debuff actif.\n");
  }
  printf("\n");
}

void caraInterface(Team equipe, int cara, ActiveTeam *activeTeam) {
  Fighter hero;
  Move move, ulti;
  int space, num = 0;
  float percent, truePercent;
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
  for (int j = 0; j < 3; j++) {
    num = j;
    printf("┃      ");
    move = getMove(hero.specials[j]);
    if (activeTeam[cara].cooldowns[j] != -1) {
      printf("{%d} %s | Type: %s | ", j + 1, move.name, move.type);
      if (activeTeam[cara].cooldowns[j] >= 1) {
        color("31");
      } else if (activeTeam[cara].cooldowns[j] < 1) {
        color("33");
      }
      printf("CD: %d tour(s).", activeTeam[cara].cooldowns[j] + 1);
    } else {
      printf("{%d} %s | Type: %s | ", j + 1, move.name, move.type);
      color("32");
      printf("CAPACITÉ PRÊTE");
    }
    color("0");
    space = strlen(move.name) + strlen(move.type) + 34;
    for (int i = space; i < 78; i++) {
      printf(" ");
    }
    printf("┃\n");
  }
  num++;
  printf("┃      ");
  printf("{%d} Attaque Basique | Type: Attack", num + 1);
  space = strlen("{} Attaque Basique | Type: Attack") + 1;
  for (int i = space; i < 74; i++) {
    printf(" ");
  }
  printf("┃\n");
  printf("┣━━━━━━━━━━━━");
  for (int i = 0; i < 68; i++) {
    printf(" ");
  }
  printf("┃\n");
  num++;
  ulti = getUltimate(hero.ultimate);
  printf("┃      ");
  printf("[%d] %s | Type: %s", num + 1, ulti.name, ulti.type);
  space = strlen(" [] | Type: ") + 1 + strlen(ulti.name) + strlen(ulti.type);
  if (activeTeam[cara].cooldowns[3] != -1) {
    printf(" |");
    if (activeTeam[cara].cooldowns[3] >= 1) {
      color("31");
    } else if (activeTeam[cara].cooldowns[3] < 1) {
      color("33");
    }
    printf(" CD: %d tour(s).", activeTeam[cara].cooldowns[3] + 1);
    space = space + strlen(" | CD:  tour(s).") +
            (int)ceil((activeTeam[cara].cooldowns[3] + 1) / 10) + 1;
    color("0");
  } else {
    printf(" |");
    color("32");
    printf(" ULTIME PRÊT");
    color("0");
    space = space + strlen("| ULTIME PRÊT");
  }
  for (int i = space; i < 74; i++) {
    printf(" ");
  }
  printf("┃\n");
  printf("┃      ");
  printf("    Chargement: [");
  color("34");
  percent = 40.0 - floorf((((float)activeTeam[cara].cooldowns[3] + 1) /
                           (float)ulti.stats.cooldown) *
                          40.0);
  for (int i = 0; i < 40; i++) {
    if (i < (int)percent) {
      printf("\u25A0");
    } else {
      printf("\u25A1");
    }
  }
  color("0");
  printf("]   ");
  truePercent = floorf((percent / 40.0) * 100.0);
  if ((int)truePercent < 10) {
    printf("[  %d%%  ] ", (int)truePercent);
  } else if ((int)truePercent < 100) {
    printf("[ %d %% ] ", (int)truePercent);
  } else {
    printf("[ %d%% ] ", (int)truePercent);
  }
  space = 5 + 40 + strlen("    Chargement: ") + strlen("[ 0000 ] ");
  for (int i = space; i < 74; i++) {
    printf(" ");
  }
  printf("┃\n");
  printf("┣━━━━━━━━━━━━");
  for (int i = 0; i < 68; i++) {
    printf(" ");
  }
  printf("┃\n");
  num++;
  printf("┃     ");
  color("33");
  printf("Pour plus d'informations à propos d'une attaque, saisissez \"%d\".",
         num + 1);
  color("0");
  for (int i = strlen("Pour plus d'informations à propos d'une attaque, "
                      "saisissez \"\".") +
               7;
       i < 79; i++) {
    printf(" ");
  }
  printf("   ┃\n");
  num++;
  printf("┃     ");
  color("33");
  printf("Pour plus d'informations sur les effets actifs, saisissez "
         "\"%d\".",
         num + 1);
  color("0");
  for (int i = strlen("Pour plus d'informations sur les effets actifs, "
                      "saisissez \"\".") +
               8;
       i < 79; i++) {
    printf(" ");
  }
  printf("   ┃\n");
  num++;
  printf("┃     ");
  color("33");
  printf("Pour plus d'informations sur les stats du personnage, saisissez "
         "\"%d\".",
         num + 1);
  color("0");
  for (int i = strlen("Pour plus d'informations sur les stats du personnage, "
                      "saisissez \"\" .") +
               7;
       i < 79; i++) {
    printf(" ");
  }
  printf("   ┃\n");
  num++;
  printf("┃     ");
  color("33");
  printf("Pour voir les deux équipes, saisissez \"%d\".", num + 1);
  color("0");
  for (int i = strlen("Pour voir les deux équipes, saisissez \"\" .") + 6;
       i < 79; i++) {
    printf(" ");
  }
  printf("   ┃\n");
  if (cara != 0) {
    printf("┃     ");
    color("33");
    printf("Saisissez \"%d\" pour effectuer un retour arrière.", num - num);
    color("0");
    for (int i = strlen("Saisissez \"\" . pour effectuer un retour arrière") + 6;
        i < 79; i++) {
      printf(" ");
    }
    printf("   ┃\n");
  }
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
}