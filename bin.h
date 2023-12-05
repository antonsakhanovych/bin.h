#ifndef BINARY_HEAP
#define BINARY_HEAP
#define INITIAL_CAPACITY 3

#include <stdlib.h>

typedef struct {
  int *nodes;
  size_t size;
  size_t cap;
} Binary_Heap;

Binary_Heap *binheap_init();

void binheap_print(Binary_Heap *self);

Binary_Heap *binheap_construct(int *arr, size_t size);

void binheap_insert(Binary_Heap *self, int val);

int binheap_find_min(Binary_Heap *self);

int binheap_del_min(Binary_Heap *self);

Binary_Heap *binheap_merge(Binary_Heap *first, Binary_Heap *second);

void binheap_deinit(Binary_Heap *self);

#endif
