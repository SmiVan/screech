/*
 *  Name:       screech.h
 *  Purpose:    Test-driven development assistance tool for C.
 *  Updated:    2020-07-26
 *  Author:     SmiVan
 */

#ifndef SCREECH_H_
#define SCREECH_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TEST_RESULT_FORMAT "%d. %s - %s"
#define TEST_PASSED_MESSAGE "passed\n"
#define TEST_FAILED_MESSAGE "failed\n"

// The following defines a type for the test function pointer,
// that takes in nothing and returns int.
typedef int (*test_func)(void);

// The following is a struct with a test function and it's description.
typedef struct test {
    test_func function;
    const char* description;
} test;

/* Screech easy testing main function.
 *
 * Example usage:
 *
 * return screech_test("Testing Thrice", 3,
 *     (test){.function = example_test, .description = "Example Test 2.1"},
 *     (test){.function = example_test, .description = "Example Test 2.2"},
 *     (test){.function = example_test, .description = "Example Test 2.3"}
 * );
 *
 */
int screech_test(const char* description, int test_count, ...);

#ifdef __cplusplus
}
#endif

#endif
