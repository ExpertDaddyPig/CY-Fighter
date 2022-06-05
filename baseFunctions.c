#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseFunctions.h"
#include "combatFunctions.h"


void toLowerCase(char *str) {  
    int i = 0;  
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        } 
        i++; 
    }  
} 

void clear_scan() {
	char c;
	int res;
	do {
		res = fscanf(stdin, "%c", &c);
	} while (res == 1 && c != '\n');
}

Fighter getFighter (char *champName) {
    FILE *data;
    Fighter champ;
    char file[100];
    snprintf(file, sizeof(file), "characters/%s.txt", champName);
    data = fopen(file, "r");
    if (data == NULL) {
        printf("%s n'est pas un personnage disponible dans ce roster.\nVeuillez réessayez avec une champion figurant dans la liste.", champName);
        exit(1);
    }
    fseek(data, 6, SEEK_SET);
    char name[40], special1[40], special2[40], type[40];
    int atk, def, hp, hp_max, spd, agi;
    int i = 0;
    char letter = fgetc(data);
    while (letter != ';') {
        name[i] = letter;
        i++;
        letter = fgetc(data);
    }
    name[i] = '\0';
    i = 0;
    fseek(data, 8, SEEK_CUR);
    letter = fgetc(data);
    while (letter != ';') {
        type[i] = letter;
        i++;
        letter = fgetc(data);
    }
    type[i] = '\0';
    i = 0;
    fseek(data, 6, SEEK_CUR);
    fscanf(data, "%d", &hp);
    fseek(data, 10, SEEK_CUR);
    fscanf(data, "%d", &hp_max);
    fseek(data, 7, SEEK_CUR);
    fscanf(data, "%d", &atk);
    fseek(data, 7, SEEK_CUR);
    fscanf(data, "%d", &def);
    fseek(data, 7, SEEK_CUR);
    fscanf(data, "%d", &agi);
    fseek(data, 7, SEEK_CUR);
    fscanf(data, "%d", &spd);
    fseek(data, 17, SEEK_CUR);
    letter = fgetc(data);
    i = 0;
    while (letter != ']') {
        if (letter == '1') {
            fseek(data, 2, SEEK_CUR);
            letter = fgetc(data);
            while (letter != ',') {
                special1[i] = letter;
                i++;
                letter = fgetc(data);
            }
            special1[i] = '\0';
            i = 0;
            letter = fgetc(data);
        }
        if (letter == '2') {
            fseek(data, 2, SEEK_CUR);
            letter = fgetc(data);
            while (letter != ',') {
                special2[i] = letter;
                i++;
                letter = fgetc(data);
            }
            special2[i] = '\0';
            i = 0;
            letter = fgetc(data);
        }
        letter = fgetc(data);
    }
    champ.stats.hp = hp;
    champ.stats.hpMax = hp_max;
    champ.stats.atk = atk;
    champ.stats.def = def;
    champ.stats.agi = agi;
    champ.stats.spd = spd;
    strcpy(champ.name, name);
    strcpy(champ.type, type);
    for (i = 0; i <= strlen(special1); i++) {
        champ.specials[0][i] = special1[i];
    }
    for (i = 0; i <= strlen(special2); i++) {
        champ.specials[1][i] = special2[i];
    }
    fclose(data);
    return champ;
}

int verifyChamp (char *champName) {
    FILE *data;
    char file[100];
    snprintf(file, sizeof(file), "characters/%s.txt", champName);
    data = fopen(file, "r+");
    if (data == NULL) {
        return 0;
    }
    fclose(data);
    return 1;
}

