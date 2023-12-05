#include "./bin.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void _swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void _upheap(Binary_Heap *self, size_t index) {
  size_t par_index = (index - 1) / 2;
  while (index > 0 && self->nodes[index] < self->nodes[par_index]) {
    _swap(self->nodes + index, self->nodes + par_index);
    index = par_index;
    par_index = (index - 1) / 2;
  }
}

void _downheap(Binary_Heap *self, size_t index) {
  int temp = self->nodes[index];
  int next_ind = index * 2 + 1;
  while (next_ind < self->size) {
    if (next_ind + 1 < self->size &&
        self->nodes[next_ind] > self->nodes[next_ind + 1]) {
      next_ind += 1;
    }
    if (temp < (self->nodes[next_ind])) {
      break;
    }
    self->nodes[index] = self->nodes[next_ind];
    index = next_ind;
    next_ind = index * 2 + 1;
  }
  self->nodes[index] = temp;
}

// [ 0 1 2 3 4 5 6 7 8 9 ]
// parent = (ind - 1)/2
// child = ind * 2 (+ 1/ + 2)

Binary_Heap *binheap_init() {
  Binary_Heap *self = malloc(sizeof(Binary_Heap));
  *self = (Binary_Heap){.nodes = NULL, .size = 0, .cap = INITIAL_CAPACITY};
  self->nodes = calloc(self->cap, sizeof(int));
  return self;
}

void binheap_print(Binary_Heap *self) {
  printf("[ ");
  for (size_t i = 0; i < self->size; i++) {
    printf("%d ", self->nodes[i]);
  }
  printf("]\n");
}

Binary_Heap *_binheap_construct(int *arr, size_t size, size_t cap) {
  Binary_Heap *self = malloc(sizeof(Binary_Heap));
  *self = (Binary_Heap){.nodes = arr, .size = size, .cap = cap};
  ssize_t index = (size - 2) / 2;
  while (index >= 0) {
    _downheap(self, index);
    index--;
  }
  return self;
}

Binary_Heap *binheap_construct(int *arr, size_t size) {
  return _binheap_construct(arr, size, size * 2);
}

void binheap_insert(Binary_Heap *self, int val) {
  if (self->size == self->cap) {
    self->cap *= 2;
    self->nodes = realloc(self->nodes, self->cap * sizeof(int));
  }
  self->nodes[self->size] = val;
  _upheap(self, self->size);
  self->size++;
}

int binheap_find_min(Binary_Heap *self) { return self->nodes[self->size - 1]; }

int binheap_del_min(Binary_Heap *self) {
  int res = self->nodes[0];
  _swap(self->nodes, self->nodes + (self->size - 1));
  if (self->size == 0) {
    return 0;
  }
  self->size--;
  _downheap(self, 0);
  return res;
}

Binary_Heap *binheap_merge(Binary_Heap *first, Binary_Heap *second) {
  size_t size = first->size + second->size;
  int *nodes = calloc(size * 2, sizeof(int));
  memcpy(nodes, first->nodes, sizeof(int) * first->size);
  memcpy(nodes + first->size, second->nodes, sizeof(int) * second->size);
  return binheap_construct(nodes, size);
}

void binheap_deinit(Binary_Heap *self) {
  free(self->nodes);
  free(self);
  self = NULL;
}
