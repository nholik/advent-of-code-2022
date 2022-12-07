#include <stdio.h>
#include <stdlib.h>

#define WINDOW_SIZE 14

int main(void) {

  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_06.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  nread = getline(&line, &len, stream);

  int marker_index = 0;
  char *line_window = line;

  for (int i = 0; i < nread - 1; i++) {

    int all_diff = 1;

    for (int j = 0; j < WINDOW_SIZE; j++) {
      for (int k = j + 1; k < WINDOW_SIZE; k++) {
        if (line_window[k] == line_window[j]) {
          all_diff = 0;
          break;
        }
      }
      if (!all_diff) {
        break;
      }
    }
    if (all_diff) {
      break;
    }
    marker_index++;
    line_window++;
  }

  printf("%d\n", marker_index + WINDOW_SIZE);
  fclose(stream);
  free(line);
}
