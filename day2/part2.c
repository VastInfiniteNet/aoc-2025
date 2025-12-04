#include <stdio.h>
#include <time.h>
#include <math.h>

typedef unsigned long long ull;
typedef unsigned char uc;

#define DEBUG // Uncomment to enable debug prints

int checkFakeBinary(ull n) {
    while (n > 0) {
        ull digit = n % 10;
        if (digit != 0 && digit != 1)
            return 0;
        n /= 10;
    }
    return 1;
}

int allOnes(ull n) {
    while (n > 0) {
        ull digit = n % 10;
        if (digit != 1)
            return 0;
        n /= 10;
    }
    return 1;
}

ull repeated(ull n) {
    uc digits = log10((long double)n) + 1;
    ull mod, div;
    #ifdef DEBUG
    //printf(" Checking %llu with %d digits\n", n, digits);
    #endif

    ull divisor = pow(10, ceil(digits / 2));
    ull max_candidate = n % divisor;

    for (ull candidate = 2; candidate <= max_candidate; candidate++) {
        mod = n % candidate;
        if (mod != 0)
            continue;

        div = n / candidate;
        #ifdef DEBUG
        printf(" Candidate:%llu, mod:%llu, div:%llu\n", candidate, mod, div);
        #endif
        if (checkFakeBinary(div))
            return n;
    }

    #ifdef DEBUG
    printf(" Max Candidate:%llu\n", max_candidate);
    #endif
    return 0;
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