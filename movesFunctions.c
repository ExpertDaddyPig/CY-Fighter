#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "baseFunctions.h"
#include "movesFunctions.h"
#include "attacksFunctions.h"

ActiveTeam useMove(ActiveTeam *fighter, Team *ally, Team *enemy, int moveIndex, int pos1, int pos2) {
    char *name = fighter->champ.name;
    if (strcmp(name, "Expert Daddy Pig") == 0) {
        if (moveIndex == 0) {
            pizza(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            avion(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Son Goku") == 0) {
        if (moveIndex == 0) {
            kamehameha(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            kaioken(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Hinata") == 0) {
        if (moveIndex == 0) {
            ramen(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            paume(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Knuckles") == 0) {
        if (moveIndex == 0) {
            acier(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            seisme(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Luigi") == 0) {
        if (moveIndex == 0) {
            thunder(fighter, ally, enemy, pos1, pos2);
        }
        if (moveIndex == 1) {
            boomerang(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Mario") == 0) {
        if (moveIndex == 0) {
            fire(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            ice(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Naruto") == 0) {
        if (moveIndex == 0) {
            rasengan(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            clone(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Princess Peach") == 0) {
        if (moveIndex == 0) {
            golf(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            peche(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Saitama") == 0) {
        if (moveIndex == 0) {
            boule(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            punch(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Sakura") == 0) {
        if (moveIndex == 0) {
            cherry(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            heal(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Sasuke") == 0) {
        if (moveIndex == 0) {
            katon(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            chidori(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Scooby-Doo") == 0) {
        if (moveIndex == 0) {
            croque(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            repos(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Shaggy (Sammy)") == 0) {
        if (moveIndex == 0) {
            croque(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            kamehameha(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Sonic") == 0) {
        if (moveIndex == 0) {
            spinattack(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            homming(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Tails") == 0) {
        if (moveIndex == 0) {
            hand(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            bots(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
    if (strcmp(name, "Vegeta") == 0) {
        if (moveIndex == 0) {
            flash(fighter, ally, enemy);
        }
        if (moveIndex == 1) {
            garrick(fighter, ally, enemy);
        }
        if (moveIndex == 2) {
            basic(fighter, ally, enemy);
        }
    }
}

Move getMove(char *moveName) {
    FILE *data;
    Move move;
    char file[50];
    sprintf(file, "specials_attacks/%s.txt", moveName);
    fflush(stdout);
    data = fopen(file, "r");
    if (data == NULL) {
        printf("%s n'est pas une capacité spéciale disponible.\nVeuillez réessayez avec une capacité figurant dans la liste.", moveName);
        exit(1);
    }
    fseek(data, 6, SEEK_SET);
    char name[100], desc[200], type[100];
    int pow, dur, acc, chr, tur, cd, prio, tar;
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
    strcpy(move.name, name);
    strcpy(move.description, desc);
    strcpy(move.type, type);
    if (strcmp(move.type, "Attack") == 0) {
        fseek(data, 9, SEEK_CUR);
        fscanf(data, "%d", &pow);
        fseek(data, 10, SEEK_CUR);
        fscanf(data, "%d", &chr);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 8, SEEK_CUR);
        fscanf(data, "%d", &tur);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.stats.power = pow;
        move.stats.duration = dur;
        move.stats.accuracy = acc;
        move.stats.cooldown = cd;
        move.stats.priority = prio;
        move.stats.turns = tur;
        move.stats.targets = tar;
    }
    if (strcmp(move.type, "Status") == 0) {
        fseek(data, 10, SEEK_CUR);
        fscanf(data, "%d", &chr);
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
        fseek(data, 8, SEEK_CUR);
        fscanf(data, "%d", &tur);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.stats.power = pow;
        move.stats.duration = dur;
        move.stats.accuracy = acc;
        move.stats.cooldown = cd;
        move.stats.priority = prio;
        move.stats.turns = tur;
        move.stats.targets = tar;
    }
    if (strcmp(move.type, "Buff") == 0) {
        fseek(data, 10, SEEK_CUR);
        fscanf(data, "%d", &chr);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &dur);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &acc);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &cd);
        fseek(data, 12, SEEK_CUR);
        fscanf(data, "%d", &prio);
        fseek(data, 8, SEEK_CUR);
        fscanf(data, "%d", &tur);
        fseek(data, 11, SEEK_CUR);
        fscanf(data, "%d", &tar);
        move.stats.power = 0;
        move.stats.duration = dur;
        move.stats.accuracy = acc;
        move.stats.cooldown = cd;
        move.stats.priority = prio;
        move.stats.turns = tur;
        move.stats.targets = tar;
    }
    fclose(data);
    return move;
}

void actions(ActiveTeam *fighters, Team *ally, Team *enemy, int turn) {
    int target1, target2, verif, pos1 = 0, pos2 = 0;
    Move nobuff;
    srand(time(NULL));
    for (int i = 0; i < 6; i++) {
        printf("Tour de %s.\n", fighters[i].champ.name);
        if (fighters[i].champ.stats.hp > 0) {
            verif = verifyTeam(fighters[i].champ, *enemy);
            if (verif == 0) {
                if (fighters[i].targets == -1) {
                    if (fighters[i].move.type == "Attack") {
                        printf("%s utilise %s sur l'équipe adverse.\n", fighters[i].champ.name, fighters[i].move.name);
                    } else {
                        printf("%s utilise %s sur son équipe.\n", fighters[i].champ.name, fighters[i].move.name);
                    }
                } else if (fighters[i].targets == -2) {
                    target1 = rand() % 3;
                    pos1 = target1; 
                    do {
                        target2 = rand() % 3;
                    } while (target1 == target2);
                    pos2 = target2;
                    printf("%s utilise %s sur %s et %s.\n", fighters[i].champ.name, fighters[i].move.name, enemy->team[target1].name, enemy->team[target2].name);
                } else {
                    if (fighters[i].champ.name == enemy->team[fighters[i].targets].name) {
                        printf("%s utilise %s.\n", fighters[i].champ.name, fighters[i].move.name);
                    } else {
                        printf("%s utilise %s sur %s.\n", fighters[i].champ.name, fighters[i].move.name, ally->team[fighters[i].targets].name);
                    }                }
            } else {
                if (fighters[i].targets == -1) {
                    if (fighters[i].move.type == "Attack") {
                        printf("%s utilise %s sur l'équipe adverse.\n", fighters[i].champ.name, fighters[i].move.name);
                    } else {
                        printf("%s utilise %s sur son équipe.\n", fighters[i].champ.name, fighters[i].move.name);
                    }
                } else if (fighters[i].targets == -2) {
                    target1 = rand() % 3;
                    pos1 = target1; 
                    do {
                        target2 = rand() % 3;
                    } while (target1 == target2);
                    pos2 = target2;
                    printf("%s utilise %s sur %s et %s.\n", fighters[i].champ.name, fighters[i].move.name, ally->team[target1].name, ally->team[target2].name);
                } else {
                    if (fighters[i].champ.name == ally->team[fighters[i].targets].name) {
                        printf("%s utilise %s.\n", fighters[i].champ.name, fighters[i].move.name);
                    } else {
                        printf("%s utilise %s sur %s.\n", fighters[i].champ.name, fighters[i].move.name, ally->team[fighters[i].targets].name);
                    }
                }
            }
            useMove(&fighters[i], ally, enemy, fighters[i].moveIndex, pos1, pos2);
            printf("\n");
        } else {
            printf("%s est K.O.\n", fighters[i].champ.name);
        }
    }
}