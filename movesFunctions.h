#ifndef MOVESFUNCTIONS_H
#define MOVESFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"

typedef struct {
    char *name;
    char *description;
    char *type;
    int power;
    int accuracy;
    int duration;
    int cooldown;
    int priority;
    int targets;
} Move;

Move getMove(char *name);

#endif