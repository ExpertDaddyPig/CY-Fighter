#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void main() {
    FILE *test;
    char heros[40];
    printf("Choose a fighter\n");
    scanf("%s", heros);
    char file[] = "characters/";
    char end[] = ".txt";
    strcat(strcat(file, heros), end);
    test = fopen(file, "r+");
    if (test == NULL) {
        printf("Ouverture du fichier impossible\n");
        exit(1);
    }
    fseek(test, 6, SEEK_SET);
    char name[40];
    char special1[40];
    char special2[40];
    char special3[40];
    char effect[40];
    int atk, def, hp, hp_max, spd, agi;
    int i = 0;
    char letter = fgetc(test);
    while (letter != ';') {
        name[i] = letter;
        i++;
        letter = fgetc(test);
    }
    name[i] = '\0';
    i = 0;
    fseek(test, 6, SEEK_CUR);
    fscanf(test, "%d", &hp);
    fseek(test, 10, SEEK_CUR);
    fscanf(test, "%d", &hp_max);
    fseek(test, 7, SEEK_CUR);
    fscanf(test, "%d", &atk);
    fseek(test, 7, SEEK_CUR);
    fscanf(test, "%d", &def);
    fseek(test, 7, SEEK_CUR);
    fscanf(test, "%d", &agi);
    fseek(test, 7, SEEK_CUR);
    fscanf(test, "%d", &spd);
    fseek(test, 17, SEEK_CUR);
    letter = fgetc(test);
    i = 0;
    while (letter != ']') {
        if (letter == '1') {
            fseek(test, 2, SEEK_CUR);
            letter = fgetc(test);
            while (letter != ',') {
                special1[i] = letter;
                i++;
                letter = fgetc(test);
            }
            special1[i] = '\0';
            i = 0;
            letter = fgetc(test);
        }
        if (letter == '2') {
            fseek(test, 2, SEEK_CUR);
            letter = fgetc(test);
            while (letter != ',') {
                special2[i] = letter;
                i++;
                letter = fgetc(test);
            }
            special2[i] = '\0';
            i = 0;
            letter = fgetc(test);
        }
        if (letter == '3') {
            fseek(test, 2, SEEK_CUR);
            letter = fgetc(test);
            while (letter != ',') {
                special3[i] = letter;
                i++;
                letter = fgetc(test);
            }
            special3[i] = '\0';
            i = 0;
            letter = fgetc(test);
        }
        letter = fgetc(test);
    }
    fseek(test, 12, SEEK_CUR);
    i = 0;
    letter = fgetc(test);
    while (letter != ';') {
        effect[i] = letter;
        i++;
        letter = fgetc(test);
    }
    effect[i] = '\0';
    printf("Le nom: %s\nHP: %d/%d\nAttack: %d\nDefense: %d\nAgilité: %d\nSpeed: %d\nAttaques spéciales :\n-%s\n-%s\n-%s\nEffet spécial: %s", name, hp, hp_max, atk, def, agi, spd, special1, special2, special3, effect);
}
