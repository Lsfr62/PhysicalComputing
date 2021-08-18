#include <stdio.h>
#include <stdlib.h>

                // 1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
int sensors[16] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
int testV = 0;
int lenk_winkel_rechts = 0;
int lenk_winkel_links = 0;
int lenken(int angle) {
    if (angle < 0) {
        testV--;
    } else {
        testV++;
    }
    return testV;
}

int evenSides() {
  for (int i = 0; i < 6; i++) {
    if (sensors[i] == 0) {
      printf("Es muss nach rechts abgebogen werden, Winkel = %d\n", lenken(++lenk_winkel_rechts));
      sensors[i] = 1;
      return -20;
    }
  }

  for (int i = 10; i < 16; i++) {
    if (sensors[i] == 0) {
      printf("Es muss nach links abgebogen werden, Winkel = %d\n", lenken(--lenk_winkel_links));
      sensors[i] = 1;
      return -20;
    }
  }

  return 0;
}

void turnIfNotOnLine() {
  int side = 0;
  while ((side = evenSides()) == -20);
}

int main(int argc, char const *argv[]) {
    if (evenSides() == -20) {
        turnIfNotOnLine();
        printf("Das Fahrzeug befindet sich in der Mitte\nSensors = {");
        for (int i = 0; i < 16; i++) {
            printf("%d ", sensors[i]);
        }
        printf("}\n");
    } else {
        printf("Das Fahrzeug befindet sich in der Mitte\n");
    }
    return 0;
}
