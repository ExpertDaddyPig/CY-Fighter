#include "effectsFunctions.h"
#include "baseFunctions.h"
#include "movesFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Effect getEffect(char *effectName) {
  FILE *data;
  Effect effect;
  char file[100];

  // Open the file of the fighter
  snprintf(file, sizeof(file), "specials_effects/%s.txt", effectName);
  data = fopen(file, "r+");

  // If the file doesn't exist, return NULL, and print an error message
  if (data == NULL) {
    exit(1);
  }
  char *name, *desc, line[500];
  int dmg, lck;

  fgets(line, sizeof(line), data);
  name = getValue(line);

  fgets(line, sizeof(line), data);
  desc = getValue(line);
  fscanf(data, "damage: %d;\nluck: %d;", &dmg, &lck);
  strcpy(effect.name, name);
  strcpy(effect.description, desc);
  effect.damage = dmg;
  effect.luck = lck;
  effect.next = NULL;

  fclose(data);
  return effect;
}

int verifyEffect(char *effectName) {
  FILE *data;
  char file[100];
  snprintf(file, sizeof(file), "specials_effects/%s.txt", effectName);
  data = fopen(file, "r+");

  if (data == NULL) {
    return 0;
  }
  fclose(data);
  return 1;
}

Effect *createEffect(char *name, int dur) {
  Effect *effect = malloc(sizeof(Effect));
  *effect = getEffect(name);
  effect->duration = dur;
  return effect;
}

Effect *deleteEffect(Effect **effects, char *effect) {
  Effect *current = *effects;
  Effect *previous = NULL;

  while (current != NULL && strcmp(current->name, effect) != 0) {
    previous = current;
    current = current->next;
  }

  if (current == NULL) {
    return *effects;
  }

  if (previous == NULL) {
    *effects = current->next;
  } else {
    previous->next = current->next;
  }

  current = NULL;
  free(current);
  return *effects;
}

Effect *addEffect(Effect *effects, char *effect, int dur) {
  Effect *new = createEffect(effect, dur);
  new->next = effects;
  return new;
}

Effect *returnEffect(Effect *effects, char *effect) {
  Effect *temp = effects, *res = NULL;
  while (temp != NULL) {
    if (strcmp(temp->name, effect) == 0) {
      res = temp;
    }
    temp = temp->next;
  }
  if (res == NULL)
    printf("Effect not found\n");
  return res;
}

int searchEffect(ActiveTeam *activeFighter, char *buff) {
  Effect *temp = activeFighter->buffs;
  int res = 1;
  while (temp != NULL) {
    if (strcmp(temp->name, buff) == 0) {
      res = 0;
    }
    temp = temp->next;
  }
  if (res == 0)
    return res;
  temp = activeFighter->debuffs;
  res = 1;
  while (temp != NULL) {
    if (strcmp(temp->name, buff) == 0) {
      res = 0;
    }
    temp = temp->next;
  }
  return res;
}

void updateEffects(Effect **effectList, Effect *effect,
                   ActiveTeam *activeFighter, Team *team) {
  int free = rand() % 100;
  if (effect == NULL)
    return;
  if (free <= effect->luck) {
    printf("%s s'est libéré(e) de l'effet \"%s\" (%d %d)\n",
           activeFighter->champ.name, effect->name, free, effect->luck);
    effect->duration = -1;
  }
  if (effect->duration != -1) {
    if (effect->duration > 0) {
      if (strcmp(effect->name, "Charge") != 0) {
        printf("L'effet \"%s\" est actif sur %s. %d tours restants.\n",
               effect->name, activeFighter->champ.name, effect->duration);
        applyEffect(activeFighter, team, effect);
        printf("\n");
      }
      effect->duration--;
    } else if (effect->duration != -2) {
      if (strcmp(effect->name, "Charge") != 0) {
        printf("L'effet \"%s\" est actif sur %s. Il prendra fin au prochain "
               "tour.\n",
               effect->name, activeFighter->champ.name);
        applyEffect(activeFighter, team, effect);
        printf("\n");
      }
      effect->duration--;
    } else {
      if (strcmp(effect->name, "Charge") != 0)
        printf("L'effet \"%s\" est actif sur %s. Il prendra à la prochaine "
               "attaque.\n\n",
               effect->name, activeFighter->champ.name);
    }
    updateEffects(effectList, effect->next, activeFighter, team);
  } else {
    if (strcmp(effect->name, "Charge") != 0)
      printf("L'effet \"%s\" n'a plus effet sur %s.\n\n", effect->name,
             activeFighter->champ.name);
    removeEffect(activeFighter, team, effect);
    *effectList = deleteEffect(effectList, effect->name);
    updateEffects(effectList, effect->next, activeFighter, team);
  }
}

