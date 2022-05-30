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
} fighterStats;

typedef struct {
    char name[100];
    char type[40];
    char specials[3][40];
    char effect[40];
    fighterStats stats;
} Fighter;

typedef struct {
    char teamName[100];
    Fighter team[3];
} Team;

Fighter getFighter(char *name);
Team createTeam(char *name);
int verifyChamp(char *champName);
void toLowerCase(char *str);
void clear_scan();

#endif
