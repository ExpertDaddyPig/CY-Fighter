#ifndef COMBATFUNCTIONS_H
#define COMBATFUNCTIONS_H

#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaring all function needed for the interface and the turns
Move moveChoice(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam *activeTeam);
Move moveChoiceBot(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam *activeTeam, int bot);
void fight(Team ally, Team enemy, int bot);
void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam);
void turnBot(Team *ally, Team *enemy, ActiveTeam *activeTeam, int diff);
void sortBySpeed(ActiveTeam *team, int size);
void makeOrder(ActiveTeam *team);
void activeCooldown(ActiveTeam *activeTeam, int champIndex);
void desactiveCooldown(ActiveTeam *activeTeam, int champIndex);

#endif