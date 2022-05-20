#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseFunctions.h"

char toLowerCase(char *str) {  
    int i = 0;  
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        } 
        i++; 
    }  
}  

fighter getFighter (char *champName) {
    FILE *data;
    fighter champ;
    char file[] = "characters/";
    char end[] = ".txt";
    strcat(strcat(file, champName), end);
    data = fopen(file, "r+");
    if (data == NULL) {
        printf("%s n'est pas un personnage disponible dans ce roster.\nVeuillez réessayez avec une champion figurant dans la liste.", champName);
        exit(1);
    }
    fseek(data, 6, SEEK_SET);
    char name[40], special1[40], special2[40], special3[40], effect[40], type[40];
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
        if (letter == '3') {
            fseek(data, 2, SEEK_CUR);
            letter = fgetc(data);
            while (letter != ',') {
                special3[i] = letter;
                i++;
                letter = fgetc(data);
            }
            special3[i] = '\0';
            i = 0;
            letter = fgetc(data);
        }
        letter = fgetc(data);
    }
    fseek(data, 12, SEEK_CUR);
    i = 0;
    letter = fgetc(data);
    while (letter != ';') {
        effect[i] = letter;
        i++;
        letter = fgetc(data);
    }
    effect[i] = '\0';
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
        champ.specials[0][i] = special2[i];
    }
    for (i = 0; i <= strlen(special3); i++) {
        champ.specials[0][i] = special3[i];
    }
    strcpy(champ.effect, effect);
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

team createTeam (char *name) {
    team equipe;
    char *teamName = name;
    char heros1[40], heros2[40], heros3[40];
    int verif = 0;
    fighter champ1, champ2, champ3;
    printf("Choissisez votre premier champion: ");
    do {
        scanf("%[^\n]%*c", heros1);
        toLowerCase(heros1);
        verif = verifyChamp(heros1);
        if (verif == 0) {
            printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros1);
            printf("\nChoissisez votre premier champion: ");
        }
    } while (verif == 0);
    printf("Choissisez votre deuxième champion: ");
    do {
        scanf("%[^\n]%*c", heros2);
        toLowerCase(heros2);
        verif = verifyChamp(heros2);
        if (verif == 0) {
            printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.", heros2);
            printf("\nChoissisez votre deuxième champion: ");
        }
        if (strcmp(heros1, heros2) == 0) {
            printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre deuxième champion: ", heros2);
            verif = 0;
        }
    } while (verif == 0);
    printf("Choissisez votre troisième champion: ");
    do {
        scanf("%[^\n]%*c", heros3);
        toLowerCase(heros3);
        verif = verifyChamp(heros3);
        if (verif == 0) {
            printf("\"%s\" n'est pas un personnage disponible dans ce roster.\nVeuillez réessayer avec une champion figurant dans la liste.\n", heros3);
            printf("Choissisez votre troisième champion: ");
        }
        if (strcmp(heros1, heros3) == 0 || strcmp(heros2, heros3) == 0) {
            printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre personnage.\nChoissisez votre troisième champion: ", heros3);
            verif = 0;
        }
    } while (verif == 0);
    champ1 = getFighter(heros1);
    champ2 = getFighter(heros2);
    champ3 = getFighter(heros3);
    strcpy(equipe.teamName, name);
    equipe.team[0] = champ1;
    equipe.team[1] = champ2;
    equipe.team[2] = champ3;
    return equipe;
}
