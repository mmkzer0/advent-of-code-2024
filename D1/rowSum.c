#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10000
#define MAX_LEN 1024

int compare_integers(const void *a, const void *b) {
  const int *int1 = (const int *)a;
  const int *int2 = (const int *)b;
  return (*int1 > *int2) -
         (*int1 < *int2); // Alternative to `return (*int1 - *int2)`
}

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

  char line[MAX_LEN];
  int firstTokens[MAX_LINES];
  int secTokens[MAX_LINES];
  int linecount = 0;

  while (fgets(line, sizeof(line), file)) {
    if (linecount >= MAX_LINES) {
      fprintf(stderr, "Error: too may lines!\n");
      break;
    }

    // trim newline
    line[strcspn(line, "\n")] = '\0';

    char *tok = strtok(line, " \t");
    firstTokens[linecount] = atoi(tok);

    tok = strtok(NULL, " \t");
    secTokens[linecount] = atoi(tok);

    linecount++;
  }

  fclose(file);

  int out = 0;
  for (int i = 0; i < linecount; i++) {
    int a = firstTokens[i];
    int mult = 0;

    for (int j = 0; j < linecount; j++) {
      if (a == secTokens[j]) {
        mult += 1;
      }
    }
    out += a * mult;
  }

  printf("Result: %d\n", out);

  return 0;
}
