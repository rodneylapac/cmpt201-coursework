#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *best_fit_id = NULL;
  // TODO: Implement best fit

  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      if (best_fit_id == NULL || current->size < best_fit_id->size) {
        best_fit_id = current;
      }
    }

    current = current->next;
  }

  if (best_fit_id == NULL) {
    return -1;
  }

  return best_fit_id->id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement worst fit
  struct header *worst_fit_id = NULL;
  struct header *current = free_list_ptr;

  while (current != NULL) {
    if (current->size >= size) {
      if (worst_fit_id == NULL || current->size > worst_fit_id->size) {
        worst_fit_id = current;
      }
    }

    current = current->next;
  }

  if (worst_fit_id == NULL) {
    return -1;
  }
  return worst_fit_id->id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs

  printf("First fit ID: %d\n", first_fit_id);
  printf("Best fit ID: %d\n", best_fit_id);
  printf("Worst fit ID: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

// PART 2
//
// 1. Insert free block into the linked free list which is in order of memory
//    adresses
//
// 2. While loop through the free list starting with the first block.
//
// 3. If the first block touches in memory with the next block it points to, merge
//    them into one block. If they dont touch in memory, move onto the next block
//    and repeat.
//
// 4. Repeat step 3 until you have reached the end of the list.
//
