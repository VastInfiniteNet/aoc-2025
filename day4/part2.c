#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

//#define DEBUG 
#define MAX_LINE_LENGTH 139
#define MAX_LINES 138
#define MAX_ROLLS 4096
#define ROLL '@'
#define TILE '.'
#define OLD 0
#define TARGET 1
#define NEW 2

struct Tuple {
    int row;
    int col;
};

void count_line_rolls(char **floor, int row, int *found, struct Tuple **rolls) {
    #ifdef DEBUG
    printf("\n'%s'\n", floor[OLD]);
    printf("'%s'\n", floor[TARGET]);
    printf("'%s'\n", floor[NEW]);
    #endif
    // check if rolls in line 1
    for (int j = 0; j < MAX_LINE_LENGTH; j++) {
        #ifdef DEBUG
        printf("Checking pos %d: %c\n", j, floor[TARGET][j]);
        #endif
        if (floor[1][j] != ROLL)
            continue;

        // check for adjacent rolls
        int ar = 0;
        for (int k = -1; k < 2; k++) { // line above
            if (j + k > -1 && j + k < MAX_LINE_LENGTH && floor[OLD][j + k] == ROLL) {
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
        if (j < MAX_LINE_LENGTH - 1 && floor[TARGET][j + 1] == ROLL) { // right side
            ar++;
            #ifdef DEBUG
            printf("    Found roll right at pos %d\n", j + 1);
            #endif
        }

        for (int k = -1; k < 2; k++) { // line below
            if (j + k > -1 && j + k < MAX_LINE_LENGTH && floor[NEW][j + k] == ROLL) {
                ar++;
                #ifdef DEBUG
                printf("    Found roll below at pos %d\n", j + k);
                #endif
            }
        }

        if (ar < 4) {
            rolls[*found] = (struct Tuple *)malloc(sizeof(struct Tuple));
            *rolls[*found] = (struct Tuple){.row = row, .col = j};
            (*found)++;
            #ifdef DEBUG
            printf("        ACCESSIBLE ROLL at pos %d\n", j);
            #endif
        }
    }
}

int main()
{
    FILE *f;
    ull result = 0;
    char floor[MAX_LINES][MAX_LINE_LENGTH] = {0};
    char *window[3], empty[MAX_LINE_LENGTH] = {0}, *currPtr = *floor;
    char c;
    struct Tuple *rolls[MAX_LINE_LENGTH * MAX_LINES] = {0};

    f = fopen("day4/input.1", "r");
    if (f == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    }

    while ((c = fgetc(f)) != EOF) { // read in floor plan
        if (c == '\n') { // add char to last line
            currPtr++;
            continue;
        }
        *(currPtr++) = c;
    }

    while (1)
    {
        int round_result = 0;

         // read in line one
        window[OLD] = empty;
        window[TARGET] = floor[0];
        window[NEW] = empty;

        for (int line = 1; line < MAX_LINES + 1; line++) { // find valid rolls in the line
            window[NEW] = floor[line];
            count_line_rolls(window, line - 1, &round_result, rolls);

            window[OLD] = window[TARGET];
            window[TARGET] = window[NEW];
        }
        // update the floor with removed rolls
        for (int i = 0; i < round_result; i++) {
            floor[rolls[i]->row][rolls[i]->col] = TILE;
            free(rolls[i]);
        }
        #ifdef DEBUG
        printf("Found %d rolls this floor\n", round_result);
        #endif
        if (round_result == 0)
            break;
        result += round_result;
    }
   

    #ifdef DEBUG
    for (int row = 0; row < MAX_LINES; row++)
        printf("%d '%s', %p\n", row, floor[row], (void *)floor[row]);
    #endif

    fclose(f);
    printf("Result: %llu\n", result);
    return 0;
}