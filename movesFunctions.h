#ifndef MOVESFUNCTIONS_H
#define MOVESFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"

typedef struct {
	int power;
    int accuracy;
    int duration;
    int cooldown;
    int priority;
    int targets;
} moveStats;

typedef struct {
    char name[100];
    char description[300];
    char type[100];
    moveStats stats;
} Move;

Move getMove(char *name);

#endif
