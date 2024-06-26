#include "attacksFunctions.h"
#include "baseFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// This is the code of every moves that can be used in the game

void basic(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  Move move = fighter->move;
  int power = fighter->champ.stats.atk;
  int def, verif, miss = 0;
  float percent;
  miss = rand() % 125;
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
      fighter->buffs = addEffect(fighter->buffs, move);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
      fighter->buffs = addEffect(fighter->buffs, move);
    }
  }
}

void pizza(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power;
  int verif;
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
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void avion(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void kamehameha(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy) * 5;
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void kaioken(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target = ally->team[fighter->targets];
  printf("%s utilise %s.\n", target.name, fighter->move.name);
  target.stats.atk = target.stats.atk * 2;
  printf("%s a maintenant %d points d'attaque.\n",
         ally->team[fighter->targets].name,
         ally->team[fighter->targets].stats.atk);
}

void ramen(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, missing;
  int verif;
  verif = verifyTeam(fighter->champ, *ally);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  missing = target.stats.hpMax - target.stats.hp;
  heal = heal + missing * 0.3;
  if (target.stats.hp > 0) {
    printf("La capacité %s redonne %d points de vie à %s.\n",
           fighter->move.name, heal, target.name);
    target.stats.hp += heal;
    if (target.stats.hp > target.stats.hpMax) {
      target.stats.hp = target.stats.hpMax;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void paume(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void acier(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void seisme(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int i = 0; i < 3; i++) {
    miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    def = target.stats.def;
    if (miss < target.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target.name);
    } else {
      percent = (rand() % 5 + 30) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
             target.name);
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
      }
      if (verif == 1) {
        ally->team[i] = target;
        printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
               ally->team[i].stats.hp);
      } else {
        enemy->team[i] = target;
        printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
               enemy->team[i].stats.hp);
      }
    }
  }
}

void thunder(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy, int pos1, int pos2) {
  Fighter target1, target2;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target1 = ally->team[pos1];
    target2 = ally->team[pos2];
  } else {
    target1 = enemy->team[pos1];
    target2 = enemy->team[pos2];
  }
  def = target1.stats.def;
  if (miss < target1.stats.agi || miss < target2.stats.agi) {
    if (miss < target1.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target1.name);
    }
    if (miss < target2.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target2.name);
    }
  } else {
    if (miss > target1.stats.agi) {
      percent = (rand() % 5 + 30) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
             target1.name);
      target1.stats.hp -= damage;
    }
    def = target2.stats.def;
    if (miss > target2.stats.agi) {
      percent = (rand() % 5 + 30) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
             target2.name);
      target2.stats.hp -= damage;
    }
    if (target1.stats.hp < 0) {
      target1.stats.hp = 0;
    }
    if (target2.stats.hp < 0) {
      target2.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[pos1] = target1;
      ally->team[pos2] = target2;
      printf("%s a maintenant %d points de vie.\n", ally->team[pos1].name,
             ally->team[pos1].stats.hp);
      printf("%s a maintenant %d points de vie.\n", ally->team[pos2].name,
             ally->team[pos2].stats.hp);
    } else {
      enemy->team[pos1] = target1;
      enemy->team[pos2] = target2;
      printf("%s a maintenant %d points de vie.\n", enemy->team[pos1].name,
             enemy->team[pos1].stats.hp);
      printf("%s a maintenant %d points de vie.\n", enemy->team[pos2].name,
             enemy->team[pos2].stats.hp);
    }
  }
}

void boomerang(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    printf("Le boomerang revient, %s inflige %d dégâts à %s.\n",
           fighter->champ.name, damage, target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void fire(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    percent = (rand() % 5 + 30) / 100.0;
    damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * 1.25;
    printf("%s renvoie une boule de feu et inflige %d dégâts à %s.\n",
           fighter->champ.name, damage, target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void ice(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, freeze;
  float percent;
  freeze = rand() % 100;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (freeze > 0) {
      printf("%s est gelé.\n", target.name);
      target.stats.spd = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void rasengan(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void clone(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, clones;
  float percent;
  clones = rand() % 5 + 1;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * clones;
    printf("%s a fait apparaitre %d clones qui frapperont tous une fois.",
           fighter->champ.name, clones);
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void golf(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void peche(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power;
  int verif;
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    if (target.stats.hp > 0) {
      if (target.stats.hp < target.stats.hpMax) {
        target.stats.hp += heal;
        if (target.stats.hp > target.stats.hpMax) {
          target.stats.hp = target.stats.hpMax;
        }
        printf("La capacité %s redonne %d points de vie à %s.\n",
               fighter->move.name, heal, target.name);
        printf("%s a maintenant %d points de vie.\n", target.name,
               target.stats.hp);
      }
      if (verif == 1) {
        ally->team[i] = target;
      } else {
        enemy->team[i] = target;
      }
    } else if (target.stats.hp - target.stats.hpMax == 0) {
      printf("%s ne peut pas regagner des points de vie car ses points de vies "
             "sont au maximum.\n",
             target.name);
    } else {
      printf("\n%s est K.O. et ne peut pas regagner des points de vie.\n",
             target.name);
    }
  }
}

void boule(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void punch(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void cherry(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void heal(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power;
  int verif;
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
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void katon(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + 50 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void chidori(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void croque(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power;
  int verif;
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
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void repos(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power;
  int verif;
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
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void spinattack(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void homming(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void hand(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  verif = verifyTeam(fighter->champ, *enemy);
  for (int i = 0; i < 3; i++) {
    miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    def = target.stats.def;
    if (miss < target.stats.agi) {
      printf("%s a manqué %s.\n", fighter->champ.name, target.name);
    } else {
      percent = (rand() % 5 + 30) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
             target.name);
      target.stats.hp -= damage;
      if (target.stats.hp < 0) {
        target.stats.hp = 0;
      }
      if (verif == 1) {
        ally->team[i] = target;
        printf("%s a maintenant %d points de vie.\n", ally->team[i].name,
               ally->team[i].stats.hp);
      } else {
        enemy->team[i] = target;
        printf("%s a maintenant %d points de vie.\n", enemy->team[i].name,
               enemy->team[i].stats.hp);
      }
    }
  }
}

void bots(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int verif;
  printf(
      "%s utilise %s, son équipe gagne 10 points de défense pendant 4 tours.\n",
      fighter->champ.name, fighter->move.name);
  verif = verifyTeam(fighter->champ, *ally);
  for (int i = 0; i < 3; i++) {
    if (verif == 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    target.stats.def = target.stats.def + 10;
    if (verif == 1) {
      ally->team[i] = target;
    } else {
      enemy->team[i] = target;
    }
    printf("%s a maintenant %d points de defense.\n", target.name,
           target.stats.def);
  }
}

void flash(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}

void garrick(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss;
  float percent;
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 30) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->targets].name,
             ally->team[fighter->targets].stats.hp);
    } else {
      enemy->team[fighter->targets] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->targets].name,
             enemy->team[fighter->targets].stats.hp);
    }
  }
}
