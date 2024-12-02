#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LEN_LIMIT 30
#define VAL_LIMIT 30

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    perror("Error opening file!\n");
    return 1;
  }

  char line[LINE_LEN_LIMIT];
  int safe_lines = 0;

  while (fgets(line, sizeof(line), file)) {

    int values[30];
    int index = 0;

    // trim newline
    line[strcspn(line, "\n")] = '\0';

    char *strVal;
    int curVal;

    strVal = strtok(line, " \t");
    while (strVal != NULL) {
      curVal = atoi(strVal);
      strVal = strtok(NULL, " \t");
      values[index] = curVal;
      index++;
    }

    enum { UNSET = 0, DECREASING = -1, INCREASING = 1 };
    int direction = UNSET; //  init to 0, -1 for decreasing, 1 for increasing
    int add_safe = 1;      // assume safe at init

    for (int i = 0; i < index - 1; i++) {
      int a = values[i];
      int b = values[i + 1];
      int diff = abs(a - b);

      // break on out of range diff or value equality
      if (diff > 3 || a == b) {
        add_safe = 0;
        break;
      }

      // set direction
      if (direction == 0) {
        direction = (a < b) ? INCREASING : DECREASING;
      }

      // check direction flip
      if ((direction == 1 && a > b) || (direction == -1 && a < b)) {
        add_safe = 0;
        break;
      }
    }

    if (add_safe == 1) {
      safe_lines++;
    }
  }

  fclose(file);

  printf("Safe Line Count: %d\n", safe_lines);
}
