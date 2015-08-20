#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "heap.h"

#define MAX_MEM 10000
#define EMPTY (-1)

#define STDIN 0
#define READ "r"
#define WRITE "w"

void parse_input(char *);
void run_command(int *args[]);

void print_heap(void);
void verify_heap(void);

struct Heap heapp;
FILE *infp, *outfp;

/* opting for static alloc */
int main(int argc, char *argv[]) {

    extern FILE *infp, *outfp;
    char *line;
    size_t len;
    ssize_t nread;

    infp = outfp = NULL, line = NULL;
    nread = len = 0;

    if (argc >= 2 && argc <= 3) {
        if ( (infp = fopen(argv[1], READ)) == NULL) {
            fprintf(stderr, "Failed to open in file %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        if (argc == 3) {
            if ( (argv[1] == argv[2]) || (outfp = fopen(argv[2], WRITE)) == NULL ) {
                fprintf(stderr, "Failed to open out file %s\n", argv[2]);
                exit(EXIT_FAILURE);
            }
        } else {
            if ( (outfp = fopen("log.out", WRITE)) == NULL) {
                fprintf(stderr, "Cannot open a log file\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (argc == 1) {
        printf("Did not enter a filename. Enterting Interactive Mode...\n");
        printf("Commands: 0 Insert | 1 Delete Mininum Value | 2 Print Heap \n");
        if ( (infp = fdopen(STDIN, READ)) == NULL) {
            fprintf(stderr, "Cannot read from stdin\n");
            exit(EXIT_FAILURE);
        }
        if ( (outfp = fopen("log.out", WRITE)) == NULL) {
            fprintf(stderr, "Cannot open a log file\n");
            exit(EXIT_FAILURE);
        }
    }
    else {
        printf("Usage: [in file] [out file]\n");
        exit(EXIT_FAILURE);
    }

    initialize_heap(MAX_MEM);
    clear_heap();
    while ( (nread = getline(&line, &len, infp)) != EOF ) {
        parse_input(line);
    }

    verify_heap();
    free(heapp.hep);
    return 0;
}

#define OP_INSERT 0
#define OP_DELMIN 1
#define OP_PRINT  2

#define DECIMAL 10
#define MAX_NUM_OF_ARGS 2
#define NIL (-1)
void parse_input(char *s)
{
    int *args[MAX_NUM_OF_ARGS];
    size_t i;

    long arg;          /* arg from string */
    char *arg_end;

    if (*s == '\n')
        return;

    for (arg = strtol(s, &arg_end, DECIMAL), i = 0; s != arg_end;
                arg = strtol(s, &arg_end, DECIMAL), ++i) {
        s = arg_end;
        args[i] = malloc(sizeof(int));
        *(args[i]) = (int)arg;
    }

    run_command(args);

    while (i > 0)
        free(args[--i]);
}

void run_command(int *args[]) {
    switch (**args) {
        case OP_INSERT :
            insert(**++args);
            verify_heap();
            break;
        case OP_DELMIN :
            deletemin();
            verify_heap();
            break;
        case OP_PRINT :
            print_heap();
            break;
        default :
            fprintf(stderr, "WARNING: can't parse input: Operation %i not \
                                found \n EXITING IMMEDIATELY \n", **args);
            exit(EXIT_FAILURE);
    }
}

void print_heap(void) {
    int i;
    int *hep;

    hep = heapp.hep;

    if (heapp.size == 0) {
        printf("Empty\n");
        return;
    }

    printf("\n");
    for (i = 0; i < heapp.size; ++i) {
        printf("[%3i] %6d\t", i, hep[i]);
        if (!(i % 5))
            printf("\n");
    }
    printf("\n");
}

/* Verifies integrity of Min Heap Property */
void verify_heap(void) {
    int i, d;
    int *hep;

    hep = heapp.hep;

    for (i = 0; i < heapp.size; ++i) {
        d = i / 2;       /* integer division acts as floor */
        if (!(i % 2))    /* if right child, adjust */
            d -= 1;
        if (d < 0)       /* handle root case */
            d = 0;
        if (hep[d] > hep[i]) {
            printf("\nERROR: HEAP NOT VALID i: %d heap[i]: %d \n", d, hep[d]);
            printf("ERROR: HEAP NOT VALID i: %d heap[i]: %d \n", i, hep[i]);
            exit(EXIT_FAILURE);
        }
    }
}
