#ifndef COMBATFUNCTIONS_H
#define COMBATFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"

int espace(int a);
void Interface(team ally, team enemy);

#endif
/*int Tours(){
	int n;
	do{
	printf("Début de la manche %d",n);
	
	n=n+1;
	} while (n<=3);
}*/

/*
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
*/