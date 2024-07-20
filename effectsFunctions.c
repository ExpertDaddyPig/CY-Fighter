#include "effectsFunctions.h"
#include "baseFunctions.h"
#include "movesFunctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void applyEffect(ActiveTeam *activeFighter, Team *team, Effect *effect) {
  if (strcmp(effect->name, "Brûlure") == 0) {
    printf("%s est brûlé(e) et subit %d points de dégats.\n",
           activeFighter->champ.name, effect->damage);
    team->team[activeFighter->champIndex].stats.hp =
        team->team[activeFighter->champIndex].stats.hp - effect->damage;
    if (team->team[activeFighter->champIndex].stats.hp <= 0) {
      team->team[activeFighter->champIndex].stats.hp = 0;
      activeFighter->alive = 0;
    }
    printf("%s a maintenant %d points de vie.\n", activeFighter->champ.name,
           team->team[activeFighter->champIndex].stats.hp);
  }
}

void removeEffect(ActiveTeam *activeFighter, Team *team, Effect *effect) {
  if (strcmp(effect->name, "Stun") == 0) {
    team->team[activeFighter->champIndex].stats.spd =
        team->team[activeFighter->champIndex].stats.spd * 2;
    team->team[activeFighter->champIndex].stats.agi =
        team->team[activeFighter->champIndex].stats.agi * 2;
  } else if (strcmp(effect->name, "Defense Bots") == 0) {
    team->team[activeFighter->champIndex].stats.def =
        team->team[activeFighter->champIndex].stats.def - 50;
  }
}
