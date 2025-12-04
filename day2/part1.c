#include <stdio.h>
#include <time.h>
#include <math.h>

typedef unsigned long long ull;
typedef unsigned char uc;

ull repeated(ull n) {
    uc digits = log10((long double)n) + 1;
    #ifdef DEBUG
    printf(" Checking %llu with %d digits\n", n, digits);
    #endif
    if (digits % 2 == 1)
        return 0;

    ull divisor = pow(10, digits / 2);
    ull first = n / divisor;
    ull second = n % divisor;
    #ifdef DEBUG
    printf(" %llu  %llu vs %llu (%d)\n", divisor, first, second, first == second);
    #endif
    return (first == second) ? n : 0;
}

int main()
{
    FILE *f;
    clock_t start_time, end_time;
    ull start, end;
    ull result = 0;

    start_time = clock();
    f = fopen("day2/input.1", "r");

    if (f == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    } 


    while (fscanf(f, "%llu-%llu,", &start, &end) != EOF) {
        #ifdef DEBUG
        printf("Pair: '%llu'-'%llu'\n", start, end);
        #endif
        for (ull s = start; s <= end; s++) {
            #ifdef DEBUG
            printf(" Testing %llu\n", s);
            #endif
            result += repeated(s);
        }
        #ifdef DEBUG
        printf("%llu\n", result);
        #endif
    }
   
    fclose(f);
    printf("Result: %llu\n", result);
    end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);
    return 0;
}