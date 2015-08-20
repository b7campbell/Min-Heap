#include "heap.h"

#define EMPTY (-1)

#define swap(x, y) do \
    { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
      memcpy(swap_temp, &y, sizeof(x)); \
      memcpy(&y, &x,        sizeof(x)); \
      memcpy(&x, swap_temp, sizeof(x)); \
    } while(0)

/*
 *  Setup Functions: Initialize and Clear
 *
 *  Allocate memory for heap
 *  Clear Allocated Memory to Null Equivalent
 *
 */
void initialize_heap(size_t m) {
    heapp.hep = malloc(sizeof(int) * m);
    heapp.size = 0;
    heapp.max_size = m;
    return;
}
void clear_heap(void) {
    int i;

    for (i = 0; i < heapp.max_size; ++i)
        heapp.hep[i] = EMPTY;
}

/*
 *  Function 0: Insert
 *
 *  Insert Value at Back
 *  Percolate Up to Restore Heap Property
 *
 */
void insert(int n) {
    int siz;
    int *hep;

    hep = heapp.hep;
    siz = heapp.size;

    if (siz >= heapp.max_size) {
        fprintf(stderr, "Warning: Heap full\n");
        return;
    }

    hep[siz] = n;
    per_up(siz);
    heapp.size += 1;
    fprintf(outfp, "insert %i\n", n);
}

/*
 *  Function 1: Deletemin
 *
 *  Overwrite Head with Last Element
 *  Empty Last Element
 *  Percolate Down to Restore Heap Property
 *
 */
#define HEAD 0
void deletemin(void) {
    int *hep;

    hep = heapp.hep;

    if (heapp.size == 0) {
        fprintf(outfp, "error_structure_is_empty\n");
        return;
    }
    fprintf(outfp, "deletemin %i\n", *hep);
    *hep = hep[--heapp.size];
    hep[heapp.size] = EMPTY;
    per_down(HEAD);
}

/*
 *  Helper Function: Percolate Down
 *
 *  Sink Larger Values Down the Heap
 */
void per_down(int i) {
    int len, lchild, rchild, index_of_min;
    int *hep;

    len = heapp.size;
    lchild = (i << 1) | 1;
    rchild = lchild + 1;
    index_of_min = i;
    hep = heapp.hep;

    /* Case 1: index i is already a leaf */
    if (lchild >= len)
        return;

    /* Case 2: minimum is found at left child */
    if (hep[index_of_min] > hep[lchild])
        index_of_min = lchild;

    /* Case 3: minimum is found at right child */
    if ((rchild < len) && hep[index_of_min] > hep[rchild])
        index_of_min = rchild;

    /* Case 4: unless element is min already
     *         swap, then continue percolating down
     */
    if (index_of_min != i) {
        swap(hep[i], hep[index_of_min]);
        per_down(index_of_min);
    }
}

/*
 *  Helper Function: Percolate Up
 *
 *  Float Smaller Values Up the Heap
 *
 */
void per_up(int i) {
    int p;
    int *hep;

    if (i == 0)
        return;

    p = i / 2;       /* integer division acts as a floor */
    if (!(i % 2))    /* if right child, adjust */
        p -= 1;
    hep = heapp.hep;

    if (hep[p] > hep[i]) {
        swap(hep[p], hep[i]);
        per_up(p);
    }
}

