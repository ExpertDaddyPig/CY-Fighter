#include "attacksFunctions.h"
#include "baseFunctions.h"
#include "effectsFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// This is the code of every moves that can be used in the game

void basic(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  Effect *effect;
  Move move = fighter->move;
  int power = fighter->champ.stats.atk;
  int def, verif, miss = 0, check, star = 1, para, kaio = 1, kunai, burn;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  check = searchEffect(fighter, "Kaioken");
  if (check == 0) {
    kaio = 2;
    printf("La puissance de %s a été doublée: elle passe de %d à %d.\n",
           fighter->move.name, fighter->move.stats.power,
           fighter->move.stats.power * kaio);
    fighter->buffs = deleteEffect(&fighter->buffs, "Kaioken");
  }
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    if (strcmp(fighter->champ.name, "Sakura") == 0) {
      for (int i = 0; i < 6; i++) {
        if (strcmp(target.name, fighters[i].champ.name) == 0) {
          kunai = searchEffect(&fighters[i], "Kunaï Explosifs");
          if (kunai == 0) {
            effect = returnEffect(fighters[i].debuffs, "Kunaï Explosifs");
            printf("Les Kunaï Explosifs de Sakura explosent.\n");
            fighters[i].debuffs =
                deleteEffect(&fighters[i].debuffs, "Kunaï Explosifs");
            for (int j = 0; j < 3; j++) {
              if (verif == 1) {
                target = ally->team[j];
              } else {
                target = enemy->team[j];
              }
              def = target.stats.def;
              percent = (rand() % 5 + 20) / 100.0;
              burn = rand() % 100;
              power = effect->damage + fighter->champ.stats.atk / 10;
              int damage = power - def * percent;
              if (damage < 0) {
                damage = power / 10;
              }
              printf(
                  "Les Kunaï Explosifs de Sakura infligent %d points de dégâts "
                  "à %s.\n",
                  damage, target.name);
              if (target.stats.shield <= 0) {
                target.stats.hp -= damage;
                if (target.stats.hp < 0) {
                  target.stats.hp = 0;
                  printf("%s est K.O.\n", target.name);
                }
              } else {
                int new_damage = 0;
                if (target.stats.shield < damage) {
                  new_damage = damage - target.stats.shield;
                  target.stats.shield = 0;
                  target.stats.hp -= new_damage;
                  printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                         target.name, new_damage);
                } else if (target.stats.shield == damage) {
                  target.stats.shield = 0;
                  printf("%s n'a plus de bouclier.\n", target.name);
                } else {
                  target.stats.shield -= damage;
                  printf("Le bouclier de %s perd %d points de vie.\n",
                         target.name, damage);
                }
              }
              check = searchEffect(fighter, "Brûlure");
              if (check != 0) {
                if (burn < 15) {
                  for (int k = 0; k < 6; k++) {
                    if (strcmp(target.name, fighters[k].champ.name) == 0) {
                      printf("%s est brulé(e).\n", fighters[k].champ.name);
                      fighters[k].debuffs =
                          addEffect(fighters[k].debuffs, "burn",
                                    fighter->move.stats.duration);
                    }
                  }
                }
              }
              for (int k = 0; k < 6; k++) {
                if (strcmp(target.name, fighters[k].champ.name) == 0) {
                  star = searchEffect(&fighters[k], "Super Star");
                }
              }
              if (star == 0 && target.stats.hp == 0) {
                printf("La Super Star de %s l'empèche d'être K.O.\n",
                       target.name);
                target.stats.hp = 1;
              }
              if (verif == 1) {
                ally->team[j] = target;
                if (target.stats.shield > 0) {
                  printf("%s a maintenant %d points de vie et %d points de vie "
                         "sur son "
                         "bouclier.\n",
                         ally->team[j].name, ally->team[j].stats.hp,
                         ally->team[j].stats.shield);
                } else {
                  printf("%s a maintenant %d points de vie.\n",
                         ally->team[j].name, ally->team[j].stats.hp);
                }
              } else {
                enemy->team[j] = target;
                if (target.stats.shield > 0) {
                  printf("%s a maintenant %d points de vie et %d points de vie "
                         "sur son "
                         "bouclier.\n",
                         enemy->team[j].name, enemy->team[j].stats.hp,
                         enemy->team[j].stats.shield);
                } else {
                  printf("%s a maintenant %d points de vie.\n",
                         enemy->team[j].name, enemy->team[j].stats.hp);
                }
              }
            }
          }
        }
      }
    }
    if (kunai != 0) {
      for (int i = 0; i < 6; i++) {
        if (strcmp(target.name, fighters[i].champ.name) == 0) {
          star = searchEffect(&fighters[i], "Super Star");
        }
      }
      if (star == 0 && target.stats.hp == 0) {
        printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
        target.stats.hp = 1;
      }
      if (verif == 1) {
        ally->team[fighter->targets] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 ally->team[fighter->targets].name,
                 ally->team[fighter->targets].stats.hp,
                 ally->team[fighter->targets].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n",
                 ally->team[fighter->targets].name,
                 ally->team[fighter->targets].stats.hp);
        }
      } else {
        enemy->team[fighter->targets] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 enemy->team[fighter->targets].name,
                 enemy->team[fighter->targets].stats.hp,
                 enemy->team[fighter->targets].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n",
                 enemy->team[fighter->targets].name,
                 enemy->team[fighter->targets].stats.hp);
        }
      }
    }
  }
}

