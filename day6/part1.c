#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG 
#define MAX_PROBLEM_COUNT 1024
#define OPERAND_COUNT 4

int main()
{
    FILE *f;
    size_t result, num, problem_count;
    const char *INPUT_FILE = "day6/input.1"; // PLEASE CHGANGE EVERY DAY
    // THere is no operands with value of 0 in example or problem input
    size_t *curr_op;
    char nextc;

    problem_count = result = 0;

    f = fopen(INPUT_FILE, "r");
    if (f == NULL) {
        printf("The file '%s' could not be opened.\n", INPUT_FILE);
        return 1;
    }

    // get number of problems
    while (fscanf(f, "%zu", &num) != EOF) {
        problem_count++;
        if (fgetc(f) == '\n')
            break;
        if (fgetc(f) == '\n')
            break;
        fseek(f, -1, SEEK_CUR); // dont skip operand
    }
    fseek(f, 0, SEEK_SET);

    printf("%zu problems detected\n", problem_count);
    size_t *problems[OPERAND_COUNT] = {0};
    for (size_t i = 0; i < OPERAND_COUNT; i++) {
        problems[i] = malloc(sizeof(size_t) * problem_count); // no need to zero, overwriting all
        if (problems[i] == NULL) {
            printf("Issue trying to allocate memory for problems. Exiting");
            exit(EXIT_FAILURE);
        }
        printf("%zu: %p\n", i, problems[i]);
    }

    num = 0;
    curr_op = *problems; // point to first operand of first problem
    while (fscanf(f, "%zu", &num) != EOF) { // read and store the ith operand of all problems
        printf("Setting %p from %zu to %zu\n", curr_op, *curr_op, num);
        
        *curr_op = num;
        curr_op++;
        if (fgetc(f) != '\n') {
            if (fgetc(f) != '\n') {// start of next line, if operator stop looking for operands
                fseek(f, -1, SEEK_CUR); // dont skip first operator
                continue;
            }
        }
        // end of line
        curr_op += 2; // idk man, WHAT DID I DO WRONG
        nextc = fgetc(f);
        if ('*' <= nextc &&  nextc < '0') {// start of next line, if operator stop looking for operands
            fseek(f, -1, SEEK_CUR); // dont skip first operator
            break;
        }
        fseek(f, -1, SEEK_CUR); // not at operators yet
    }

    for (int i = 0; i < OPERAND_COUNT; i++) {
        printf("Array %d: [ ", i);
        for (size_t j = 0; j < problem_count; j++) {
            printf("%zu ", problems[i][j]);
        }
        printf("]\n");
    }

    num = 0;
    size_t problem_answer;
    while (fscanf(f, "%c", &nextc) != EOF) { // read and store the ith operand of all problems
        if (nextc == ' ')
            continue;
        printf("Applying op '%c' to problem %zu\n", nextc, num);
        problem_answer = 0;
        if (nextc == '*') {
            problem_answer = 1;
            for (int i = 0; i < OPERAND_COUNT; i++)
                problem_answer *= problems[i][num];
        } else {
            for (int i = 0; i < OPERAND_COUNT; i++)
                problem_answer += problems[i][num];
        }
        printf("Answer to problem %zu: %zu\n", num, problem_answer);
        num++;
        result += problem_answer;
    }

    // clean up
    fclose(f);
    for (size_t i = 0; i < OPERAND_COUNT; i++)
        free(problems[i]); // no need to zero, overwriting all

    printf("Result: %lu\n", result);
    return 0;
}