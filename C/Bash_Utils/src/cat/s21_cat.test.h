#ifndef S21_CAT_TEST
#define S21_CAT_TEST

#include <stdio.h>

#include "../common/test.h"

int TEST_CASES_QTY = 25;
const char *test_cases[] = {
    "-b test.txt",      "-e test.txt",    "-n test.txt",    "-s test.txt",
    "-t test.txt",      "-v test.txt",    "-b -n test.txt", "-b -s test.txt",
    "-b -t test.txt",   "-b -v test.txt", "-e -n test.txt", "-e -s test.txt",
    "-e -t test.txt",   "-e -v test.txt", "-n -s test.txt", "-n -t test.txt",
    "-n -v test.txt",   "-s -t test.txt", "-s -v test.txt", "-t -v test.txt",
    "-be test.txt",     "-ben test.txt",  "-bens test.txt", "-benst test.txt",
    "-benstv test.txt",
};

#endif
