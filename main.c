#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "baseFunctions.h"
#include "combatFunctions.h"

void main() {
    char teamName[200];
    printf("Entrez le nom de votre équipe: ");
    scanf("%[^\n]%*c", teamName);
    team team1 = createTeam(teamName);
    Interface(team1);
}
