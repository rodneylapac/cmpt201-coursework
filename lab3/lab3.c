#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 5

void addInput(char *history[], size_t *currentSize, char *input) {
  if (*currentSize == MAX_CAPACITY) {
    free(history[0]);

    for (int i = 1; i < *currentSize; i++) {
      history[i - 1] = history[i];
    }

    (*currentSize)--;
  }

  history[*currentSize] = input;
  (*currentSize)++;
}

void printHistory(char *history[], size_t currentSize) {
  for (int i = 0; i < currentSize; i++) {
    printf("%s\n", history[i]);
  }
}

void clearHistory(char *history[], size_t currentSize) {
  for (int i = 0; i < currentSize; i++) {
    free(history[i]);
  }
}

int main() {

  char *history[MAX_CAPACITY] = {NULL};
  size_t currentSize = 0;

  while (1) {
    char *input = NULL;
    size_t size = 0;

    printf("Input a line: ");
    fflush(stdout);

    ssize_t length = getline(&input, &size, stdin);

    if (length > 0 && (input[length - 1] == '\n')) {
      input[length - 1] = '\0';
    }

    addInput(history, &currentSize, input);

    if (strcmp(input, "print") == 0) {
      printHistory(history, currentSize);
    }
  }

  clearHistory(history, currentSize);

  return 0;
}
