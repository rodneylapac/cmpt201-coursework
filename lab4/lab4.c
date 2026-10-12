#define _DEFAULT_SOURCE
#define _ISOC99_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 64
#define HEAP_SIZE 256

struct header {
  uint64_t size;
  struct header *next;
};

void error(char *msg) {
  perror(msg);
  exit(EXIT_FAILURE);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *start = sbrk(HEAP_SIZE);

  if (start == (void *)-1) {
    error("sbrk");
  }

  struct header *first = (struct header *)start;

  struct header *second = (struct header *)((char *)start + 128);

  first->size = 128;
  first->next = NULL;

  second->size = 128;
  second->next = first;

  char *first_data = (char *)first + sizeof(struct header);
  char *second_data = (char *)second + sizeof(struct header);

  size_t data_size = 128 - sizeof(struct header);

  memset(first_data, 0, data_size);
  memset(second_data, 1, data_size);

  print_out("first block: %p\n", &first, sizeof(first));
  print_out("second block: %p\n", &second, sizeof(second));

  print_out("first block size: %lu\n", &first->size, sizeof(first->size));
  print_out("first block next: %p\n", &first->next, sizeof(first->next));

  print_out("second block size: %lu\n", &second->size, sizeof(second->size));
  print_out("second block next: %p\n", &second->next, sizeof(second->next));

  for (int i = 0; i < data_size; i++) {
    uint64_t value = (char)first_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }

  for (int i = 0; i < data_size; i++) {
    uint64_t value = (char)second_data[i];
    print_out("%lu\n", &value, sizeof(value));
  }
}
