#include <stdio.h>
#include <stdlib.h>

//#define DEBUG 
#define SPLITTER '^'
#define BEAM '|'
#define SPACE '.'

void progress(char *prev, char *curr, int width, size_t *result) {
    printf("\nProgressing:%lu\n'%s'\n'%s'\n", *result, prev, curr);
    for (int i = 0; i < width; i++) {
        printf("%d: %c", i, prev[i]);
        if (prev[i] != BEAM)
            continue;
        if (curr[i] == SPLITTER) { // split beam
            if (i > 0 && curr[i - 1] == SPACE) { // split left
                curr[i - 1] = BEAM;
                (*result)++;
            }
            if (i + 1 < width && curr[i + 1] == SPACE) { // split right
                curr[i + 1] = BEAM;
                (*result)++;
            }
            continue;
        }
        curr[i] = BEAM; // continue beam
    }
    printf("\nProgressed to:%lu\n'%s'\n'%s'\n\n", *result, prev, curr);
    for (int i = 0; i < width; i++) {
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
    while (fgetc(f) != '\n') continue;

    while ((c = fgetc(f)) != EOF) { // trace beams
        printf("char: %c ", c);
        if (c == '\n') {  // if newline progress lines
            progress(prev, curr, width, &result);
            pos = 0;
            while (fgetc(f) != '\n') continue;
            continue;
        }
            
        curr[pos++] = c;
    }

    fclose(f);
    printf("\nResult: %lu\n", result);
    return 0;
}