#ifndef S21_GREP_TEST
#define S21_GREP_TEST

#include "../common/test.h"

int TEST_CASES_QTY = 61;
const char *test_cases[] = {
    "utility test_files/test_1.txt",
    "utility test_files/test_1.txt",
    "utility test_files/test_1.txt -c",
    "utility test_files/test_1.txt -n",
    "utility test_files/test_1.txt -l",
    "utility test_files/test_1.txt -h",
    "utility test_files/test_1.txt non_exist_file -s",
    "UTILITY test_files/test_1.txt -i",
    "utility test_files/test_1.txt -ov",
    "utility test_files/test_1.txt -on",
    "utility test_files/test_1.txt -oc",
    "utility test_files/test_1.txt -vo",
    "utility test_files/test_1.txt -vn",
    "utility test_files/test_1.txt -vn",
    "utility test_files/test_1.txt -cl",
    "utility test_files/test_1.txt -f test_files/patterns_1.txt",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -v",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -vc",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -vn",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -vl",
    "-e first test_files/test_2.txt no_file -f test_files/patterns_1.txt -vs",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -vh",
    "-e first test_files/test_2.txt -f test_files/patterns_1.txt -iv",
    "-e first test_files/test_2.txt -f test_files/patterns_2.txt",
    "-e first test_files/test_2.txt -f test_files/empty.txt",
    "utility test_files/test_1.txt -f test_files/patterns_1.txt -f "
    "test_files/empty.txt -f test_files/patterns_2.txt",
    "utility test_files/test_1.txt test_files/test_2.txt",
    "utility test_files/test_1.txt test_files/test_2.txt non_exist_file",
    "utility test_files/test_1.txt test_files/test_2.txt non_exist_file -s",
    "utility test_files/test_1.txt test_files/test_2.txt non_exist_file -n",
    "-e utility test_files/test_1.txt",
    "-e utility test_files/test_2.txt",
    "-e utility test_files/test_1.txt test_files/test_2.txt",
    "-e utility -e second test_files/test_1.txt test_files/test_2.txt",
    "-e utility -e matches test_files/test_1.txt "
    "test_files/test_2.txt -f test_files/patterns_1.txt",
    "-e utility -e matches test_files/test_1.txt test_files/test_2.txt -f "
    "test_files/patterns_2.txt",
    "-e utility -e matches test_files/test_1.txt test_files/test_2.txt -f "
    "test_files/patterns_2.txt -iv",
    "test_files/test_1.txt test_files/test_2.txt -f "
    "test_files/patterns_1.txt -v",
    "-e utility -e matches test_files/test_1.txt test_files/test_2.txt -f "
    "test_files/patterns_2.txt -cl",
    "-e utility -e matches test_files/test_1.txt test_files/test_2.txt -f "
    "non_exist_file",
    "-e utility -e matches test_files/test_1.txt test_files/test_2.txt -f "
    "test_files/empty.txt",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -v",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -v",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -o",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -c",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -s",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -h",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -n",
    "-e utility -e CaT -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -i",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -l",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -lc",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -oc",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -ocv",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -cvh",
    "-e utility -e first -e file -e line test_files/test_1.txt "
    "test_files/test_2.txt -ch",
    "-e utility -e first -e FILE -e line test_files/test_1.txt "
    "test_files/test_2.txt -iv",
    "-e utility -e grep -e first -e FILE -e line test_files/test_1.txt "
    "test_files/test_2.txt -in",
    "-e utility -e grep -e first -e FILE -e file -e line "
    "test_files/test_1.txt "
    "test_files/test_2.txt -in",
    "-e utility -e grep -e first -e FILE -e file -e line "
    "test_files/test_1.txt "
    "test_files/test_2.txt -inhs",
};

#endif