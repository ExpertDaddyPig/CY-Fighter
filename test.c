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
  printf("%d\n", makePipi().boudin);
}