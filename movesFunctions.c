#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "baseFunctions.h"
#include "movesFunctions.h"

Move getMove(char *moveName) {
    FILE *data;
    Move move;
    char file[100];
    snprintf(file, sizeof(file), "specials_attacks/%s.txt", moveName);
    data = fopen(file, "r+");
    if (data == NULL) {
        printf("%s n'est pas une capacité spéciale disponible.\nVeuillez réessayez avec une capacité figurant dans la liste.", moveName);
        exit(1);
    }
    fseek(data, 6, SEEK_SET);
    char name[100], desc[300], type[100];
    int pow, dur, acc, cd, prio, tar;
    int i = 0;
    char letter = fgetc(data);
    while (letter != ';') {
        name[i] = letter;
        i++;
        letter = fgetc(data);
    }
    name[i] = '\0';
    i = 0;
    fseek(data, 15, SEEK_CUR);
    letter = fgetc(data);
    while (letter != ';') {
        desc[i] = letter;
        i++;
        letter = fgetc(data);
    }
    desc[i] = '\0';
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
    if (strcmp(type, "Attack") == 0) {
        fseek(data, 9, SEEK_CUR);
        fscanf(data, "%d", &pow);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.name = name;
        move.description = desc;
        move.type = type;
        move.power = pow;
        move.duration = dur;
        move.accuracy = acc;
        move.cooldown = cd;
        move.priority = prio;
        move.targets = tar;
    }
    if (strcmp(type, "Status") == 0) {
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 8, SEEK_CUR);
        fscanf(data, "%d", &pow);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.name = name;
        move.description = desc;
        move.type = type;
        move.power = pow;
        move.duration = dur;
        move.accuracy = acc;
        move.cooldown = cd;
        move.priority = prio;
        move.targets = tar;
    }
    if (strcmp(type, "Buff") == 0) {
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        pow = 0;
        move.name = name;
        move.description = desc;
        move.type = type;
        move.power = pow;
        move.duration = dur;
        move.accuracy = acc;
        move.cooldown = cd;
        move.priority = prio;
        move.targets = tar;
    }
    if (strcmp(type, "Debuff") == 0) {
        fseek(data, 8, SEEK_CUR);
        fscanf(data, "%d", &pow);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.name = name;
        move.description = desc;
        move.type = type;
        move.power = pow;
        move.duration = dur;
        move.accuracy = acc;
        move.cooldown = cd;
        move.priority = prio;
        move.targets = tar;
    }
    if (strcmp(type, "Shield") == 0) {
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        pow = 0;
        move.name = name;
        move.description = desc;
        move.type = type;
        move.power = pow;
        move.duration = dur;
        move.accuracy = acc;
        move.cooldown = cd;
        move.priority = prio;
        move.targets = tar;
    }
    fclose(data);
    return move;
}