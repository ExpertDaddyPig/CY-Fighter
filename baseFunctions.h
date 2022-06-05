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
    char specials[2][40];
    fighterStats stats;
} Fighter;

typedef struct {
    char teamName[100];
    Fighter team[3];
} Team;

typedef struct {
	int power;
    int accuracy;
    int duration;
    int turns;
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

typedef struct {
    Fighter champ;
    Move move;
    int moveIndex;
    int targets;
    Move buff;
} ActiveTeam;

Fighter getFighter(char *name);
Team createTeam(char *name);
Team createTeam2(char *name, Team team);
int verifyChamp(char *champName);
int verifyTeam(Fighter champ, Team team);
void toLowerCase(char *str);
void clear_scan();

#endif