Team createTeam(char *name) {
    Team equipe;
    char *teamName = name;
    char heros1[40], heros2[40], heros3[40];
    int verif = 0, nameVerif = 0;
    Fighter champ1, champ2, champ3;
    printf("Choissisez votre premier champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros1);
        toLowerCase(heros1);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre premier champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros1);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros1);
                printf("\nChoissisez votre premier champion: ");
            }
        }
    } while (verif == 0 || nameVerif == 0);
    champ1 = getFighter(heros1);
    printf("Vous avez choisi: %s\n", champ1.name);
    printf("Choissisez votre deuxième champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros2);
        toLowerCase(heros2);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre deuxième champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros2);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros2);
                printf("\nChoissisez votre premier champion: ");
            }
            if (strcmp(heros1, heros2) == 0) {
                printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre deuxième champion: ", heros2);
                verif = 0;
            }
        }
    } while (verif == 0 || nameVerif == 0);
    champ2 = getFighter(heros2);
    printf("Vous avez choisi: %s\n", champ2.name);
    printf("Choissisez votre troisième champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros3);
        toLowerCase(heros3);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre troisième champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros3);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros3);
                printf("\nChoissisez votre premier champion: ");
            }
            if (strcmp(heros1, heros3) == 0 || strcmp(heros2, heros3) == 0) {
                printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre troisième champion: ", heros3);
                verif = 0;
            }
        }
    } while (verif == 0 || nameVerif == 0);
    champ3 = getFighter(heros3);
    printf("Vous avez choisi: %s\n", champ3.name);
    strcpy(equipe.teamName, name);
    equipe.team[0] = champ1;
    equipe.team[1] = champ2;
    equipe.team[2] = champ3;
    return equipe;
}

Team createTeam2(char *name, Team team) {
    Team equipe;
    char *teamName = name;
    char heros1[40], heros2[40], heros3[40];
    int verif = 0, nameVerif = 0, teamVerif = 0;
    Fighter champ1, champ2, champ3;
    printf("Choissisez votre premier champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros1);
        toLowerCase(heros1);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre premier champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros1);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros1);
                printf("\nChoissisez votre premier champion: ");
            }
            if (verif == 1) {
                teamVerif = verifyTeam(getFighter(heros1), team);
                if (teamVerif == 1) {
                    printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre premier champion: ", heros2);
                }
            }
        }
    } while (verif == 0 || nameVerif == 0 || teamVerif == 1);
    champ1 = getFighter(heros1);
    printf("Vous avez choisi: %s\n", champ1.name);
    printf("Choissisez votre deuxième champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros2);
        toLowerCase(heros2);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre deuxième champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros2);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros2);
                printf("\nChoissisez votre deuxième champion: ");
            }
            if (strcmp(heros1, heros2) == 0) {
                printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre deuxième champion: ", heros2);
                verif = 0;
            }
            if (verif == 1) {
                teamVerif = verifyTeam(getFighter(heros2), team);
                if (teamVerif == 1) {
                    printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre deuxième champion: ", heros2);
                }
            }
        }
    } while (verif == 0 || nameVerif == 0 || teamVerif == 1);
    champ2 = getFighter(heros2);
    printf("Vous avez choisi: %s\n", champ2.name);
    printf("Choissisez votre troisième champion: ");
    do {
        nameVerif = scanf("%[^\n]%*c", heros3);
        toLowerCase(heros3);
        if (nameVerif == 0) {
            printf("Veuillez entrer un nom de champion valide.\n");
            printf("Choissisez votre troisième champion: ");
            clear_scan();
        } else {
            verif = verifyChamp(heros3);
            if (verif == 0) {
                printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros3);
                printf("\nChoissisez votre troisième champion: ");
            }
            if (strcmp(heros1, heros3) == 0 || strcmp(heros2, heros3) == 0) {
                printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre troisième champion: ", heros3);
                verif = 0;
            }
            if (verif == 1) {
                teamVerif = verifyTeam(getFighter(heros3), team);
                if (teamVerif == 1) {
                    printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre troisième champion: ", heros3);
                }
            }
        }
    } while (verif == 0 || nameVerif == 0 || teamVerif == 1);
    champ3 = getFighter(heros3);
    printf("Vous avez choisi: %s\n", champ3.name);
    strcpy(equipe.teamName, name);
    equipe.team[0] = champ1;
    equipe.team[1] = champ2;
    equipe.team[2] = champ3;
    return equipe;
}

