#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_04.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int overlaps = 0;
  int overlap_intervals = 0;

  while ((nread = getline(&line, &len, stream)) != -1) {
    char *section_one = strtok(line, ",");
    char *section_two = strtok(NULL, ",");

    char *section_one_start = strtok(section_one, "-");
    char *section_one_end = strtok(NULL, "-");

    char *section_two_start = strtok(section_two, "-");
    char *section_two_end = strtok(NULL, "-");

    int start_one = strtol(section_one_start, (char **)NULL, 10);
    int end_one = strtol(section_one_end, (char **)NULL, 10);

    int start_two = strtol(section_two_start, (char **)NULL, 10);
    int end_two = strtol(section_two_end, (char **)NULL, 10);

    if ((start_one <= start_two && end_two <= end_one) ||
        (start_two <= start_one && end_one <= end_two)) {
      overlaps++;
    }

    if (((start_one <= start_two) && (start_two <= end_one)) ||
        ((start_two <= start_one) && (start_one <= end_two))) {
      overlap_intervals++;
    }
  }

  printf("answer part one: %d\n", overlaps);
  printf("answer part two: %d\n", overlap_intervals);

  return 0;
}
