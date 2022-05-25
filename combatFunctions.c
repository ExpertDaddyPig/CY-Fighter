#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "combatFunctions.h"

int espace(int a) {
  a = 75-a;
  return a;
}

void Interface(team ally, team enemy) {
  int space, namespace, spaceleft;
  char *heros1, *heros2, *heros3, *heros4, *heros5, *heros6, *allyName, *enemyName;
  allyName = ally.teamName;
  enemyName = enemy.teamName;
  heros1 = ally.team[0].name;
  heros2 = ally.team[1].name;
  heros3 = ally.team[2].name;
  heros4 = enemy.team[0].name;
  heros5 = enemy.team[1].name;
  heros6 = enemy.team[2].name;
  printf("┏[%s]", allyName);
  space = strlen(allyName);
  namespace = 0;
  spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros1) + strlen(heros2) + strlen(heros3) + strlen("|1|") * 3);
  for (int i = space; i < 78; i++) {
    printf("━");
  }
  printf("┓\n");
  printf("┃    ");
  printf("%s", heros1);
  for (int i = strlen(heros1); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|1|      ");
  printf("%s", heros2);
  for (int i = strlen(heros2); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|2|      ");
  printf("%s", heros3);
  for (int i = strlen(heros3); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|3|");
  printf("    ┃\n");
  printf("┃    ");
  for (int i = 0; i < 72; i++) {
    printf(" ");
  }
  printf("    ┃\n");
  printf("┃   [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]    [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]    [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]   ┃\n");
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
  printf("┏[%s]", enemyName);
  space = strlen(enemyName);
  namespace = 0;
  spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros4) + strlen(heros5) + strlen(heros6) + strlen("|1|") * 3);
  for (int i = space; i < 78; i++) {
    printf("━");
  }
  printf("┓\n");
  printf("┃    ");
  printf("%s", heros4);
  for (int i = strlen(heros4); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|1|      ");
  printf("%s", heros5);
  for (int i = strlen(heros5); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|2|      ");
  printf("%s", heros6);
  for (int i = strlen(heros6); i < 17; i++) {
    printf(" ");
    namespace = namespace + 1;
  }
  printf("|3|");
  printf("    ┃\n");
  printf("┃    ");
  for (int i = 0; i < 72; i++) {
    printf(" ");
  }
  printf("    ┃\n");
  printf("┃   [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]    [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]    [");
  for (int i = 0; i < 20; i++) {
    printf("\u25A0");
  }
  printf("]   ┃\n");
  printf("┗");
  for (int i = 0; i < 80; i++) {
    printf("━");
  }
  printf("┛\n");
}

/*int Tours(){
	int n;
	do{
	printf("Début de la manche %d",n);
	n=n+1;
	} while (n<=3);
}*/