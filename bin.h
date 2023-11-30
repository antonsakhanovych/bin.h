#ifndef BINARY_HEAP
#define BINARY_HEAP

#include <stdlib.h>

typedef struct {
  void *_internal;
} Binary_Heap;

Binary_Heap *binheap_init();

Binary_Heap *binheap_construct(int *arr);

void binheap_insert(Binary_Heap *self);

int binheap_find_min(Binary_Heap *self);

int binheap_del_mind(Binary_Heap *self);

Binary_Heap *binheap_merge(Binary_Heap *first, Binary_Heap *second);

#endif
