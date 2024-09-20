#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baseFunctions.h"
#include "combatFunctions.h"
#include "effectsFunctions.h"

void toLowerCase(char *str) {
  int i = 0;
  // Convert a string to lower case
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
  // Reset the scanf() buffer
  do {
    res = fscanf(stdin, "%c", &c);
  } while (res == 1 && c != '\n');
}

void removePattern(char *str, const char *pattern) {
  int len = strlen(pattern);
  char *pos;

  while ((pos = strstr(str, pattern)) != NULL) {
    memmove(pos, pos + len, strlen(pos + len) + 1);
  }
}

char *getAliase(char *fullName) {
  FILE *data;
  struct dirent *entry;
  char *aliase, *fileName, *champName, file[100];
  int verif = 0;
  Fighter champ;
  DIR *dp = opendir("./characters");

  if (dp == NULL) {
    perror("Unable to open directory");
    exit(1);
  }

  while ((entry = readdir(dp)) && verif == 0) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      fileName = entry->d_name;
      snprintf(file, sizeof(file), "characters/%s", fileName);
      data = fopen(file, "r+");
      if (data == NULL) {
        printf("Error opening : %s\n", fileName);
        verif = 0;
      } else {
        removePattern(fileName, ".txt");
        champ = getFighter(fileName);
        champName = champ.name;
        if (strcmp(champName, fullName) == 0) {
          aliase = fileName;
          verif = 1;
        } else {
          toLowerCase(champName);
          if (strcmp(champName, fullName) == 0) {
            aliase = fileName;
            verif = 1;
          }
        }
        fclose(data);
      }
    }
  }

  closedir(dp);
  return aliase;
}

char *getFullName(char *aliase) {
  FILE *data;
  struct dirent *entry;
  char *fullName, *fileName, file[100];
  int verif = 0;
  Fighter champ;
  DIR *dp = opendir("./characters");

  if (dp == NULL) {
    perror("Unable to open directory");
    exit(1);
  }

  while ((entry = readdir(dp)) && verif == 0) {
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      fileName = entry->d_name;
      removePattern(fileName, ".txt");
      if (strcmp(fileName, aliase) == 0) {
        champ = getFighter(aliase);
        verif = 1;
        fullName = champ.name;
      }
    }
  }

  closedir(dp);
  return fullName;
}

char *getValue(char *input) {
  char *value = malloc(500 * sizeof(char)), token[500];
  strcpy(token, strtok(input, ":"));
  strcpy(token, strtok(NULL, ":"));
  sscanf(token, " %500[^;];", value);
  return value;
}

char *getSpec(char *input) {
  char *value = malloc(200 * sizeof(char)), token[200];
  strcpy(token, strtok(input, ":"));
  strcpy(token, strtok(NULL, ":"));
  sscanf(token, " %200[^,],", value);
  return value;
}

Fighter getFighter(char *champName) {
  FILE *data;
  Fighter champ;
  char file[100];

  // Open the file of the fighter
  snprintf(file, sizeof(file), "characters/%s.txt", champName);
  data = fopen(file, "r");

  // If the file doesn't exist, return NULL, and print an error message
  if (data == NULL) {
    snprintf(file, sizeof(file), "characters/%s.txt", getAliase(champName));
    data = fopen(file, "r");
    if (data == NULL) {
      printf("%s n'est pas un personnage disponible dans ce roster.\nVeuillez "
             "réessayez avec une champion figurant dans la liste.",
             champName);
      exit(1);
    }
  }
  // Read the file and store the data in the Fighter structure
  char *name, *special1, *special2, *special3, *ultimate, *type, line[100],
      *token;
  int atk, def, hp, hp_max, spd, agi, last;
  int i = 0;
  char letter;

  // Get the name of the fighter
  fgets(line, sizeof(line), data);
  name = getValue(line);

  // Get the type of the fighter
  fgets(line, sizeof(line), data);
  type = getValue(line);

  // Get the stats of the fighter
  fscanf(data,
         "hp: %d;\nhp-max: %d;\natk: %d;\ndef: %d;\nagi: %d;\nspd: "
         "%d;\nspecials: [\n",
         &hp, &hp_max, &atk, &def, &agi, &spd);

  // Get the special moves of the fighter
  fgets(line, sizeof(line), data);
  special1 = getSpec(line);

  fgets(line, sizeof(line), data);
  special2 = getSpec(line);

  fgets(line, sizeof(line), data);
  special3 = getSpec(line);

  fgets(line, sizeof(line), data);
  fgets(line, sizeof(line), data);
  ultimate = getValue(line);

  // Store the data in the Fighter structure
  champ.stats.hp = hp;
  champ.stats.hpMax = hp_max;
  champ.stats.atk = atk;
  champ.stats.def = def;
  champ.stats.agi = agi;
  champ.stats.spd = spd;
  champ.stats.shield = 0;
  strcpy(champ.name, name);
  strcpy(champ.type, type);
  strcpy(champ.specials[0], special1);
  strcpy(champ.specials[1], special2);
  strcpy(champ.specials[2], special3);
  strcpy(champ.ultimate, ultimate);

  // Close the file and return the Fighter structure
  fclose(data);
  return champ;
}

