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
  int def, verif, miss = 0, check, para, kaio = 1;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void pizza(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, para;
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
      ally->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->champIndex].name,
             ally->team[fighter->champIndex].stats.hp);
    } else {
      enemy->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->champIndex].name,
             enemy->team[fighter->champIndex].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void avion(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void kamehameha(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                Team *enemy) {
  Fighter target;
  int def, verif, miss, check, para, kaio = 1;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n\n", fighter->champ.name, damage,
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

void kaioken(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target = ally->team[fighter->champIndex];
  int check, para;
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

void ramen(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, missing, verif, check, para;
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
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
  int def, verif, miss, check, para, stun;
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
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
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

void seisme(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
      percent = (rand() % 5 + 35) / 100.0;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void thunder(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy,
             int pos1, int pos2) {
  Fighter target1, target2;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
  if (miss < target1.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target1.name);
  } else if (miss > target1.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target1.name);
    check = searchEffect(fighter, "Paralysie");
    if (check != 0) {
      if (para < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target1.name, fighters[i].champ.name) == 0) {
            printf("%s est paralysé(e).\n", target1.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    target1.stats.hp -= damage;
    if (target1.stats.hp < 0) {
      target1.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[pos1] = target1;
      printf("%s a maintenant %d points de vie.\n", ally->team[pos1].name,
             ally->team[pos1].stats.hp);
    } else {
      enemy->team[pos1] = target1;
      printf("%s a maintenant %d points de vie.\n", enemy->team[pos1].name,
             enemy->team[pos1].stats.hp);
    }
  }
  def = target2.stats.def;
  if (miss < target2.stats.agi) {
    printf("%s a manqué %s.\n", fighter->champ.name, target2.name);
  } else if (miss > target2.stats.agi) {
    para = rand() % 100;
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target2.name);
    check = searchEffect(fighter, "Paralysie");
    if (check != 0) {
      if (para < 30) {
        for (int i = 0; i < 6; i++) {
          if (strcmp(target2.name, fighters[i].champ.name) == 0) {
            printf("%s est paralysé(e).\n", target2.name);
            fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                            fighter->move.stats.duration);
          }
        }
      }
    }
    target2.stats.hp -= damage;
    if (target2.stats.hp < 0) {
      target2.stats.hp = 0;
    }
    if (verif == 1) {
      ally->team[pos2] = target2;
      printf("%s a maintenant %d points de vie.\n", ally->team[pos2].name,
             ally->team[pos2].stats.hp);
    } else {
      enemy->team[pos2] = target2;
      printf("%s a maintenant %d points de vie.\n", enemy->team[pos2].name,
             enemy->team[pos2].stats.hp);
    }
  }
}

void boomerang(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
               Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    printf("Le boomerang revient, %s inflige %d points de dégâts à %s.\n",
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
  int def, verif, miss, check, para, burn;
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
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    percent = (rand() % 5 + 35) / 100.0;
    damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * 1.25;
    printf("%s renvoie une boule de feu et inflige %d points de dégâts à %s.\n",
           fighter->champ.name, damage, target.name);
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
  int def, verif, miss, freeze, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
    if (target.stats.hp < 0) {
      target.stats.hp = 0;
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

void rasengan(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
              Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
  int def, verif, miss, clones, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    damage = damage * clones;
    printf("%s a fait apparaitre %d clones qui frapperont tous une fois.",
           fighter->champ.name, clones);
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
  int def, verif, miss, stun, check, para;
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
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    target.stats.hp -= damage;
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
  int heal = fighter->move.stats.power, verif, check, para;
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
        printf("%s a maintenant %d points de vie.\n", target.name,
               target.stats.hp);
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

void boule(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para, stun;
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
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
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
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void cherry(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
  int heal = fighter->move.stats.power, verif, check, para;
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
  int def, verif, miss, check, para, burn;
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
  miss = rand() % 100 + 50 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    {
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

void chidori(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
  miss = rand() % 100 + (100 - fighter->move.stats.accuracy);
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
           target.name);
    if (para < 30) {
      for (int i = 0; i < 6; i++) {
        if (strcmp(target.name, fighters[i].champ.name) == 0) {
          printf("%s est paralysé(e).\n", target.name);
          fighters[i].debuffs = addEffect(fighters[i].debuffs, "paralyze",
                                          fighter->move.stats.duration);
        }
      }
    }
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

void croque(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, para;
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
      ally->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->champIndex].name,
             ally->team[fighter->champIndex].stats.hp);
    } else {
      enemy->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->champIndex].name,
             enemy->team[fighter->champIndex].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void repos(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int heal = fighter->move.stats.power, verif, check, para;
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
      ally->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             ally->team[fighter->champIndex].name,
             ally->team[fighter->champIndex].stats.hp);
    } else {
      enemy->team[fighter->champIndex] = target;
      printf("%s a maintenant %d points de vie.\n",
             enemy->team[fighter->champIndex].name,
             enemy->team[fighter->champIndex].stats.hp);
    }
  } else {
    printf("%s est K.O. et ne peut pas regagner de points de vie.\n",
           target.name);
  }
}

void spinattack(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
                Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void homming(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
  int def, verif, miss, check, para;
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
      percent = (rand() % 5 + 35) / 100.0;
      para = rand() % 100;
      int damage = power - def * percent;
      if (damage < 0) {
        damage = power / 10;
      }
      printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
             target.name);
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
  int verif, check, para;
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

void flash(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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

void garrick(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, para;
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
    percent = (rand() % 5 + 35) / 100.0;
    int damage = power - def * percent;
    if (damage < 0) {
      damage = power / 10;
    }
    printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
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
