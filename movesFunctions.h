#ifndef MOVESFUNCTIONS_H
#define MOVESFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"

// Declaring all moves functions
void useMove(ActiveTeam *activeTeam, Team *ally, Team *enemy, int moveIndex, int pos1, int pos2);
Move getMove(char *name);
void actions(ActiveTeam *fighters, Team *ally, Team *enemy);


#endif