void pizza(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->champIndex];
  } else {
    target = enemy->team[fighter->champIndex];
  }
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void avion(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = 999999999;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void marteau(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, broken, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  broken = rand() % 100;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    check = searchEffect(fighter, "Brisage");
    if (check != 0) {
      if (broken < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est brisé(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "broken",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void kamehameha(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                Team *enemy) {
  Fighter target;
  int def, verif, miss, check, star = 1, para, kaio = 1;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  check = searchEffect(fighter, "Kaioken");
  if (check == 0) {
    kaio = 2;
    printf("La puissance de %s a été doublée: elle passe de %d à %d.\n",
           fighter->move.name, fighter->move.stats.power,
           fighter->move.stats.power * kaio);
    fighter->buffs = deleteEffect(&fighter->buffs, "Kaioken");
  }
  int power = fighter->move.stats.power * kaio + fighter->champ.stats.atk / 10;
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy) * 5;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss > target.stats.agi) {
    printf("%s a manqué %s.\n\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void kaioken(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  int verif, check, para;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  check = searchEffect(fighter, "Kaioken");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "kaioken", fighter->move.stats.duration);
  }
  printf("La puissance de sa prochaine attaque sera doublée.\n");
}

void instant(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, kaio = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  check = searchEffect(fighter, "Kaioken");
  if (check == 0) {
    kaio = 2;
    printf("La puissance de %s a été doublée: elle passe de %d à %d.\n",
           fighter->move.name, fighter->move.stats.power,
           fighter->move.stats.power * kaio);
    fighter->buffs = deleteEffect(&fighter->buffs, "Kaioken");
  }
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void chakra(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, missing, verif, check, star = 1, para,
      shield;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  missing = target.stats.hpMax - target.stats.hp;
  heal = heal + missing * 0.3;
  check = searchEffect(fighter, "Byakugan");
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (check == 0) {
      if (target.stats.shield != target.stats.hpMax)
        target.stats.shield += shield;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (check == 0) {
        printf("%s reçoit un bouclier équivalent à %d points de vie.\n",
               ally->team[fighter->targets].name, shield);
      }
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (check == 0) {
        printf("%s reçoit un bouclier équivalent à %d points de vie.\n",
               enemy->team[fighter->targets].name, shield);
      }
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void paume(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Byakugan");
    if (check == 0) {
      printf("Le Byakugan d'Hinata double les dégats de son attaque.");
      damage = damage * 2;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void poings(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int shield, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    shield = target.stats.hpMax * 0.3;
    if (target.stats.hp > 0 && target.stats.shield != target.stats.hpMax) {
      if (target.stats.shield < target.stats.hpMax) {
        target.stats.shield += shield;
        if (target.stats.shield > target.stats.hpMax) {
          target.stats.shield = target.stats.hpMax;
        }
        printf("%s reçoit un bouclier équivalent à %d points de vie.\n",
               target.name, shield);
      }
      if (verif == 1) {
        ally->team[i] = target;
      } else {
        enemy->team[i] = target;
      }
    } else if (target.stats.shield == target.stats.hpMax) {
      printf("%s ne peut pas gagner un bouclier car son bouclier actif est "
             "équivalent aux points de vie "
             "maximum.\n",
             target.name);
    } else {
      printf("\n%s est K.O. et ne peut pas gagner des boucliers.\n",
             target.name);
    }
  }
}

void hook(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, stun;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  stun = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Stun");
    if (check != 0) {
      if (stun < 30) {
        target.stats.spd = target.stats.spd / 2;
        target.stats.agi = target.stats.agi / 2;
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est étourdi(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "stun",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void heat(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int i = 0; i < 3; i++) {
    miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    def = target.stats.def;
    if (miss < target.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target.name);
    } else {
      percent = (rand() % 5 + 20) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      if (target.stats.shield <= 0) {
        printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
               damage, target.name);
        target.stats.hp -= damage;
        if (target.stats.hp < 0) {
          target.stats.hp = 0;
          printf("%s est K.O.\n", target.name);
        }
      } else {
        int new_damage = 0;
        if (target.stats.shield < damage) {
          new_damage = damage - target.stats.shield;
          target.stats.shield = 0;
          target.stats.hp -= new_damage;
          printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                 target.name, new_damage);
        } else if (target.stats.shield == damage) {
          target.stats.shield = 0;
          printf("%s n'a plus de bouclier.\n", target.name);
        } else {
          target.stats.shield -= damage;
          printf("Le bouclier de %s perd %d points de vie.\n", target.name,
                 damage);
        }
      }
      for (int j = 0; j < 6; j++) {
        if (strcmp(target.name, fighters[j].champ.name) == 0) {
          star = searchEffect(&fighters[j], "Super Star");
        }
      }
      if (star == 0 && target.stats.hp == 0) {
        printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
        target.stats.hp = 1;
      }
      if (verif == 1) {
        ally->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 ally->team[i].name, ally->team[i].stats.hp,
                 ally->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
                 ally->team[i].stats.hp);
        }
      } else {
        enemy->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 enemy->team[i].name, enemy->team[i].stats.hp,
                 enemy->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
                 enemy->team[i].stats.hp);
        }
      }
    }
  }
}

void thunder(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy,
             int pos1, int pos2) {
  Fighter target1, target2;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target1 = ally->team[pos1];
    target2 = ally->team[pos2];
  } else {
    target1 = enemy->team[pos1];
    target2 = enemy->team[pos2];
  }
  def = target1.stats.def;
  if (miss < target1.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target1.name);
  } else if (miss > target1.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Paralysie");
    if (check != 0) {
      if (para < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target1.name, fighters[i].champ.name) == 0) {
            printf("%s est paralysé(e).\n", target1.name);
            target1.stats.spd = target1.stats.spd - target1.stats.spd * 0.25;
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target1.name);
    if (target1.stats.shield <= 0) {
      target1.stats.hp -= damage;
      if (target1.stats.hp < 0) {
        target1.stats.hp = 0;
        printf("%s est K.O.\n", target1.name);
      }
    } else {
      int new_damage = 0;
      if (target1.stats.shield < damage) {
        new_damage = damage - target1.stats.shield;
        target1.stats.shield = 0;
        target1.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target1.name, new_damage);
      } else if (target1.stats.shield == damage) {
        target1.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target1.name);
      } else {
        target1.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target1.name,
               damage);
      }
    }
    if (verif == 1) {
      ally->team[pos1] = target1;
      if (target1.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[pos1].name, ally->team[pos1].stats.hp,
               ally->team[pos1].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", ally->team[pos1].name,
               ally->team[pos1].stats.hp);
      }
    } else {
      enemy->team[pos1] = target1;
      if (target1.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[pos1].name, enemy->team[pos1].stats.hp,
               enemy->team[pos1].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", enemy->team[pos1].name,
               enemy->team[pos1].stats.hp);
      }
    }
  }
  def = target2.stats.def;
  if (miss < target2.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target2.name);
  } else if (miss > target2.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Paralysie");
    if (check != 0) {
      if (para < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target2.name, fighters[i].champ.name) == 0) {
            printf("%s est paralysé(e).\n", target2.name);
            target2.stats.spd = target2.stats.spd - target2.stats.spd * 0.25;
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target2.name);
    if (target2.stats.shield <= 0) {
      target2.stats.hp -= damage;
      if (target2.stats.hp < 0) {
        target2.stats.hp = 0;
        printf("%s est K.O.\n", target2.name);
      }
    } else {
      int new_damage = 0;
      if (target2.stats.shield < damage) {
        new_damage = damage - target2.stats.shield;
        target2.stats.shield = 0;
        target2.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target2.name, new_damage);
      } else if (target2.stats.shield == damage) {
        target2.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target2.name);
      } else {
        target2.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target2.name,
               damage);
      }
    }
    if (verif == 1) {
      ally->team[pos2] = target2;
      if (target2.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[pos2].name, ally->team[pos2].stats.hp,
               ally->team[pos2].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", ally->team[pos2].name,
               ally->team[pos2].stats.hp);
      }
    } else {
      enemy->team[pos2] = target2;
      if (target2.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[pos2].name, enemy->team[pos2].stats.hp,
               enemy->team[pos2].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", enemy->team[pos2].name,
               enemy->team[pos2].stats.hp);
      }
    }
  }
}

