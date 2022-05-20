#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "combatFunctions.h"

int espace(int a){
	a=75-a;
	return a;
}

void Interface(team equipe){
	int space;
	char *heros1, *heros2, *heros3, *teamName;
	teamName = equipe.teamName;
	heros1 = equipe.team[0].name;
	heros2 = equipe.team[1].name;
	heros3 = equipe.team[2].name;
	printf("┏[%s]",teamName);
	space=strlen(teamName);
	space=75-space;
	for(int i=0; i<space;i++) {
		printf("━");
	}
	printf("┓\n");
	printf("┃    %s  |1|              %s  |2|              %s  |3|",heros1,heros2,heros3);
    space=strlen(heros1)+strlen(heros2)+strlen(heros3);
	space=30-space;
	for(int i=0; i<space;i++){
		printf(" ");
	}
	printf("┃");
}

/*int Tours(){
	int n;
	do{
	printf("Début de la manche %d",n);
	
	n=n+1;
	} while (n<=3);
}*/