#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define DEFAULT 10000   /* Sets Default Heap Size */
#define WRITE "w"
#define NULL_INT (-1)
/*
 *  Test Case Generator for Min-Heap Data Structure
 *
 *      Conventions:
 *
 *          0 [:num:]*  insert
 *          1           delete minimum value
 *
 *      Can Generate:
 *
 *          0           sorted series of inserts and deletes                    full
 *          1           randomly generated set of grouped instructions          partial
 *          2           randomly generated set of interleaved instructions
 *
 *      Will Make:
 *
 *          Input and Corresponding Output File for Testing
 */

void test_scenario_chooser(int);
void generate_initializer(int);
void generate_insert(int);
void generate_predictable_insert(int);
void generate_deletemin(int);
void generate_deletemin_untrackable(int);
void generate_interleaved(int);
int test_size(void);

FILE *infp, *outfp; /* for easy reference later */

int main(void)
{
    int siz;
    extern FILE *infp, *outfp;

    infp  = fopen("test.in", WRITE);
    outfp = fopen("test.out", WRITE);

    if (infp == NULL || outfp == NULL) {
        fprintf(stderr, "problem opening files for writing\n");
        exit(EXIT_FAILURE);
    }

    siz = test_size();
    generate_initializer(siz);
    test_scenario_chooser(siz);

    fclose(infp);
    fclose(outfp);
    exit(EXIT_SUCCESS);
}

/* Chooses which Test to Generate */
void test_scenario_chooser(int siz) {
    int c;

    printf("Choose a Test Case: | (0) Predictable, Ordered Test | (1) Grouped | (2) Interleaved\n");
    getchar();
    switch (c = getchar()) {
    case '0' :
        generate_predictable_insert(siz);
        generate_deletemin(siz);
        break;
    case '1' :
        generate_insert(siz);
        generate_deletemin(siz);
        break;
    case '2' :
        generate_interleaved(siz);
        break;
    default :
        fprintf(stderr, "Error: Unrecognized Test Case: %d\n", c);
        exit(1);
        break;
    }
}

/* Uses Default or User Provided Size */
int test_size(void) {
    int n;

    printf("Default Size of %i or Custom Size? Choose: d/c\n", DEFAULT);

    if (getchar() == 'c') {
        scanf("%i", &n);
        return n;
    } else
        return DEFAULT;
}

/* Generate a Number for Initialization */
void generate_initializer(int init_size) {
    extern FILE *infp, *outfp;

    fprintf(infp, "%d\n", init_size);
    fprintf(outfp, "read heap size %d\n", init_size);
}

/* Generate a Unique Set of Integers to be Inserted */
void generate_insert(int siz) {
    extern FILE *infp, *outfp;
    int i, n;

    srand((unsigned)time(NULL));

    for (i = 0; i < siz; ++i) {
        n = rand();
        fprintf(infp, "0 %i\n", n);
        fprintf(outfp, "insert %i\n", n);
    }
}

/* Generate a Number of Deletemin Instructions but no Check */
void generate_deletemin_untrackable(int siz) {
    extern FILE *infp, *outfp;
    int i;

    for (i = 0; i < siz; ++i) {
        fprintf(infp, "1\n");
        fprintf(outfp, "deletemin\n");
    }
}
/* Generate Inserts of 1 to 10000 for testing Deletemin */
void generate_predictable_insert(int siz) {
    extern FILE *infp, *outfp;
    int i;

    for (i = 0; i < siz; ++i) {
        fprintf(infp, "0 %i\n", i);
        fprintf(outfp, "insert %i\n", i);
    }
}

/* Generate a Number of Deletemin Instructions */
void generate_deletemin(int siz) {
    extern FILE *infp, *outfp;
    int i;

    for (i = 0; i < siz; ++i) {
        fprintf(infp, "1\n");
        fprintf(outfp, "deletemin %i\n", i);
    }
}

/* Generate a Number of Inserts and Deletemins that are Untrackable */
void generate_interleaved(int lim) {
    extern FILE *infp, *outfp;
    int i;

    srand((unsigned)time(NULL));

    lim *= 2;
    while (lim--) {

        i = rand();

        if (i % 2) {
            fprintf(infp, "1\n");
            fprintf(outfp, "deletemin\n");
        } else {
            fprintf(infp, "0 %i\n", i);
            fprintf(outfp, "insert %i\n", i);
        }
    }
}

