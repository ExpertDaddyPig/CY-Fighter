#ifndef EFFECTSFUNCTIONS_H
#define EFFECTSFUNCTIONS_H

#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring all moves functions
Effect *deleteEffect(Effect **effects, char *effect);
Effect *addEffect(Effect *effects, char *effect, int dur);
Effect *returnEffect(Effect *effects, char *effect);
Effect *createEffect(char *effect, int dur);
int searchEffect(ActiveTeam *activeFighter, char *buff);
void updateEffects(Effect **effectList, Effect *effect, ActiveTeam *activeFighter, Team *team);
void applyEffect(ActiveTeam *activeFighter, Team *team, Effect *effect);
void removeEffect(ActiveTeam *activeFighter, Team *team, Effect *effect);

#endif
