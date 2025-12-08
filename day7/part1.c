#include <stdio.h>
#include <stdlib.h>

//#define DEBUG 
#define SPLITTER '^'
#define BEAM '|'
#define SPACE '.'

void progress(char *prev, char *curr, size_t *result) {
    printf("\nProgressing:%lu\n'%s'\n'%s'\n", *result, prev, curr);
    for (int i = 0; prev[i] != '\0'; i++) {
        printf("%d: %c", i, prev[i]);
        if (prev[i] != BEAM)
            continue;
        if (curr[i] == SPLITTER) { // split beam
            if (i > 0 && curr[i - 1] == SPACE) // split left
                curr[i - 1] = BEAM;
            if (curr[i + 1] == SPACE) // split right
                curr[i + 1] = BEAM;
            (*result)++;
            continue;
        }
        curr[i] = BEAM; // continue beam
    }
    printf("\nProgressed to:%lu\n'%s'\n'%s'\n\n", *result, prev, curr);
    for (int i = 0; prev[i] != '\0'; i++) {
        prev[i] = curr[i];
        curr[i] = 0;
    }
}

int main()
{
    FILE *f;
    size_t result;
    const char *INPUT_FILE = "day7/input.1"; // PLEASE CHGANGE EVERY DAY
    char prev[142] = {0}, curr[142] = {0}, c;
    int width, pos; 

    result = pos = 0;

    f = fopen(INPUT_FILE, "r");
    if (f == NULL) {
        printf("The file '%s' could not be opened.\n", INPUT_FILE);
        return 1;
    }

    while ((c = fgetc(f)) != '\n') { // get width of diagram
        printf("char: %c", c);
        if (c == 'S')
            c = BEAM;
        prev[width] = c;
        width++;
    }

    while ((c = fgetc(f)) != EOF) { // prase and process available ids
        printf("char: %c ", c);
        if (c == '\n') {  // if newline progress lines
            progress(prev, curr, &result);
            pos = 0;
            continue;
        }
            
        // if '.' incr horizontal position
        curr[pos++] = c;
    }

    fclose(f);
    printf("\nResult: %lu\n", result);
    return 0;
}