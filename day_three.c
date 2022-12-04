#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)                                          \
  (((i)&0x80ll) ? '1' : '0'), (((i)&0x40ll) ? '1' : '0'),                      \
      (((i)&0x20ll) ? '1' : '0'), (((i)&0x10ll) ? '1' : '0'),                  \
      (((i)&0x08ll) ? '1' : '0'), (((i)&0x04ll) ? '1' : '0'),                  \
      (((i)&0x02ll) ? '1' : '0'), (((i)&0x01ll) ? '1' : '0')

#define PRINTF_BINARY_PATTERN_INT16                                            \
  PRINTF_BINARY_PATTERN_INT8 PRINTF_BINARY_PATTERN_INT8
#define PRINTF_BYTE_TO_BINARY_INT16(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT8((i) >> 8), PRINTF_BYTE_TO_BINARY_INT8(i)
#define PRINTF_BINARY_PATTERN_INT32                                            \
  PRINTF_BINARY_PATTERN_INT16 PRINTF_BINARY_PATTERN_INT16
#define PRINTF_BYTE_TO_BINARY_INT32(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT16((i) >> 16), PRINTF_BYTE_TO_BINARY_INT16(i)
#define PRINTF_BINARY_PATTERN_INT64                                            \
  PRINTF_BINARY_PATTERN_INT32 PRINTF_BINARY_PATTERN_INT32
#define PRINTF_BYTE_TO_BINARY_INT64(i)                                         \
  PRINTF_BYTE_TO_BINARY_INT32((i) >> 32), PRINTF_BYTE_TO_BINARY_INT32(i)

int get_item_index(char c) {
  char first = isupper(c) ? 'A' : 'a';
  return ((int)c - first) + (26 * (isupper(c) > 0));
}

int get_duplicate_index(uint64_t duplicates) {
  int duplicate_index = 1;

  while (duplicates) {
    if ((duplicates & (u_int64_t)1) == 1) {
      break;
    }
    duplicates >>= 1;
    duplicate_index++;
  }

  return duplicate_index;
}

int main() {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_03.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int total_priority = 0;
  int commont_priority = 0;
  uint64_t group_contents[3] = {0, 0, 0};

  int curr_line_num = 0;

  while ((nread = getline(&line, &len, stream)) != -1) {
    uint64_t first_half_counts = 0;
    uint64_t second_half_counts = 0;

    int half_way = (nread - 1) / 2;

    for (int i = 0; i < nread - 1; i++) {
      char entry = line[i];
      uint64_t entry_index = ((u_int64_t)1 << (uint64_t)get_item_index(entry));

      if (i < half_way) {
        first_half_counts |= entry_index;
      } else {
        second_half_counts |= entry_index;
      }
    }

    group_contents[curr_line_num % 3] = second_half_counts | first_half_counts;

    if (curr_line_num % 3 == 2) {
      uint64_t common_elt =
          group_contents[0] & group_contents[1] & group_contents[2];
      int common_duplicate_index = get_duplicate_index(common_elt);
      commont_priority += common_duplicate_index;
    }

    u_int64_t duplicates = first_half_counts & second_half_counts;

    total_priority += get_duplicate_index(duplicates);
    curr_line_num++;
  }

  printf("answer part one: %d\n", total_priority);
  printf("answer part two: %d\n", commont_priority);
}
