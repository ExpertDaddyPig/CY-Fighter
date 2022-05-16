#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "baseFunctions.h"

void main() {
    char teamName[200];
    printf("Entrez le nom de votre équipe: ");
    scanf("%[^\n]%*c", teamName);
    team team1 = createTeam(teamName);
    printf("%s\n",team1.teamName);
    printf("%s\n",team1.team[0].name);
    printf("%s\n",team1.team[1].name);
    printf("%s\n",team1.team[2].name);
}
