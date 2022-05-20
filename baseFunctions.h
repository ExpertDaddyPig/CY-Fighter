#ifndef BASEFUNCTIONS_H
#define BASEFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hp;
    int hpMax;
    int atk;
    int def;
    int agi;
    int spd;
} stats;

typedef struct {
    char name[40];
    char type[40];
    char specials[3][40];
    char effect[40];
    stats stats;
} fighter;

typedef struct {
    char teamName[100];
    fighter team[3];
} team;

fighter getFighter(char *name);
team createTeam(char *name);
int verifyChamp(char *champName);
char toLowerCase(char *str);
void clear_scan();


#endif
