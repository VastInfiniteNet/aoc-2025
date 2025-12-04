#include <stdio.h>

typedef unsigned long long ull;

//#define DEBUG 

int main()
{
    FILE *f;
    int first = 10, second = 1;
    ull result = 0;

    f = fopen("day3/input.1", "r");

    if (f == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    } 
    
    int volt;
    while ((volt = fgetc(f)) != EOF) {
        if (volt == '\n') {
            #ifdef DEBUG
            printf("EOL: New total: '%c', '%c'\n", first, second);
            #endif
            result += first + second;
            first = second = 0;
            continue;
        }
        volt -= 48; // ascii to int
        if (second * 10 + volt > first + second) {
            first = second * 10;
            second = volt;
        } else if (volt > second) {
            second = volt;
        }

        #ifdef DEBUG
        printf("Pair: '%c', '%c' \n", first, second);
        #endif
    }
   
    fclose(f);
    printf("Result: %llu\n", result);
    return 0;
}