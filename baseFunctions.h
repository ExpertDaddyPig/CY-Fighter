#ifndef BASEFUNCTIONS_H
#define BASEFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaring all structures needed for the game
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

typedef struct Effect {
  char name[100];
  int duration;
  moveStats stats;
  struct Effect *next;
} Effect;

typedef struct {
  Fighter champ;
  int champIndex;
  int moveIndex;
  int targets;
  int cooldowns[3];
  int alive;
  Move move;
  Effect *buffs;
  Effect *debuffs;
} ActiveTeam;

// Declaring basic functions
Fighter getFighter(char *name);
void fighterInfos(char *name);
void printChamps();
Team createTeam(char *name);
Team createTeam2(char *name, Team team);
int verifyChamp(char *champName);
int verifyTeam(Fighter champ, Team team);
void deleteEffect(Effect *effects, char *effect);
Effect *addEffect(Effect *effects, Move effect);
Effect *createEffect(Move move);
void toLowerCase(char *str);
void clear_scan();
char *getValue(char *input);
char *getSpec(char *input);

#endif
