#include <stdio.h>
#include <stdlib.h>

//#define DEBUG 
#define MAX_RANGES 256

int main()
{
    FILE *f;
    size_t result, one, two, id;
    const char *INPUT_FILE = "day5/input.1"; // PLEASE CHGANGE EVERY DAY
    size_t ranges[MAX_RANGES][2];
    int range_count; 

    result = 0;

    f = fopen(INPUT_FILE, "r");
    if (f == NULL) {
        printf("The file '%s' could not be opened.\n", INPUT_FILE);
        return 1;
    }

    range_count = 0;
    while (fscanf(f, "%zu-%zu", &one, &two) != EOF) { // parse and store fresh ranges
        printf("Range: %zu - %zu\n", one, two);
        ranges[range_count][0] = one;
        ranges[range_count][1] = two;
        range_count++;

        fseek(f, 1, SEEK_CUR);
        if (fgetc(f) == '\n') // blank line between fresh ranges and available ids
            break;
        fseek(f, -1, SEEK_CUR); // not at blank yet
    }

    id = 0;
    while (fscanf(f, "%zu", &id) != EOF) { // prase and process available ids
        printf("ID: %zu\n", id);
        for (int i = 0; i < range_count; i++) {
            if (id >= ranges[i][0] && id <= ranges[i][1]) {
                printf("  ID %zu is in range %zu - %zu\n", id, ranges[i][0], ranges[i][1]);
                result++;
                break;
            }
        }
    }

    fclose(f);
    printf("Result: %lu\n", result);
    return 0;
}