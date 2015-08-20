#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Heap {
    int size;
    int max_size;
    int *hep;
};

extern struct Heap heapp;
extern FILE* outfp;

void initialize_heap(size_t);
void clear_heap(void);

void insert(int);
void deletemin(void);

void per_up(int);
void per_down(int);

#endif /* HEAP_H */

