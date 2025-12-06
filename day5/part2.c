#include <stdio.h>
#include <stdlib.h>

//#define DEBUG 
#define MAX_RANGES 256

int compareRanges(const void *a, const void *b) {
    size_t startA = ((size_t *)a)[0];
    size_t startB = ((size_t *)b)[0];
    return (startA > startB) - (startA < startB);
}

int main()
{
    FILE *f;
    size_t result, one, two;
    const char *INPUT_FILE = "day5/input.1"; // PLEASE CHGANGE EVERY DAY
    size_t ranges[MAX_RANGES][2];
    int range_count; 


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

    // sort to find range starts easier
    // guarentees when comparing ranges, right range starts will be compared to left range ends
    qsort(ranges, range_count, sizeof(size_t)*2, compareRanges); 
    printf("Sorted ranges (%d):\n", range_count);
    for (int i = 0; i < range_count; i++) { // print sorted ranges
        printf("%zu-%zu   ", ranges[i][0], ranges[i][1]);
    }
    printf("\n");

    // add first range -- no competitors 
    size_t merged_ranges[MAX_RANGES][2];
    merged_ranges[0][0] = ranges[0][0];
    merged_ranges[0][1] = ranges[0][1];
    int merged_count = 1;
    for (int i = 1; i < range_count; i++) {
        size_t *lastr = merged_ranges[merged_count - 1]; // right edge of ranges
        size_t currr[2] = {ranges[i][0], ranges[i][1]}; // starts in last range, or new range

        if (currr[0] <= lastr[1]) { // overlap, expand range if needed
            lastr[1] = (currr[1] > lastr[1]) ? currr[1] : lastr[1];
        } else { // no overlap, add new range
            merged_ranges[merged_count][0] = currr[0];
            merged_ranges[merged_count][1] = currr[1];
            merged_count++;
        }
    }

    result = 0;
    printf("\n\nMerged ranges (%d):\n", merged_count);
    for (int i = 0; i < merged_count; i++) { // print merged ranges
        printf("%zu-%zu   ", merged_ranges[i][0], merged_ranges[i][1]);
        result += (merged_ranges[i][1] - merged_ranges[i][0] + 1);
    }
    printf("\n");



    fclose(f);
    printf("Result: %lu\n", result);
    return 0;
}