int verifyChamp(char *champName) {
  FILE *data;
  char file[100];
  snprintf(file, sizeof(file), "characters/%s.txt", champName);
  data = fopen(file, "r+");

  // Verify if the fighter exists, if not, return 0, else return 1
  if (data == NULL) {
    snprintf(file, sizeof(file), "characters/%s.txt", getAliase(champName));
    data = fopen(file, "r+");
    if (data == NULL) {
      return 0;
    }
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

  // Getting the name of the first fighter
  printf(
      "Le nom de votre équipe est : %s.\nChoissisez votre premier champion: ",
      name);
  do {
    nameVerif = scanf("%[^\n]%*c", heros1);
    toLowerCase(heros1);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre premier champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros1);
      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros1);
        printf("\nChoissisez votre premier champion: ");
      }
    }
  } while (verif == 0 || nameVerif == 0);

  // Store the first fighter in a variable
  champ1 = getFighter(heros1);
  printf("Vous avez choisi: %s\n", champ1.name);

  // Getting the name of the second fighter
  printf("Choissisez votre deuxième champion: ");
  do {
    nameVerif = scanf("%[^\n]%*c", heros2);
    toLowerCase(heros2);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre deuxième champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros2);
      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros2);
        printf("\nChoissisez votre deuxième champion: ");
      }

      // Verify if the two first fighters are different
      if (strcmp(heros1, heros2) == 0) {
        printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre "
               "personnage.\nChoissisez votre deuxième champion: ",
               heros2);
        verif = 0;
      }
    }
  } while (verif == 0 || nameVerif == 0);

  // Store the second fighter in a variable
  champ2 = getFighter(heros2);
  printf("Vous avez choisi: %s\n", champ2.name);

  // Getting the name of the third fighter
  printf("Choissisez votre troisième champion: ");
  do {
    nameVerif = scanf("%[^\n]%*c", heros3);
    toLowerCase(heros3);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre troisième champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros3);
      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros3);
        printf("\nChoissisez votre troisième champion: ");
      }

      // Verify if all fighters are different
      if (strcmp(heros1, heros3) == 0 || strcmp(heros2, heros3) == 0) {
        printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre "
               "personnage.\nChoissisez votre troisième champion: ",
               heros3);
        verif = 0;
      }
    }
  } while (verif == 0 || nameVerif == 0);

  // Store the third fighter in a variable
  champ3 = getFighter(heros3);
  printf("Vous avez choisi: %s\n", champ3.name);

  // Store the data in the Team structure and return it
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

  // Getting the name of the first fighter
  printf(
      "Le nom de votre équipe est : %s.\nChoissisez votre premier champion: ",
      name);
  do {
    nameVerif = scanf("%[^\n]%*c", heros1);
    toLowerCase(heros1);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre premier champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros1);

      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros1);
        printf("\nChoissisez votre premier champion: ");
      }
      // If the fighter exists, verify if it's already in the first team
      if (verif == 1) {
        teamVerif = verifyTeam(getFighter(heros1), team);
        if (teamVerif == 1) {
          printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre "
                 "personnage.\nChoissisez votre premier champion: ",
                 heros1);
        }
      }
    }
  } while (verif == 0 || nameVerif == 0 || teamVerif == 1);

  // Store the first fighter in a variable
  champ1 = getFighter(heros1);
  printf("Vous avez choisi: %s\n", champ1.name);

  // Getting the name of the second fighter
  printf("Choissisez votre deuxième champion: ");
  do {
    nameVerif = scanf("%[^\n]%*c", heros2);
    toLowerCase(heros2);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre deuxième champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros2);

      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros2);
        printf("\nChoissisez votre deuxième champion: ");
      }

      // Verify if the two first fighters are different
      if (strcmp(heros1, heros2) == 0) {
        printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre "
               "personnage.\nChoissisez votre deuxième champion: ",
               heros2);
        verif = 0;
      }

      // If the fighter exists, verify if it's already in the first team
      if (verif == 1) {
        teamVerif = verifyTeam(getFighter(heros2), team);
        if (teamVerif == 1) {
          printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre "
                 "personnage.\nChoissisez votre deuxième champion: ",
                 heros2);
        }
      }
    }
  } while (verif == 0 || nameVerif == 0 || teamVerif == 1);

  // Store the second fighter in a variable
  champ2 = getFighter(heros2);
  printf("Vous avez choisi: %s\n", champ2.name);

  // Getting the name of the third fighter
  printf("Choissisez votre troisième champion: ");
  do {
    nameVerif = scanf("%[^\n]%*c", heros3);
    toLowerCase(heros3);

    // Verify if the fighter name is valide
    if (nameVerif == 0) {
      printf("Veuillez entrer un nom de champion valide.\n");
      printf("Choissisez votre troisième champion: ");
      clear_scan();
    } else {
      verif = verifyChamp(heros3);

      // Verify if the fighter exists
      if (verif == 0) {
        printf("\"%s\" n'est pas un personnage disponible dans ce "
               "roster.\nVeuillez réessayer avec une champion figurant dans la "
               "liste.",
               heros3);
        printf("\nChoissisez votre troisième champion: ");
      }

      // Verify if the two first fighters are different
      if (strcmp(heros1, heros3) == 0 || strcmp(heros2, heros3) == 0) {
        printf("Vous avez déjà choisi %s.\nVeuillez choisir un autre "
               "personnage.\nChoissisez votre troisième champion: ",
               heros3);
        verif = 0;
      }

      // If the fighter exists, verify if it's already in the first team
      if (verif == 1) {
        teamVerif = verifyTeam(getFighter(heros3), team);
        if (teamVerif == 1) {
          printf("Votre adversaire déjà choisi %s.\nVeuillez choisir un autre "
                 "personnage.\nChoissisez votre troisième champion: ",
                 heros3);
        }
      }
    }
  } while (verif == 0 || nameVerif == 0 || teamVerif == 1);

  // Store the third fighter in a variable
  champ3 = getFighter(heros3);
  printf("Vous avez choisi: %s\n", champ3.name);

  // Create the team with the fighters and the name of the team and return it
  strcpy(equipe.teamName, name);
  equipe.team[0] = champ1;
  equipe.team[1] = champ2;
  equipe.team[2] = champ3;
  return equipe;
}

