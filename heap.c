#include "heap.h"

/* BCC: Understand this better */
#define swap(x, y) do \
    { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
      memcpy(swap_temp, &y, sizeof(x)); \
      memcpy(&y, &x,        sizeof(x)); \
      memcpy(&x, swap_temp, sizeof(x)); \
    } while(0)

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
    printf("insert %i\n", n);
}

#define EMPTY (-1)
#define HEAD 0
void deletemin(void) {
    int *hep;

    hep = heapp.hep;

    if (heapp.size == 0) {
        printf("error_structure_is_empty\n");
        return;
    }
    /* BCC: potentially dangerous side effects here*/
    printf("deleteMin %i\n", *hep);
    *hep = hep[--heapp.size];
    hep[heapp.size] = EMPTY;
    per_down(HEAD);
}

void per_down(int i) {
    int len, lchild, rchild, index_of_min;
    int *hep;

    len = heapp.size;
    lchild = (i << 1) | 1;
    rchild = lchild + 1;
    index_of_min = i;
    hep = heapp.hep;

    /*printf("rchild: %i    | len: %i\n", rchild, len);*/

    /* Case 1: index i is already a leaf */
    if (lchild >= len) /* BCC: may be a bug?? */
        return;

    /* Case 2: minimum is found at left child */
    if (hep[index_of_min] > hep[lchild])
        index_of_min = lchild;

    /* Case 3: minimum is found at right child */
    if ((rchild < len) && hep[index_of_min] > hep[rchild])
        index_of_min = rchild;

    /* Case 4: continue percolating down */
    if (index_of_min != i) {
        swap(hep[i], hep[index_of_min]);
        per_down(index_of_min);
    }
}

void per_up(int i) {
    int p;
    int *hep;

    if (i == 0)
        return;

    p = (i - 1) / 2; /* integer division acts as a floor */
    hep = heapp.hep;

    if (hep[p] > hep[i]) {
        swap(hep[p], hep[i]);
        per_up(p);
    }
}

 /* insert, deletemin */

