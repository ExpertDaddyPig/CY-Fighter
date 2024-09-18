#include "baseFunctions.h"
#include "effectsFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void blizzard(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
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
    if (verif != 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    for (int i = 0; i < 6; i++) {
      if (strcmp(target.name, fighters[i].champ.name) == 0) {
        printf("L'effet \"Kunaï Explosifs\" est actif sur %s.\n",
               fighters[i].champ.name);
        fighters[i].debuffs = addEffect(fighters[i].debuffs, "kunai",
                                        fighter->move.stats.duration);
      }
    }
  }
}

void byakugan(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
              Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Byakugan");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "byakugan", fighter->move.stats.duration);
  }
  target.stats.atk += 20;
  target.stats.def += 20;
  target.stats.agi += 20;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Hinata active son Byakugan.\n");
}

void expert(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  Fighter target;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para;
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
  } else {
    target = enemy->team[fighter->targets];
  }
  int damage = power;
  printf("%s inflige %d points de dégâts à %s.\n", fighter->champ.name, damage,
         target.name);
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
      printf("%s n'a plus de bouclier et perd %d points de vie.\n", target.name,
             new_damage);
    } else if (target.stats.shield == damage) {
      target.stats.shield = 0;
      printf("%s n'a plus de bouclier.\n", target.name);
    } else {
      target.stats.shield -= damage;
      printf("Le bouclier de %s perd %d points de vie.\n", target.name, damage);
    }
  }
  for (int i = 0; i < 6; i++) {
    if (strcmp(target.name, fighters[i].champ.name) == 0) {
      star = searchEffect(&fighters[i], "Super Star");
    }
  }
  if (star == 0 && target.stats.hp == 0) {
    printf("La Super Star de %s l'empèche d'être K.O.", target.name);
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

void kyubi(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Mode Chakra de Kyubi");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "kyubi", fighter->move.stats.duration);
  }
  target.stats.atk += 30;
  target.stats.spd += 30;
  target.stats.agi += 20;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Naruto active le Mode Chakra de Kyubi.\n");
}

void meteor(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
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
  miss = rand() % 125 + 50 - (100 - fighter->move.stats.accuracy);
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
      printf("La Super Star de %s l'empèche d'être K.O.", target.name);
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

void mystery(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
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
      percent = (rand() % 5 + 35) / 100.0;
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
        printf("La Super Star de %s l'empèche d'être K.O.", target.name);
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

void blossom(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  Fighter target;
  int verif, check, star = 1, para, heal = fighter->move.stats.power;
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
    for (int j = 0; j < 6; j++) {
      if (strcmp(target.name, fighters[j].champ.name) == 0) {
        printf("L'effet \"Régénération\" est actif sur %s pendant %d tours.\n",
               fighters[j].champ.name, fighter->move.stats.duration + 7);
        fighters[j].buffs = addEffect(fighters[j].buffs, "regeneration",
                                      fighter->move.stats.duration + 7);
      }
    }
    if (verif != 1) {
      target = ally->team[i];
    } else {
      target = enemy->team[i];
    }
    for (int j = 0; j < 6; j++) {
      if (strcmp(target.name, fighters[j].champ.name) == 0) {
        printf("%s s'est endormi(e) pendant %d tours.\n",
               fighters[j].champ.name, fighter->move.stats.duration);
        fighters[j].debuffs = addEffect(fighters[j].debuffs, "sleep",
                                        fighter->move.stats.duration);
      }
    }
  }
}

void laser(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  Fighter target, self;
  int power = fighter->move.stats.power + fighter->champ.stats.atk / 10;
  int def, verif, miss, check, star = 1, para, shield = 75;
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
  miss = rand() % 125 + 50 - (100 - fighter->move.stats.accuracy);
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif == 1) {
    target = ally->team[fighter->targets];
    self = enemy->team[fighter->champIndex];
  } else {
    target = enemy->team[fighter->targets];
    self = ally->team[fighter->champIndex];
  }
  self.stats.shield += shield;
  printf("%s obtient un bouclier équivalent à %d points de vie.\n", self.name, shield);
  if (verif == 1) {
    enemy->team[fighter->champIndex] = self;
  } else {
    ally->team[fighter->champIndex] = self;
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
      printf("La Super Star de %s l'empèche d'être K.O.", target.name);
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

void serious(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
             Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  check = searchEffect(fighter, "Serious Mode");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "serious", fighter->move.stats.duration);
  }
  printf("Saitama devient serieux.\n");
}

void saiyan(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Super Saiyan");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "ssj", fighter->move.stats.duration);
  }
  target.stats.atk += 20;
  target.stats.spd += 20;
  target.stats.agi += 20;
  target.stats.def += 20;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("%s se transforme en Super Saiyan.\n", target.name);
}

void super(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Super Sonic");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "super", fighter->move.stats.duration);
  }
  target.stats.atk += 30;
  target.stats.spd += 50;
  target.stats.def += 50;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Sonic se transforme en Super Sonic.\n");
}

void star(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally, Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Super Star");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "star", fighter->move.stats.duration);
  }
  target.stats.spd += 30;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("%s utilise une Super Star et devient invincible pendant %d tours.\n",
         fighter->champ.name, fighter->move.stats.duration);
}

void susano(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Susano");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "susano", fighter->move.stats.duration);
  }
  target.stats.atk += 30;
  target.stats.def += 50;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Sasuke utilise son Susano.\n");
}

void ultra(ActiveTeam *fighters, ActiveTeam *fighter, Team *ally,
            Team *enemy) {
  int verif, check;
  Fighter target = ally->team[fighter->champIndex];
  verif = verifyTeam(fighter->champ, *enemy);
  if (verif != 1) {
    target = enemy->team[fighter->champIndex];
  }
  check = searchEffect(fighter, "Ultra Instinct");
  if (check != 0) {
    fighter->buffs =
        addEffect(fighter->buffs, "ultra instinct", fighter->move.stats.duration);
  }
  target.stats.spd += 10;
  target.stats.agi += 60;
  if (verif == 1) {
    ally->team[fighter->champIndex] = target;
  } else {
    enemy->team[fighter->champIndex] = target;
  }
  printf("Shaggy passe en Ultra Instinct 0.00001%%.\n");
}