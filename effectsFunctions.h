#ifndef EFFECTSFUNCTIONS_H
#define EFFECTSFUNCTIONS_H

#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring all moves functions
void applyEffect(ActiveTeam *activeFighter, Team *team, Effect *effect);
void removeEffect(ActiveTeam * activeFighter, Team * team, Effect *effect);

#endif
