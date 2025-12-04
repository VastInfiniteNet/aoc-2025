#include <stdio.h>

typedef unsigned long long ull;

//#define DEBUG 
#define BANK_SIZE 12

ull toNum(int arr[BANK_SIZE]) {
    ull total = 0;
    for (int i = 0; i < BANK_SIZE; i++)
        total = total*10 + arr[i];
    return total;
}

void add(int arr[BANK_SIZE], int val, int remove_index) {
    for (int i = remove_index; i < BANK_SIZE - 1; i++)
        arr[i] = arr[i + 1];
    arr[BANK_SIZE - 1] = val;
}

void printBank(int arr[BANK_SIZE]) {
    printf("Bank: ");
    for (int i = 0; i < BANK_SIZE; i++)
        printf("%d", arr[i]);
    printf("\n");
}

void try_candidate(int bank[BANK_SIZE], int candidate) {
    // 9 1 2 3, check: 2
    // 1. check if removing first and shifting + adding number better
        // 9 1 2 3 vs. /9/ 1 2 3 [2]
    // 2. check if removing second and shifting + adding number better
        // 9 1 2 3 vs 9 /1/ 2 3 [2]
    // 3. check if removing third and shofting + add number better
        // 9 1 2 3 vs 9 1 /2/ 3 [2] 
    // n. check if replacing last better
        // 9 1 2 3 vs 9 1 2 /3/ [2]

    for (int skip_index = 0; skip_index < BANK_SIZE; skip_index++) {
        int newi = 0;
        for (int position = 0; position < BANK_SIZE - 1; position++) { // compare
            if (position == skip_index)
                newi++;
            #ifdef DEBUG
            printf("Comp: '%d' (%d) vs '%d' (%d) \n", bank[position], position, bank[newi], newi);
            #endif
            if (bank[position] < bank[newi]) {
                add(bank, candidate, skip_index);
                #ifdef DEBUG
                printf("ADDED NEW VALUE %d at %i\n", candidate, skip_index);
                printBank(bank);
                #endif
                return;
            }
            if (bank[position] > bank[newi]) {
                position = BANK_SIZE;
                continue;
            }

            newi++;
        }
    }
    if (bank[BANK_SIZE - 1] < candidate) { // last 
        add(bank, candidate, BANK_SIZE - 1);
        #ifdef DEBUG
        printf("ADDED NEW VALUE %d at END: %i\n", candidate, BANK_SIZE - 1);
        printBank(bank);
        #endif
    }
}

int main()
{
    FILE *f;
    int bank[BANK_SIZE] = {0};
    int bank_len = 0;
    ull result = 0;

    f = fopen("day3/input.1", "r");

    if (f == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    } 
    
    for (; bank_len < BANK_SIZE; bank_len++)
        bank[bank_len] = fgetc(f) - 48;

    int volt;
    while ((volt = fgetc(f)) != EOF) {
        if (volt == '\n') {
            #ifdef DEBUG
            printf("Current bank value: '%llu'\n", toNum(bank));
            #endif

            result += toNum(bank); // add bank
            for (; bank_len > 0; bank_len--) // clear the bank
                bank[bank_len] = 0;
            continue;
        }
        volt -= 48; // ascii to int

        if (bank_len < BANK_SIZE)
            bank[bank_len++] = volt;
        if (bank_len < BANK_SIZE)
            continue;

        #ifdef DEBUG
        printBank(bank);
        printf("Candidate: '%d' \n", volt);
        #endif

        try_candidate(bank, volt);
    }
   
    fclose(f);
    printf("Result: %llu\n", result);
    return 0;
}