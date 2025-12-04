#include <stdio.h>
#include <stdlib.h>

#define INPUT(x) STR(day1/input. ## x) 
#define STR(s) #s

int main()
{
    FILE *f;
    char dir;
    short ticks = 0;
    short dial = 50;
    unsigned short result = 0;

    f = fopen( INPUT(1), "r");

    if (f == NULL) {
        printf("The file could not be opened.\n");
        exit(1);
    } 

    while (fscanf(f, "%c%hu\n", &dir, &ticks) != EOF) {
        if (dir == 'R')
            dial += ticks;
        else if (dir == 'L')
            dial -= ticks;

        dial = dial % 100;
        if (dial == 0) {
            result++;
        }
    }
    fclose(f);
    printf("Result: %u\n", result);
    
    return 0;
}