void boomerang(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
               Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    if (target.stats.shield <= 0) {
      printf("Le boomerang revient, %s inflige %d points de dégâts à %s.\n",
             fighter->champ.name, damage, target.name);
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("Le boomerang revient, %s n'a plus de bouclier et perd %d "
               "points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("Le boomerang revient, %s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf(
            "Le boomerang revient, Le bouclier de %s perd %d points de vie.\n",
            target.name, damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void green(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy,
           int pos1) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[pos1];
  } else {
    target = enemy->team[pos1];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else if (miss > target.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    if (verif == 1) {
      ally->team[pos1] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[pos1].name, ally->team[pos1].stats.hp,
               ally->team[pos1].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", ally->team[pos1].name,
               ally->team[pos1].stats.hp);
      }
    } else {
      enemy->team[pos1] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[pos1].name, enemy->team[pos1].stats.hp,
               enemy->team[pos1].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n", enemy->team[pos1].name,
               enemy->team[pos1].stats.hp);
      }
    }
  }
}

void fire(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, burn;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  burn = 0;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    percent = (rand() % 5 + 20) / 100.0;
    damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * 1.25;
    check = searchEffect(fighter, "Brûlure");
    if (check != 0) {
      if (burn < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est brûlé(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "burn",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s renvoie une boule de feu et inflige %d points de dégâts à %s.\n",
           fighter->champ.name, damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void ice(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, freeze, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  freeze = rand() % 100;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    check = searchEffect(fighter, "Gel");
    if (check != 0) {
      if (freeze < 40) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est gelé(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "freeze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void red(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else if (miss > target.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void rasengan(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
              Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void clone(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, clones, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  clones = rand() % 5 + 1;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * clones;
    printf("%s a fait apparaitre %d clones qui frapperont tous une fois.",
           fighter->champ.name, clones);
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void rasenshuriken(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                   Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10, bonus;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int i = 0; i < 3; i++) {
    miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    def = target.stats.def;
    if (miss < target.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target.name);
    } else {
      percent = (rand() % 5 + 20) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      bonus = damage * 0.25;
      if (i == fighter->targets) {
        damage += bonus;
      }
      printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
             damage, target.name);
      if (target.stats.shield <= 0) {
        target.stats.hp -= damage;
        if (target.stats.hp < 0) {
          target.stats.hp = 0;
          printf("%s est K.O.\n", target.name);
        }
      } else {
        int new_damage = 0;
        if (target.stats.shield < damage) {
          new_damage = damage - target.stats.shield;
          target.stats.shield = 0;
          target.stats.hp -= new_damage;
          printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                 target.name, new_damage);
        } else if (target.stats.shield == damage) {
          target.stats.shield = 0;
          printf("%s n'a plus de bouclier.\n", target.name);
        } else {
          target.stats.shield -= damage;
          printf("Le bouclier de %s perd %d points de vie.\n", target.name,
                 damage);
        }
      }
      for (int j = 0; j < 6; j++) {
        if (strcmp(target.name, fighters[j].champ.name) == 0) {
          star = searchEffect(&fighters[j], "Super Star");
        }
      }
      if (star == 0 && target.stats.hp == 0) {
        printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
        target.stats.hp = 1;
      }
      if (verif == 1) {
        ally->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 ally->team[i].name, ally->team[i].stats.hp,
                 ally->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
                 ally->team[i].stats.hp);
        }
      } else {
        enemy->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 enemy->team[i].name, enemy->team[i].stats.hp,
                 enemy->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
                 enemy->team[i].stats.hp);
        }
      }
    }
  }
}

