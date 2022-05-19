#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"
#include "baseFunctions.c"
#include "main.c"

int Espace(int a){
	a=75-a;
	return(a)
}

void Interface(){
	int space;
	printf("┏[%s]",teamName);
	space=strlen(teamName);
	space=75-space;
	for(int i=0; i<space;i++){
		printf("━");
	}
	printf("┓");
	printf("┃    %s  |1|              %s  |2|              %s  |3|",getFighter(heros1),getFighter(heros2),getFighter(heros3))
	space=strlen(getFighter(heros1))+strlen(getFighter(heros2))+strlen(getFighter(heros3));
	espace=30-espace;
	for(int i=0; i<space;i++){
		printf(" ");
	}
	printf("┃");
}

int Tours(){
	int n;
	do{
	printf("Début de la manche %d",n);
	
	n=n+1;
	}
}

void main(){
	printf("Le joueur 1 à choisi %s, %s et %s !",getFighter(heros1),getFighter(heros2),getFighter(heros3));
	Interface();
	
}

┏[]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃    sasuke  |1|              sakura  |¤|              naruto  |3|            ┃
┃    (***)                                                                    ┃
┃   [#################   ]   [#################   ]   [##############      ]  ┃
┃   [>>>>>>              ]   [>>>                 ]   [>>>>>>>>>>>>>>>>>>  ]  ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
┏[EQUIPE2]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃    kiba                     shino                    )>hinata<(             ┃
┃    (***)                                                                    ┃
┃   [#################   ]   [#################   ]   [##############      ]  ┃
┃   [>>>>>>              ]   [>>>                 ]   [>>>>>>>>>>>>>>>>>>  ]  ┃
┃                                                                             ┃
┃     hinata                                                                  ┃
┃     techniques speciales                                                    ┃
┃         |1| Double Kunaï (durée: 3 tours)                                   ┃
┃              ¤ Permet de frapper 2 fois par tour                            ┃
┃         |-| Ecran de fumée (recharge: 2/durée: 4 tours)                     ┃
┃              ¤ Permet d'augmenter l'esquive de 75%                          ┃
┃         |3| Barrière de glace (durée: 3 tours)                              ┃
┃              ¤ Permet d'augmenter la défense de 50%                         ┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
