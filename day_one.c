#include <stdio.h>
#include <stdlib.h>

#define ELFS_TO_TRACK 3

int find_min_index(long nums[ELFS_TO_TRACK]) {
  int min_index = 0;
  for (int i = 0; i < ELFS_TO_TRACK; i++) {
    if (nums[i] < nums[min_index]) {
      min_index = i;
    }
  }
  return min_index;
}

int main() {
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_01.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  long top_cals[ELFS_TO_TRACK];

  for (int i = 0; i < ELFS_TO_TRACK; i++) {
    top_cals[i] = 0;
  }

  long elf_cals = 0;

  while ((nread = getline(&line, &len, stream)) != -1) {
    if (line[0] == '\n') {
      for (int i = 0; i < ELFS_TO_TRACK; i++) {
        int min_index = find_min_index(top_cals);
        if (elf_cals > top_cals[min_index]) {
          top_cals[min_index] = elf_cals;
          break;
        }
      }
      elf_cals = 0;
    } else {
      long cals = strtol(line, (char **)NULL, 10);
      elf_cals += cals;
    }
  }

  for (int i = 1; i < ELFS_TO_TRACK; i++) {
    top_cals[0] += top_cals[i];
  }

  printf("max cals = %ld\n", top_cals[0]);

  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}