void golf(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, stun, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  stun = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Stun");
    if (check != 0) {
      if (stun < 20) {
        target.stats.spd = target.stats.spd / 2;
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est étourdi(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "stun",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void vegetable(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
               Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    if (target.stats.hp > 0 && target.stats.hp != target.stats.hpMax) {
      if (target.stats.hp < target.stats.hpMax) {
        target.stats.hp += heal;
        if (target.stats.hp > target.stats.hpMax) {
          target.stats.hp = target.stats.hpMax;
        }
        printf("La capacité %s redonne %d points de vie à %s.\n",
               fighter->move.name, heal, target.name);
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 target.name, target.stats.hp, target.stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", target.name,
                 target.stats.hp);
        }
      }
      if (verif == 1) {
        ally->team[i] = target;
      } else {
        enemy->team[i] = target;
      }
    } else if (target.stats.hp == target.stats.hpMax) {
      printf("%s ne peut pas regagner des points de vie car ses points de vies "
             "sont au maximum.\n",
             target.name);
    } else {
      printf("\n%s est K.O. et ne peut pas regagner des points de vie.\n",
             target.name);
    }
  }
}

void toad(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int shield, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  shield = 100;
  if (target.stats.hp > 0 && target.stats.shield != target.stats.hpMax) {
    if (target.stats.shield < target.stats.hpMax) {
      target.stats.shield += shield;
      if (target.stats.shield > target.stats.hpMax) {
        target.stats.shield = target.stats.hpMax;
      }
      printf("%s reçoit un bouclier équivalent à %d points de vie.\n",
             target.name, shield);
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
    } else {
      enemy->team[fighter->targets] = target;
    }
  } else if (target.stats.shield == target.stats.hpMax) {
    printf("%s ne peut pas gagner un bouclier car son bouclier actif est "
           "équivalent aux points de vie "
           "maximum.\n",
           target.name);
  } else {
    printf("\n%s est K.O. et ne peut pas gagner des boucliers.\n", target.name);
  }
}

void sneeze(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, bonus = 0, stun;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  check = searchEffect(fighter, "Serious Mode");
  if (check == 0) {
    bonus = 25;
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  stun = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Stun");
    if (check != 0) {
      if (stun < 50 + bonus) {
        target.stats.spd = target.stats.spd / 2;
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est étourdi(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "stun",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void punch(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, bonus = 0, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  check = searchEffect(fighter, "Serious Mode");
  if (check == 0) {
    bonus = 25;
  };
  float percent;
  miss = rand() % 125 + (100 - fighter->move.stats.accuracy + bonus);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void headbutt(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
              Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, stun;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  stun = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Stun");
    if (check != 0) {
      if (stun < 20) {
        target.stats.spd = target.stats.spd / 2;
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est étourdi(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "stun",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void cherry(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  Effect *effect;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, burn, kunai;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        kunai = searchEffect(&fighters[i], "Kunaï Explosifs");
        if (kunai == 0) {
          effect = returnEffect(fighters[i].debuffs, "Kunaï Explosifs");
          printf("Les Kunaï Explosifs de Sakura explosent.\n");
          for (int j = 0; j < 3; j++) {
            if (verif == 1) {
              target = ally->team[j];
            } else {
              target = enemy->team[j];
            }
            for (int k = 0; k < 6; k++) {
              if (strcmp(fighters[k].champ.name, target.name) == 0) {
                fighters[k].debuffs =
                    deleteEffect(&fighters[i].debuffs, "Kunaï Explosifs");
              }
            }
            def = target.stats.def;
            percent = (rand() % 5 + 20) / 100.0;
            burn = rand() % 100;
            power = effect->damage + fighter->champ.stats.atk / 10;
            int damage = power - def * percent;
            if (damage < 0) {
              damage = power / 10;
            }
            printf(
                "Les Kunaï Explosifs de Sakura infligent %d points de dégâts "
                "à %s.\n",
                damage, target.name);
            if (target.stats.shield <= 0) {
              target.stats.hp -= damage;
              if (target.stats.hp < 0) {
                target.stats.hp = 0;
                printf("%s est K.O.\n", target.name);
              }
            } else {
              int new_damage = 0;
              if (target.stats.shield < damage) {
                new_damage = damage - target.stats.shield;
                target.stats.shield = 0;
                target.stats.hp -= new_damage;
                printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                       target.name, new_damage);
              } else if (target.stats.shield == damage) {
                target.stats.shield = 0;
                printf("%s n'a plus de bouclier.\n", target.name);
              } else {
                target.stats.shield -= damage;
                printf("Le bouclier de %s perd %d points de vie.\n",
                       target.name, damage);
              }
            }
            check = searchEffect(fighter, "Brûlure");
            if (check != 0) {
              if (burn < 15) {
                for (int k = 0; k < 6; k++) {
                  if (strcmp(target.name, fighters[k].champ.name) == 0) {
                    printf("%s est brulé(e).\n", fighters[k].champ.name);
                    fighters[k].debuffs =
                        addEffect(fighters[k].debuffs, "burn",
                                  fighter->move.stats.duration);
                  }
                }
              }
            }
            for (int k = 0; k < 6; k++) {
              if (strcmp(target.name, fighters[k].champ.name) == 0) {
                star = searchEffect(&fighters[k], "Super Star");
              }
            }
            if (star == 0 && target.stats.hp == 0) {
              printf("La Super Star de %s l'empèche d'être K.O.\n",
                     target.name);
              target.stats.hp = 1;
            }
            if (verif == 1) {
              ally->team[j] = target;
              if (target.stats.shield > 0) {
                printf("%s a maintenant %d points de vie et %d points de vie "
                       "sur son "
                       "bouclier.\n",
                       ally->team[j].name, ally->team[j].stats.hp,
                       ally->team[j].stats.shield);
              } else {
                printf("%s a maintenant %d points de vie.\n",
                       ally->team[j].name, ally->team[j].stats.hp);
              }
            } else {
              enemy->team[j] = target;
              if (target.stats.shield > 0) {
                printf("%s a maintenant %d points de vie et %d points de vie "
                       "sur son "
                       "bouclier.\n",
                       enemy->team[j].name, enemy->team[j].stats.hp,
                       enemy->team[j].stats.shield);
              } else {
                printf("%s a maintenant %d points de vie.\n",
                       enemy->team[j].name, enemy->team[j].stats.hp);
              }
            }
          }
        }
      }
    }
    if (kunai != 0) {
      for (int i = 0; i < 6; i++) {
        if (strcmp(target.name, fighters[i].champ.name) == 0) {
          star = searchEffect(&fighters[i], "Super Star");
        }
      }
      if (star == 0 && target.stats.hp == 0) {
        printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
        target.stats.hp = 1;
      }
      if (verif == 1) {
        ally->team[fighter->targets] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 ally->team[fighter->targets].name,
                 ally->team[fighter->targets].stats.hp,
                 ally->team[fighter->targets].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n",
                 ally->team[fighter->targets].name,
                 ally->team[fighter->targets].stats.hp);
        }
      } else {
        enemy->team[fighter->targets] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 enemy->team[fighter->targets].name,
                 enemy->team[fighter->targets].stats.hp,
                 enemy->team[fighter->targets].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n",
                 enemy->team[fighter->targets].name,
                 enemy->team[fighter->targets].stats.hp);
        }
      }
    }
  }
}

void heal(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void rebirth(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        printf("L'effet \"Régénération\" est actif sur %s pendant %d tours.\n",
               fighters[i].champ.name, fighter->move.stats.duration);
        fighters[i].buffs = addEffect(fighters[i].buffs, "regeneration",
                                      fighter->move.stats.duration);
      }
    }
  }
}

void katon(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, burn;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  burn = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Brûlure");
    if (check != 0) {
      if (burn < 40) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est brûlé(e).\n", fighters[i].champ.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "burn",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void chidori(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  para = rand() % 100;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Paralysie");
    if (check != 0) {
      if (para < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target.name, fighters[i].champ.name) == 0) {
            printf("%s est paralysé(e).\n", target.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void amaterasu(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
               Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, burn;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  burn = 0;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    check = searchEffect(fighter, "Brûlure");
    if (check != 0) {
      for (int i = 0; i < 6; i++) {
        if (strcmp(target.name, fighters[i].champ.name) == 0) {
          printf("%s est brûlé(e).\n", fighters[i].champ.name);
          fighters[i].debuffs = addEffect(fighters[i].debuffs, "burn",
                                          fighter->move.stats.duration);
        }
      }
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void croque(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->champIndex];
  } else {
    target = enemy->team[fighter->champIndex];
  }
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void repos(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->champIndex];
  } else {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Sommeil");
  if (check != 0) {
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        printf("%s est endormi(e).\n", target.name);
        fighters[i].debuffs = addEffect(fighters[i].debuffs, "sleep",
                                        fighter->move.stats.duration);
      }
    }
  }
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void charge(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void flick(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, ui = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  check = searchEffect(fighter, "Ultra Instinct 0.00001%%");
  if (check == 0) {
    ui = 5;
    printf("La puissance de %s a été quintuplée: elle passe de %d à %d.\n",
           fighter->move.name, fighter->move.stats.power,
           fighter->move.stats.power * ui);
  }
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void spinattack(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void homming(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void lightspeed(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, i = 0, alive[3] = {0, 0, 0};
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int k = 0; k < 3; k++) {
    if (verif == 1) {
      for (int j = 0; j < 6; j++) {
        if (strcmp(ally->team[k].name, fighters[j].champ.name) == 0) {
          if (fighters[j].alive == 1)
            alive[k] = 1;
        }
      }
    } else {
      for (int j = 0; j < 6; j++) {
        if (strcmp(enemy->team[k].name, fighters[j].champ.name) == 0) {
          if (fighters[j].alive == 1)
            alive[k] = 1;
        }
      }
    }
  }
  do {
    if (alive[i] == 1) {
      miss = rand() % 125 + 50 - (100 - fighter->move.stats.accuracy);
      if (verif == 1) {
        target = ally->team[i];
      } else {
        target = enemy->team[i];
      }
      def = target.stats.def;
      if (miss < target.stats.agi) {
        printf("%s a manqué %s.\n", fighter->champ.name, target.name);
      } else {
        percent = (rand() % 5 + 20) / 100.0;
        int damage = power - def * percent;
        if (damage < 0) {
          damage = power / 10;
        }
        printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
               damage, target.name);
        if (target.stats.shield <= 0) {
          target.stats.hp -= damage;
          if (target.stats.hp < 0) {
            target.stats.hp = 0;
            printf("%s est K.O.\n", target.name);
          }
        } else {
          int new_damage = 0;
          if (target.stats.shield < damage) {
            new_damage = damage - target.stats.shield;
            target.stats.shield = 0;
            target.stats.hp -= new_damage;
            printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                   target.name, new_damage);
          } else if (target.stats.shield == damage) {
            target.stats.shield = 0;
            printf("%s n'a plus de bouclier.\n", target.name);
          } else {
            target.stats.shield -= damage;
            printf("Le bouclier de %s perd %d points de vie.\n", target.name,
                   damage);
          }
        }
        for (int j = 0; j < 6; j++) {
          if (strcmp(target.name, fighters[j].champ.name) == 0) {
            star = searchEffect(&fighters[j], "Super Star");
          }
        }
        if (star == 0 && target.stats.hp == 0) {
          printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
          target.stats.hp = 1;
        }
        if (verif == 1) {
          ally->team[i] = target;
          if (target.stats.shield > 0) {
            printf(
                "%s a maintenant %d points de vie et %d points de vie sur son "
                "bouclier.\n",
                ally->team[i].name, ally->team[i].stats.hp,
                ally->team[i].stats.shield);
          } else {
            printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
                   ally->team[i].stats.hp);
          }
        } else {
          enemy->team[i] = target;
          if (target.stats.shield > 0) {
            printf(
                "%s a maintenant %d points de vie et %d points de vie sur son "
                "bouclier.\n",
                enemy->team[i].name, enemy->team[i].stats.hp,
                enemy->team[i].stats.shield);
          } else {
            printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
                   enemy->team[i].stats.hp);
          }
        }
      }
    }
    i = i + 1;
    if (i > alive[0] + alive[1] + alive[2])
      i = 0;
  } while (miss >= target.stats.agi && target.stats.hp != 0);
  printf("L'attaque \"%s\" de %s prend fin.\n", fighter->move.name,
         fighter->champ.name);
}

void hand(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int i = 0; i < 3; i++) {
    miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    def = target.stats.def;
    if (miss < target.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target.name);
    } else {
      percent = (rand() % 5 + 20) / 100.0;
      para = rand() % 100;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
             damage, target.name);
      check = searchEffect(fighter, "Paralysie");
      if (check != 0) {
        if (para < 30) {
          for (int i = 0; i < 6; i++) {
            if (strcmp(target.name, fighters[i].champ.name) == 0) {
              printf("%s est paralysé(e).\n", fighters[i].champ.name);
              fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                              fighter->move.stats.duration);
            }
          }
        }
      }
      printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
             damage, target.name);
      if (target.stats.shield <= 0) {
        target.stats.hp -= damage;
        if (target.stats.hp < 0) {
          target.stats.hp = 0;
          printf("%s est K.O.\n", target.name);
        }
      } else {
        int new_damage = 0;
        if (target.stats.shield < damage) {
          new_damage = damage - target.stats.shield;
          target.stats.shield = 0;
          target.stats.hp -= new_damage;
          printf("%s n'a plus de bouclier et perd %d points de vie.\n",
                 target.name, new_damage);
        } else if (target.stats.shield == damage) {
          target.stats.shield = 0;
          printf("%s n'a plus de bouclier.\n", target.name);
        } else {
          target.stats.shield -= damage;
          printf("Le bouclier de %s perd %d points de vie.\n", target.name,
                 damage);
        }
      }
      for (int j = 0; j < 6; j++) {
        if (strcmp(target.name, fighters[j].champ.name) == 0) {
          star = searchEffect(&fighters[j], "Super Star");
        }
      }
      if (star == 0 && target.stats.hp == 0) {
        printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
        target.stats.hp = 1;
      }
      if (verif == 1) {
        ally->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 ally->team[i].name, ally->team[i].stats.hp,
                 ally->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
                 ally->team[i].stats.hp);
        }
      } else {
        enemy->team[i] = target;
        if (target.stats.shield > 0) {
          printf("%s a maintenant %d points de vie et %d points de vie sur son "
                 "bouclier.\n",
                 enemy->team[i].name, enemy->team[i].stats.hp,
                 enemy->team[i].stats.shield);
        } else {
          printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
                 enemy->team[i].stats.hp);
        }
      }
    }
  }
}

