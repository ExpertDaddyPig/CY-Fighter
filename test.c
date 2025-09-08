#include <stdio.h>
#include <string.h>

#define color(param) printf("\033[%sm", param)

typedef struct {
  int caca;
  int boudin;
} pipi;

pipi makePipi() {
  pipi A;
  A.boudin = 2;
  A.caca = 14;
  return A;
}

void main() {
  printf("┏[Baby Bot Team]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
  printf("┃    Saitama          K.O.     Tails            K.O.     Son Goku          |3|   ┃\n");
  printf("┃    [ ⚡⛄💖🔥✨💤🔺🔻 ]      [   ⛄💖           ]      [ ⚡⛄💖🔥✨💤🔺🔻 ]    ┃\n");
  printf("┃   [ 000/200 ]  [ ⛨ 000 ]    [ 000/200 ]  [ ⛨ 000 ]    [ 081/210 ]  [ ⛨ 000 ]   ┃\n");
  printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}