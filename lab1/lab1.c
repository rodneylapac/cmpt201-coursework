#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  printf("Enter a sentence!: ");

  char *buff = NULL;
  size_t size = 0;
  ssize_t result = getline(&buff, &size, stdin);

  if (result != -1) {
    char *saveptr;
    char *ret = NULL;
    char *str = buff;

    while ((ret = strtok_r(str, " ", &saveptr))) {
      printf("%s\n", ret);
      str = NULL;
    }
  }

  free(buff);
}
