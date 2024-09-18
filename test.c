#include <stdio.h>
#include <string.h>

#define color(param) printf("\033[%sm", param)

void main() {
  color("91");
  printf("RED");
  color("0");
  printf("\n");
  color("31");
  printf("DARKRED");
  color("0");
  printf("\n");
  color("93");
  printf("YELLOW");
  color("0");
  printf("\n");
  color("33");
  printf("DARKYELLOW");
  color("0");
  printf("\n");
  color("92");
  printf("GREEN");
  color("0");
  printf("\n");
  color("32");
  printf("DARKGEREN");
  color("0");
  printf("\n");
}