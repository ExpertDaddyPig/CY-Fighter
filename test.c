#include <stdio.h>
#include <string.h>

#define color(param) printf("\033[%sm", param)

void main() {
  char col[10];
  for (int i = 0; i <= 7; i++) {
    sprintf(col, "3%d", i);
    color(col);
    printf("■■■■■■■■■■■■■■■■■■■■");
    color("0");
    printf("\n");
  }
  for (int i = 0; i <= 7; i++) {
    sprintf(col, "4%d", i);
    color(col);
    printf("■■■■■■■■■■■■■■■■■■■■");
    color("0");
    printf("\n");
  }
  for (int i = 0; i <= 7; i++) {
    sprintf(col, "9%d", i);
    color(col);
    printf("■■■■■■■■■■■■■■■■■■■■");
    color("0");
    printf("\n");
  }
  for (int i = 0; i <= 7; i++) {
    sprintf(col, "10%d", i);
    color(col);
    printf("■■■■■■■■■■■■■■■■■■■■");
    color("0");
    printf("\n");
  }
}