void applyEffect(ActiveTeam *activeFighter, Team *team, Effect *effect) {
  int star = searchEffect(activeFighter, "Super Star");
  if (strcmp(effect->name, "Régénération") == 0) {
   if (team->team[activeFighter->champIndex].stats.hp != 0) {
    printf("%s est régénère %d points de vie.\n", activeFighter->champ.name,
           -effect->damage);
    team->team[activeFighter->champIndex].stats.hp =
        team->team[activeFighter->champIndex].stats.hp - effect->damage;
    if (team->team[activeFighter->champIndex].stats.hp >
        team->team[activeFighter->champIndex].stats.hpMax) {
      team->team[activeFighter->champIndex].stats.hp =
          team->team[activeFighter->champIndex].stats.hpMax;
    }
    printf("%s a maintenant %d points de vie.\n", activeFighter->champ.name,
           team->team[activeFighter->champIndex].stats.hp);}
  }
  if (strcmp(effect->name, "Brûlure") == 0) {
    printf("%s est brûlé(e) et subit %d points de dégats.\n",
           activeFighter->champ.name, effect->damage);
    team->team[activeFighter->champIndex].stats.hp =
        team->team[activeFighter->champIndex].stats.hp - effect->damage;
    if (team->team[activeFighter->champIndex].stats.hp <= 0) {
      team->team[activeFighter->champIndex].stats.hp = 0;
      activeFighter->alive = 0;
    }
    if (star == 0 && team->team[activeFighter->champIndex].stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.",
             team->team[activeFighter->champIndex].name);
      team->team[activeFighter->champIndex].stats.hp = 1;
      activeFighter->alive = 1;
    }
    printf("%s a maintenant %d points de vie.\n", activeFighter->champ.name,
           team->team[activeFighter->champIndex].stats.hp);
  }
}

void removeEffect(ActiveTeam *activeFighter, Team *team, Effect *effect) {
  FighterStats baseStats;
  Fighter baseFighter = getFighter(team->team[activeFighter->champIndex].name);
  baseStats = baseFighter.stats;
  if (strcmp(effect->name, "Stun") == 0) {
    team->team[activeFighter->champIndex].stats.spd = baseStats.spd;
    team->team[activeFighter->champIndex].stats.agi = baseStats.agi;
  }
  if (strcmp(effect->name, "Defense Bots") == 0 ||
      strcmp(effect->name, "Brisage") == 0) {
    team->team[activeFighter->champIndex].stats.def = baseStats.def;
  }
  if (strcmp(effect->name, "Paralysie") == 0) {
    team->team[activeFighter->champIndex].stats.spd = baseStats.spd;
  }
  if (strcmp(effect->name, "Byakugan") == 0) {
    team->team[activeFighter->champIndex].stats.atk = baseStats.atk;
    team->team[activeFighter->champIndex].stats.def = baseStats.def;
    team->team[activeFighter->champIndex].stats.agi = baseStats.agi;
  }
  if (strcmp(effect->name, "Mode Chakra de Kyubi") == 0) {
    team->team[activeFighter->champIndex].stats.atk = baseStats.atk;
    team->team[activeFighter->champIndex].stats.agi = baseStats.agi;
    team->team[activeFighter->champIndex].stats.spd = baseStats.spd;
  }
  if (strcmp(effect->name, "Saiyan Pride") == 0) {
    team->team[activeFighter->champIndex].stats.atk = baseStats.atk;
  }
  if (strcmp(effect->name, "Super Sonic") == 0) {
    team->team[activeFighter->champIndex].stats.atk = baseStats.atk;
    team->team[activeFighter->champIndex].stats.def = baseStats.def;
    team->team[activeFighter->champIndex].stats.spd = baseStats.spd;
  }
  if (strcmp(effect->name, "Susano") == 0) {
    team->team[activeFighter->champIndex].stats.atk = baseStats.atk;
    team->team[activeFighter->champIndex].stats.def = baseStats.def;
  }
  if (strcmp(effect->name, "Ultra Instinct") == 0) {
    team->team[activeFighter->champIndex].stats.agi = baseStats.agi;
    team->team[activeFighter->champIndex].stats.spd = baseStats.def;
  }
}
