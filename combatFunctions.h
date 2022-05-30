#ifndef COMBATFUNCTIONS_H
#define COMBATFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movesFunctions.h"

typedef struct {
    Fighter champ;
    Move move;
    int targets;
} ActiveTeam;

int espace(int a);
void Interface(Team ally, Team enemy);
void caraInterface(Team ally, int cara);
void movesInfos(Fighter champ);
void fight(Team ally, Team enemy);
void turn(Team *ally, Team *enemy, ActiveTeam *activeTeam);
void sortBySpeed(ActiveTeam *team, int size);
void makeOrder(ActiveTeam *team);

#endif