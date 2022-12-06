#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_STACKS 9

typedef struct node {
  char box;
  struct node *next;
} NODE;

typedef struct stack {
  NODE *head;
} STACK;

char pop(STACK *col) {
  if (col == NULL || col->head == NULL) {
    return 0;
  }

  char result = col->head->box;

  NODE *temp = col->head;
  col->head = col->head->next;

  free(temp);

  return result;
}

void push(STACK *col, char item) {
  NODE *entry = malloc(sizeof(NODE));

  if (entry == NULL) {
    exit(EXIT_FAILURE);
  }

  entry->box = item;
  entry->next = col->head;
  col->head = entry;
}

void addToBottom(STACK *col, char item) {
  NODE *entry = malloc(sizeof(NODE));
  if (entry == NULL) {
    exit(EXIT_FAILURE);
  }
  entry->box = item;
  entry->next = NULL;
  if (col->head == NULL) {
    col->head = entry;
  } else {
    NODE *head = col->head;
    while (head->next != NULL) {
      head = head->next;
    }
    head->next = entry;
  }
}

int main() {
  FILE *stream;
  char *line = NULL;

  size_t len = 0;
  ssize_t nread;

  stream = fopen("./inputfiles/day_05.txt", "r");

  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  STACK *ship_first;
  ship_first = calloc(NUMBER_OF_STACKS, sizeof(STACK));
  if (ship_first == NULL) {
    perror("cannot allocate memory for ship");
    exit(EXIT_FAILURE);
  }

  STACK *ship_second;
  ship_second = calloc(NUMBER_OF_STACKS, sizeof(STACK));

  if (ship_second == NULL) {
    perror("cannot allocate memory for ship");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < NUMBER_OF_STACKS; i++) {
    ship_first[i].head = NULL;
    ship_second[i].head = NULL;
  }

  int curr_line = 0;

  while ((nread = getline(&line, &len, stream)) != -1) {
    if (curr_line < NUMBER_OF_STACKS) {
      for (int i = 0; i < NUMBER_OF_STACKS; i++) {
        char container_item = line[(i * 4) + 1];
        if (container_item != ' ') {
          addToBottom(&ship_first[i], container_item);
          addToBottom(&ship_second[i], container_item);
        }
      }
    } else if (curr_line > NUMBER_OF_STACKS) {

      int num_to_move;
      int start_box;
      int end_box;

      sscanf(line, "move %d from %d to %d", &num_to_move, &start_box, &end_box);

      STACK *ship_two_stack_in_motion;
      ship_two_stack_in_motion = malloc(sizeof(STACK));

      if (ship_two_stack_in_motion == NULL) {
        perror("failed to allocate memory");
        exit(EXIT_FAILURE);
      }
      ship_two_stack_in_motion->head = NULL;

      for (int i = 0; i < num_to_move; i++) {
        char item_ship_one = pop(&ship_first[start_box - 1]);
        if (item_ship_one != 0) {
          push(&ship_first[end_box - 1], item_ship_one);
        }

        char item_ship_two = pop(&ship_second[start_box - 1]);
        if (item_ship_two != 0) {
          push(ship_two_stack_in_motion, item_ship_two);
        }
      }

      while (ship_two_stack_in_motion->head != NULL) {
        char item_to_move = pop(ship_two_stack_in_motion);
        push(&ship_second[end_box - 1], item_to_move);
      }
      free(ship_two_stack_in_motion);
    }

    curr_line++;
  }

  for (int i = 0; i < NUMBER_OF_STACKS; i++) {
    printf("%c", ship_first[i].head->box);
  }

  printf("\n");

  for (int i = 0; i < NUMBER_OF_STACKS; i++) {
    if (ship_second[i].head != NULL) {
      printf("%c", ship_second[i].head->box);
    }
  }
  printf("\n");

  free(line);
  free(ship_first);
  free(ship_second);
  return EXIT_SUCCESS;
}
