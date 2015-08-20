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
    /* BCC: allocate array of integers */
    /* point back to HashItem */
};

extern struct Heap heapp;


void insert(int);
void deletemin(void);

void per_up(int);
void per_down(int);

void print_heap(void);


#endif /* HEAP_H */

