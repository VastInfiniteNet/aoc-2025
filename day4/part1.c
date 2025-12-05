#include <stdio.h>

typedef unsigned long long ull;

//#define DEBUG 
#define MAX_LINE_LENGTH 139
#define ROLL '@'
#define OLD 0
#define TARGET 1
#define NEW 2


void count_line_rolls(int max_len, char floor[3][MAX_LINE_LENGTH], ull *result) {
    #ifdef DEBUG
    printf("'%s'\n", floor[OLD]);
    printf("'%s'\n", floor[TARGET]);
    printf("'%s'\n", floor[NEW]);
    #endif

    // check if rolls in line 1
    for (int j = 0; j < max_len; j++) {
        #ifdef DEBUG
        printf("Checking pos %d: %c\n", j, floor[TARGET][j]);
        #endif
        if (floor[1][j] != ROLL)
            continue;

        // check for adjacent rolls
        int ar = 0;
        for (int k = -1; k < 2; k++) { // line above
            if (j + k > -1 && j + k < max_len && floor[OLD][j + k] == ROLL) {
                ar++;
                #ifdef DEBUG
                printf("    Found roll above at pos %d\n", j + k);
                #endif
            }
        }
        
        if (j > 0 && floor[TARGET][j - 1] == ROLL) { // left side
            ar++;
            #ifdef DEBUG
            printf("    Found roll left at pos %d\n", j - 1);
            #endif
        }
        if (j < max_len - 1 && floor[TARGET][j + 1] == ROLL) { // right side
            ar++;
            #ifdef DEBUG
            printf("    Found roll right at pos %d\n", j + 1);
            #endif
        }

        for (int k = -1; k < 2; k++) { // line below
            if (j + k > -1 && j + k < max_len && floor[NEW][j + k] == ROLL) {
                ar++;
                #ifdef DEBUG
                printf("    Found roll below at pos %d\n", j + k);
                #endif
            }
        }

        if (ar < 4) {
            (*result)++;
            #ifdef DEBUG
            printf("        ACCESSIBLE ROLL at pos %d\n", j);
            #endif
        }
    }
    for (int j = 0; j < max_len; j++) { // shift lines up
        floor[OLD][j] = floor[TARGET][j];
        floor[TARGET][j] = floor[NEW][j];
        floor[NEW][j] = 0;
    }
    #ifdef DEBUG
    printf("Total rolls: %llu\n\n", *result);
    #endif
}

int main()
{
    FILE *f;
    ull result = 0;
    char floor[3][MAX_LINE_LENGTH] = {0}, c;
    int max_len, i = 0;

    f = fopen("day4/input.1", "r");
    if (f == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    }

    // read in line one
    while ((c = fgetc(f)) != '\n')
        floor[TARGET][i++] = c;
    max_len = i;
    i = 0;

    while ((c = fgetc(f)) != EOF) {
        if (c != '\n') {
            // add char to last line
            floor[NEW][i++] = c;
            continue;
        }
            
        count_line_rolls(max_len, floor, &result);
        i = 0;
    }
    count_line_rolls(max_len, floor, &result);
    count_line_rolls(max_len, floor, &result);

    #ifdef DEBUG
    printf("'%s'\n", floor[0]);
    printf("'%s'\n", floor[1]);
    printf("'%s'\n", floor[2]);
    #endif

    fclose(f);
    printf("Result: %llu\n", result);
    return 0;
}