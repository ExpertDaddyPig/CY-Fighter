#ifndef COMBATFUNCTIONS_H
#define COMBATFUNCTIONS_H

#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaring all function needed for the interface and the turns
Move moveChoice(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam *activeTeam);
void fight(Team ally, Team enemy);
void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam);
void sortBySpeed(ActiveTeam *team, int size);
void makeOrder(ActiveTeam *team);
void activeCooldown(ActiveTeam *activeTeam, int champIndex);
void desactiveCooldown(ActiveTeam *activeTeam, int champIndex);

#endif