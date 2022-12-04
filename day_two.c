#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPPONENT_ROCK 'A'
#define OPPONENT_PAPER 'B'
#define OPPONENT_SCISSORS 'C'

#define SELF_ROCK 'X'
#define SELF_PAPER 'Y'
#define SELF_SCISSORS 'Z'

#define RESPONSE_LOSE 'X'
#define RESPONSE_DRAW 'Y'
#define RESPONSE_WIN 'Z'

#define CHOICE_ROCK 0
#define CHOICE_PAPER 1
#define CHOICE_SCISSORS 2

#define POINTS_ROCK 1
#define POINTS_PAPER 2
#define POINTS_SCISSORS 3

#define POINTS_WIN 6
#define POINTS_DRAW 3
#define POINTS_LOSS 0

#define USE_SECRET_SRAT 1

int modulo_Euclidean(int a, int b) {
  int m = a % b;
  if (m < 0) {
    m = (b < 0) ? m - b : m + b;
  }
  return m;
}

int get_choice_position(char choice) {
  switch (choice) {
  case SELF_ROCK:
  case OPPONENT_ROCK:
    return 0;
  case SELF_PAPER:
  case OPPONENT_PAPER:
    return 1;
  case SELF_SCISSORS:
  case OPPONENT_SCISSORS:
    return 2;
  default:
    perror("invalid input");
    exit(EXIT_FAILURE);
  }
}

int get_points_choice(int choice_index) {
  switch (choice_index) {
  case CHOICE_ROCK:
    return POINTS_ROCK;
  case CHOICE_SCISSORS:
    return POINTS_SCISSORS;
  case CHOICE_PAPER:
    return POINTS_PAPER;
  default:
    perror("invalid input");
    exit(EXIT_FAILURE);
  }
}

int get_choice_for_strategy(int opponent_choice, char response_choice) {
  if (response_choice == RESPONSE_DRAW) {
    return opponent_choice;
  }

  if (response_choice == RESPONSE_WIN) {
    return (opponent_choice + 1) % 3;
  }

  return modulo_Euclidean(opponent_choice - 1, 3);
}

int calc_round_score(char opponent_choice, char self_choice, int strategy) {
  printf("calculating score %c %c ", opponent_choice, self_choice);

  int opoonent_choice_pos = get_choice_position(opponent_choice);
  int self_choice_pos =
      strategy == USE_SECRET_SRAT
          ? get_choice_for_strategy(opoonent_choice_pos, self_choice)
          : get_choice_position(self_choice);

  printf("calculating score %c %c (%d %d) ", opponent_choice, self_choice,
         opoonent_choice_pos, self_choice_pos);

  int choice_points = get_points_choice(self_choice_pos);

  if (opoonent_choice_pos == self_choice_pos) {
    return POINTS_DRAW + choice_points;
  }

  // you win if the index of the choice mod 3 (number of options) is 1
  if (modulo_Euclidean(self_choice_pos - opoonent_choice_pos, 3) == 1) {
    return POINTS_WIN + choice_points;
  }

  return choice_points;
}

int main() {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_02.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  int score = 0;
  while ((nread = getline(&line, &len, stream) != -1)) {
    char *opp_choice = strtok(line, " ");
    char *self_choice = strtok(NULL, " ");
    int round_score = calc_round_score(opp_choice[0], self_choice[0], USE_SECRET_SRAT);
    score += round_score;
    printf(" - score is %d\n", round_score);
  }

  printf("Total score is %d\n", score);
  return 0;
}
