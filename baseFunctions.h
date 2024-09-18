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
  int shield;
} FighterStats;

typedef struct {
  char name[100];
  char type[40];
  char specials[3][40];
  char ultimate[50];
  FighterStats stats;
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
  int charge;
  int cooldown;
  int priority;
  int targets;
} MoveStats;

typedef struct {
  char name[100];
  char description[500];
  char type[100];
  MoveStats stats;
} Move;

typedef struct Effect {
  char name[100];
  char description[500];
  int duration;
  int damage;
  int luck;
  struct Effect *next;
} Effect;

typedef struct {
  Fighter champ;
  int champIndex;
  int moveIndex;
  int targets;
  int cooldowns[4];
  int alive;
  Move move;
  Effect *buffs;
  Effect *debuffs;
} ActiveTeam;

typedef struct {
  char name[100];
  char aliase[100];
  struct ChampNames *next;
} ChampNames;

// Declaring basic functions
Fighter getFighter(char *name);
void fighterInfos(char *name);
void printChamps();
Team createTeam(char *name);
Team createTeam2(char *name, Team team);
int verifyChamp(char *champName);
int verifyTeam(Fighter champ, Team team);
void toLowerCase(char *str);
void clear_scan();
void removePattern(char *str, const char *pattern);
char *getAliase(char *fullName);
char *getFullName(char *aliase);
char *getValue(char *input);
char *getSpec(char *input);

#endif