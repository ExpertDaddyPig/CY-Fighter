#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "combatFunctions.h"

int espace(int a){
	a=75-a;
	return a;
}

void Interface(team equipe){
	int space, namespace, spaceleft;
	char *heros1, *heros2, *heros3, *teamName;
	teamName = equipe.teamName;
	heros1 = equipe.team[0].name;
	heros2 = equipe.team[1].name;
	heros3 = equipe.team[2].name;
	printf("%s\n", heros1);	
	printf("%s\n", heros2);
	printf("%s\n", heros3);
	printf("┏[%s]",teamName);
	space=strlen(teamName);
	namespace = 0;
    spaceleft = 73 - (strlen("┃    ") * 2 + strlen(heros1) + strlen(heros2) + strlen(heros3) + strlen("|1|") * 3);
	for(int i = space; i < 78;i++) {
		printf("━");

	}
	printf("┓\n");
	printf("┃    ");
    printf("%s", heros1);
    for(int i = strlen(heros1); i < 17;i++) {
        printf(" ");
        namespace = namespace + 1;
    }
    printf("|1|");
    for (int i = 0; i < spaceleft / 2; i++) {
        printf(" ");
    }
    printf("%s", heros2);
    for(int i = strlen(heros2); i < 17;i++) {
        printf(" ");
        namespace = namespace + 1;
    }
    printf("|2|");
    for (int i = 0; i < spaceleft / 2; i++) {
        printf(" ");
    }
    printf("%s", heros3);
    for(int i = strlen(heros3); i < 17;i++) {
        printf(" ");
        namespace = namespace + 1;
    }
    printf("|3|");
	printf("    ┃");
}

/*int Tours(){
	int n;
	do{
	printf("Début de la manche %d",n);
	
	n=n+1;
	} while (n<=3);
}*/