int tabTri(ActiveTeam tab[], int size) {
  ActiveTeam temp;
  // Verify if the table is sorted by speed stat
  if (size > 2) {
    for (int i = 0; i < size - 1; i++) {
      if (tab[i].champ.stats.spd < tab[i + 1].champ.stats.spd) {
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

  // Sort the table by speed stat
  while (desordre && noEtape > 0) {
    desordre = 0;
    for (noCase = 0; noCase < noEtape; noCase++) {
      if (fighters[noCase].champ.stats.spd <
          fighters[noCase + 1].champ.stats.spd) {
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
  ActiveTeam *prio0 = malloc(6 * sizeof(ActiveTeam)),
             *prio1 = malloc(6 * sizeof(ActiveTeam)),
             *prio2 = malloc(6 * sizeof(ActiveTeam)),
             *noprio = malloc(6 * sizeof(ActiveTeam)),
             *sorted = malloc(6 * sizeof(ActiveTeam));
  int prio0Size = 0, prio1Size = 0, prio2Size = 0, noprioSize = 0, verif,
      pos2 = 0, pos1 = 0, pos0 = 0, nopos = 0;

  // Separate the fighters in three groups of priority, if the fighter move has
  // a priority of 1, he will be in the first group, if the fighter move has a
  // priority of 0, he will be in the second group, and if the fighter move has
  // a priority of -1, he will be in the third group
  for (int i = 0; i < 6; i++) {
    if (fighters[i].move.stats.priority == 0) {
      prio0[pos0] = fighters[i];
      prio0Size = prio0Size + 1;
      pos0 = pos0 + 1;
    } else if (fighters[i].move.stats.priority == 1) {
      prio1[pos1] = fighters[i];
      prio1Size = prio1Size + 1;
      pos1 = pos1 + 1;
    } else if (fighters[i].move.stats.priority == 2) {
      prio2[pos2] = fighters[i];
      prio2Size = prio2Size + 1;
      pos2 = pos2 + 1;
    } else {
      noprio[nopos] = fighters[i];
      noprioSize = noprioSize + 1;
      nopos = nopos + 1;
    }
  }
  // Sort every group created previously by speed stat
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
  if (prio2Size > 1) {
    do {
      verif = tabTri(prio2, prio2Size);
      if (verif == 0) {
        sortBySpeed(prio2, prio2Size);
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
  pos2 = 0;
  nopos = 0;

  // Merge the three groups in order of speed and move priority
  for (int i = 0; i < 6; i++) {
    if (pos2 < prio2Size && prio2Size != 0) {
      sorted[i] = prio2[pos2];
      pos2 = pos2 + 1;
    } else if (pos1 < prio1Size && prio1Size != 0) {
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

  // Copy the sorted table in the original table
  for (int i = 0; i < 6; i++) {
    fighters[i] = sorted[i];
  }
}

int verifyTeam(Fighter champ, Team enemy) {
  int verif = 0;
  // Verify if the fighter is in the team puted in parameter, if it's the case,
  // return 1, else return 0
  for (int i = 0; i < 3; i++) {
    if (strcmp(champ.name, enemy.team[i].name) == 0) {
      verif = 1;
    }
  }
  return verif;
}

void fighterInfos(char *champ) {
  Fighter heros;
  int space;
  char buffer[100];
  heros = getFighter(champ);
  // Display infos about the fighter
  printf("[%s]\n-------------------\n", heros.name);
  printf("Classe: %s\n", heros.type);
  printf("Statistiques:\n");
  printf("\tPV:      %d\n", heros.stats.hpMax);
  printf("\tAttaque: %d\n", heros.stats.atk);
  printf("\tDefense: %d\n", heros.stats.def);
  printf("\tVitesse: %d\n", heros.stats.spd);
  printf("\tAgilité: %d\n", heros.stats.agi);
  printf("Attaques Spéciales:\n");
  for (int i = 0; i < 3; i++) {
    printf("\t%d. %s\n", i + 1, heros.specials[i]);
  }
  printf("Compétence Ultime: \n\t%s\n", heros.ultimate);
  printf("-------------------\n");
}

void printChamps() {
  // Display all the fighters in the database
  printf("CHAMPIONS:                |  ALIASES: \n");
  printf("- Expert Daddy Pig        |  - %s\n", getAliase("Expert Daddy Pig"));
  printf("- Scooby                  |  - %s\n", getAliase("Scooby"));
  printf("- Shaggy                  |  - %s\n", getAliase("Shaggy"));
  printf("- Saitama                 |  - %s\n", getAliase("Saitama"));
  printf("- Son Goku                |  - %s\n", getAliase("Son Goku"));
  printf("- Vegeta                  |  - %s\n", getAliase("Vegeta"));
  printf("- Hinata                  |  - %s\n", getAliase("Hinata"));
  printf("- Naruto                  |  - %s\n", getAliase("Naruto"));
  printf("- Sasuke                  |  - %s\n", getAliase("Sasuke"));
  printf("- Sakura                  |  - %s\n", getAliase("Sakura"));
  printf("- Sonic                   |  - %s\n", getAliase("Sonic"));
  printf("- Tails                   |  - %s\n", getAliase("Tails"));
  printf("- Knuckles                |  - %s\n", getAliase("Knuckles"));
  printf("- Mario                   |  - %s\n", getAliase("Mario"));
  printf("- Luigi                   |  - %s\n", getAliase("Luigi"));
  printf("- Princess Peach          |  - %s\n", getAliase("Princess Peach"));
}