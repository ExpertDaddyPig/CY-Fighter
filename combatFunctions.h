#ifndef COMBATFUNCTIONS_H
#define COMBATFUNCTIONS_H

#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Declaring all function needed for the interface and the turns
Move moveChoice(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam *activeTeam, ActiveTeam *fusedTeam);
Move moveChoiceBot(Team *ally, Team *enemy, int *i, int *index,
                ActiveTeam *activeTeam, int bot);
void fight(Team ally, Team enemy, int bot);
void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam1, ActiveTeam *activeTeam2);
void turnBot(Team *ally, Team *enemy, ActiveTeam *activeTeam, int diff);
int checkHealthy(Fighter champ);
int getLow(Fighter *fighters);
void *oneOrMoreKillable(Team enemy[], ActiveTeam fighter, Fighter champ, int killState[]);
int buffMoveAvailable(ActiveTeam fighter, Fighter champ, int statusMove[]);
int debuffMoveAvailable(ActiveTeam fighter, Fighter champ, int statusMove[]);
void sortBySpeed(ActiveTeam *team, int size);
void makeOrder(ActiveTeam *team);
void activeCooldown(ActiveTeam *activeTeam, int champIndex);
void desactiveCooldown(ActiveTeam *activeTeam, int champIndex);

#endif