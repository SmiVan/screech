/*
 *  Name:       screech.test.c
 *  Purpose:    Screech self-testing test.
 *  Updated:    2020-07-26
 *  Author:     SmiVan
 */

#include <stdlib.h>
#include <stdio.h>
#include "screech.h"

int example_test(void) {
    return 1 == 1;
}

int bad_test(void) {
    return 1 == 0;
}

int test_once(void) {
    return screech_test("Testing Once", 1,
        (test){.function = example_test, .description = "Example Test 1.1"}
    );
}

int test_thrice(void) {
    return screech_test("Testing Thrice", 3,
        (test){.function = example_test, .description = "Example Test 2.1"},
        (test){.function = example_test, .description = "Example Test 2.2"},
        (test){.function = example_test, .description = "Example Test 2.3"}
    );
}

int test_failed(void) {
    return !screech_test("Testing Failing", 3,
        (test){.function = example_test, .description = "Example Test 3.1"},
        (test){.function = example_test, .description = "Example Test 3.2"},
        (test){.function = bad_test, .description = "Bad Test"}
    );
}

int main(void) {
    screech_test("Screech Recursive Test", 3,
        (test){.function = test_once, .description = "Test Once"},
        (test){.function = test_thrice, .description = "Test Thrice"},
        (test){.function = test_failed, .description = "Test Failed"}
    );
    return 0;
}
