#ifndef INTERFACEFUNCTIONS_H
#define INTERFACEFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"

void getActiveEffects(ActiveTeam fighter, int *effectStates);
void Interface(ActiveTeam *fusedTeam, Team ally, Team enemy);
void SoloTeamInterface(ActiveTeam activeTeam[], Team team);
void caraInterface(Team ally, int cara, ActiveTeam *activeTeam);
void champInfos(Fighter champ, ActiveTeam fighter);
void movesInfos(Fighter champ);
void buffsInfos(ActiveTeam activeFighter);

#endif