int tabTri(ActiveTeam tab[], int size) {
    ActiveTeam temp;
    if (size > 2) {
        for (int i = 0; i < size - 1; i++) {   
		    if (tab[i].champ.stats.spd < tab[i+1].champ.stats.spd) {
			    return 0;
		    }
	    }
	    return 1;
    } else if (size == 2) {
        if (tab[0].champ.stats.spd < tab[1].champ.stats.spd) {
            temp = tab[0];
            tab[0] = tab[1];
            tab[1] = temp;
        }
        return 1;
    } else {
        return 1;
    }
}

void sortBySpeed(ActiveTeam *fighters, int size) {
    int desordre = 1;
    ActiveTeam temp;
    int noEtape = size - 1;
    int noCase;
    while (desordre && noEtape > 0) {
          desordre = 0;
          for (noCase = 0; noCase < noEtape; noCase++) {
               if (fighters[noCase].champ.stats.spd < fighters[noCase + 1].champ.stats.spd) {
                	desordre = 1;
                    temp = fighters[noCase];
                    fighters[noCase] = fighters[noCase + 1];
                    fighters[noCase + 1] = temp;
               }
          }
       noEtape--;
     }
}

void makeOrder(ActiveTeam *fighters) {
    ActiveTeam prio0[6], prio1[6], noprio[6], sorted[6];
    int prio0Size = 0, prio1Size = 0, noprioSize = 0, verif, pos1 = 0, pos0 = 0, nopos = 0;
    for (int i = 0; i < 6; i++) {
        if (fighters[i].move.stats.priority == 0) {
            prio0[pos0] = fighters[i];
            prio0Size = prio0Size + 1;
            pos0 = pos0 + 1;
        } else if (fighters[i].move.stats.priority == 1) {
            prio1[pos1] = fighters[i];
            prio1Size = prio1Size + 1;
            pos1 = pos1 + 1;
        } else {
            noprio[nopos] = fighters[i];
            noprioSize = noprioSize + 1;
            nopos = nopos + 1;
        }
    }
    if (prio0Size > 1) {
        do {
            verif = tabTri(prio0, prio0Size);
            if (verif == 0) {
                sortBySpeed(prio0, prio0Size);
            }
        } while (verif == 0);
    }
    if (prio1Size > 1) {
        do {
            verif = tabTri(prio1, prio1Size);
            if (verif == 0) {
                sortBySpeed(prio1, prio1Size);
            }
        } while (verif == 0);
    }
    if (noprioSize > 1) {
        do {
            verif = tabTri(noprio, noprioSize);
            if (verif == 0) {
                sortBySpeed(noprio, noprioSize);
            }
        } while (verif == 0);
    }
    pos0 = 0;
    pos1 = 0;
    nopos = 0;
    for (int i = 0; i < 6; i++) {
        if (pos1 < prio1Size && prio1Size != 0) {
            sorted[i] = prio1[pos1];
            pos1 = pos1 + 1;
        } else if (pos0 < prio0Size && prio0Size != 0) {
            sorted[i] = prio0[pos0];
            pos0 = pos0 + 1;
        } else if (nopos < noprioSize && noprioSize != 0) {
            sorted[i] = noprio[nopos];
            nopos = nopos + 1;
        }
    }
    for (int i = 0; i < 6; i++) {
        fighters[i] = sorted[i];
    }
}

int verifyTeam(Fighter champ, Team enemy) {
  int verif = 0;
  for (int i = 0; i < 3; i++) {
    if (strcmp(champ.name, enemy.team[i].name) == 0) {
      verif = 1;
    }
  }
  return verif;
}