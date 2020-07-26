/*
 *  Name:       screech.c
 *  Purpose:    Test-driven development assistance tool for C.
 *  Updated:    2020-07-26
 *  Author:     SmiVan
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "screech.h"

// The following is a list of tests to perform.
typedef struct test_suite {
    test* tests;
    const char* description;
    int count;
} test_suite;

typedef struct scoreboard {
    int testsPassed;
    int testsFailed;
} scoreboard;

void run_test(int (*test_function)(void), int test_number, const char* test_description, scoreboard* score) {

    if (test_function()) {
        // Test passed
        score->testsPassed += 1;
        fprintf(stderr, TEST_RESULT_FORMAT, test_number, test_description, TEST_PASSED_MESSAGE);
    } else {
        // Test failed
        score->testsFailed += 1;
        fprintf(stderr, TEST_RESULT_FORMAT, test_number, test_description, TEST_FAILED_MESSAGE);
    }
}

int run_suite(test_suite* suite) {
    fprintf(stderr, "\nTesting \"%s\"...\n", suite->description);

    // SETUP //
    scoreboard* score = (scoreboard*) malloc(sizeof(scoreboard));
    score->testsPassed = 0;
    score->testsFailed = 0;

    // TESTS  BEGIN //
    int test_counter = 0;
    test* current_test = suite->tests;

    while (test_counter < suite->count) {

        //increase test counter
        test_counter++;

        //run the test
        run_test(current_test->function, test_counter, current_test->description, score);

        //shift cursor to next test
        current_test = current_test + 1;
    }
    // TESTS   END  //

    printf("%i/%i tests passed.\n", score->testsPassed, score->testsPassed + score->testsFailed);

    if(score->testsFailed == 0) {
        printf("Working as intended.\n");
    }

    int failCount = score->testsFailed;

    free(score);

    return failCount;
}

// make test
test* make_test(test_func function, char* description) {
    test* this_test = (test*) malloc(sizeof(test));
    this_test->function = function;
    this_test->description = description;

    return this_test;
};

// free test
int free_test(test* test) {
    free(test);
    return 0;
};

// free test suite
int free_test_suite(test_suite* suite) {
    free(suite->tests);
    free(suite);
    return 0;
};

// make test suite, test using that suite and then free it
int screech_test(const char* description, int count, ...) {

    // MAKING TEST SUITE
    // loosely based on https://www.eskimo.com/~scs/cclass/int/sx11b.html

    test* test_list = (test*) calloc(count, sizeof(test));

    va_list argp;

    va_start(argp, count); // reads varargs *after* count argument

    // it's impossible to know how many varargs there are without count
    for(int i = 0; i < count; i++) {
        test_list[i] = va_arg(argp, test);
    }

    va_end(argp);

    test_suite* suite = (test_suite*) malloc(sizeof(test_suite));
    suite->tests = test_list;
    suite->description = description;
    suite->count = count;

    // TEST SUITE COMPLETE

    int fail_count = run_suite(suite);

    free_test_suite(suite);

    return !fail_count;
};