void bots(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int verif, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  printf("%s utilise %s, son équipe gagne 50 points de défense pendant %d "
         "tours.\n",
         fighter->champ.name, fighter->move.name, fighter->move.stats.duration);
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        printf("Le buff \"Defense Bots\" est actif sur %s.\n",
               fighters[i].champ.name);
        fighters[i].buffs =
            addEffect(fighters[i].buffs, "bots", fighter->move.stats.duration);
      }
    }
    target.stats.def = target.stats.def + fighter->move.stats.power;
    if (verif == 1) {
      ally->team[i] = target;
    } else {
      enemy->team[i] = target;
    }
    printf("%s a maintenant %d points de defense.\n", target.name,
           target.stats.def);
  }
}

void tails(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, hits, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  float percent;
  hits = rand() % 10 + 1;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * hits;
    printf("%s frappe %d fois.", fighter->champ.name, hits);
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void flash(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void garrick(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  };
  float percent;
  miss = rand() % 125 + 25 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  def = target.stats.def;
  if (miss < target.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target.name);
  } else {
    percent = (rand() % 5 + 20) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name,
           damage, target.name);
    if (target.stats.shield <= 0) {
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
        printf("%s est K.O.\n", target.name);
      }
    } else {
      int new_damage = 0;
      if (target.stats.shield < damage) {
        new_damage = damage - target.stats.shield;
        target.stats.shield = 0;
        target.stats.hp -= new_damage;
        printf("%s n'a plus de bouclier et perd %d points de vie.\n",
               target.name, new_damage);
      } else if (target.stats.shield == damage) {
        target.stats.shield = 0;
        printf("%s n'a plus de bouclier.\n", target.name);
      } else {
        target.stats.shield -= damage;
        printf("Le bouclier de %s perd %d points de vie.\n", target.name,
               damage);
      }
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        star = searchEffect(&fighters[i], "Super Star");
      }
    }
    if (star == 0 && target.stats.hp == 0) {
      printf("La Super Star de %s l'empèche d'être K.O.\n", target.name);
      target.stats.hp = 1;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp,
               ally->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               ally->team[fighter->targets].name,
               ally->team[fighter->targets].stats.hp);
      }
    } else {
      enemy->team[fighter->targets] = target;
      if (target.stats.shield > 0) {
        printf("%s a maintenant %d points de vie et %d points de vie sur son "
               "bouclier.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp,
               enemy->team[fighter->targets].stats.shield);
      } else {
        printf("%s a maintenant %d points de vie.\n",
               enemy->team[fighter->targets].name,
               enemy->team[fighter->targets].stats.hp);
      }
    }
  }
}

void pride(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  int verif, check, para;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Paralysie");
  if (check == 0) {
    para = rand() % 100;
    if (para < 30) {
      printf("%s est paralysé(e), %s n'a pas pu agir.\n", fighter->champ.name,
             fighter->champ.name);
      return;
    }
  }
  check = searchEffect(fighter, "Saiyan Pride");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "pride", fighter->move.stats.duration);
  }
  target.stats.atk = target.stats.atk + fighter->move.stats.power;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Vegeta gagne 40 points d'attaque supplémentaire pendant %d tours.\n",
         fighter->move.stats.duration);
}
