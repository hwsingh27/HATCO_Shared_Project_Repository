/**
 * @file: unit_test.c
 * @brief: the file contains a function to test the implementation of unit_to_binstr() function
 * by covering various test cases
 *
 * @author: Harshwardhan Singh
 * @tool: Linux (Ubuntu OS) compiled using gcc
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "uint_to_binstr.h"
#include "unit_test.h"

#define BUFFER_SIZE (512)

/*
* @brief: the function is used test unit_to_binstr function implementation with various test cases
* 
* @param: void
*
* @return: void
*/
int test_uint_binstr(void)
{
    typedef struct
    {
        uint32_t num;
        uint8_t nbits;
        size_t size;
        int expected_res;
        const char *expected_str;
    }test_matrix_t;

    char str[BUFFER_SIZE];
    
    // array of structure with all the testcases (keep adding the cases here)
    test_matrix_t tests[]=
    {
        {18, 8, sizeof(str), 10, "0b00010010"},
        {65400, 16, sizeof(str), 18, "0b1111111101111000"},
        {310, 0, sizeof(str), -1, ""},
        {310, 4, sizeof(str), -1, ""},

        {15, 4, sizeof(str), 6, "0b1111"},
        {16, 4, sizeof(str), -1, ""},
        {16, 5, sizeof(str), 7, "0b10000"},

        {0, 1, sizeof(str), 3, "0b0"},
        {1, 1, sizeof(str), 3, "0b1"},
        {0, 2, sizeof(str), 4, "0b00"},
        {1, 2, sizeof(str), 4, "0b01"},
        {2, 2, sizeof(str), 4, "0b10"},
        {3, 2, sizeof(str), 4, "0b11"},

        {18, 8, 0, -1, ""},
        {18, 8, 1, -1, ""},
        {18, 8, 2, -1, ""},
        {18, 8, 3, -1, ""},
        {18, 8, 8, -1, ""},
        {18, 8, 11, 10, "0b00010010"},
        {10, 4, 5, -1, ""},
        {10, 4, 7, 6, "0b1010"},

        {0xFFFFFFFE, 32, sizeof(str), 34, "0b11111111111111111111111111111110"},
        {0xFFFFFFFF, 32, sizeof(str), 34, "0b11111111111111111111111111111111"},

        {16, 33, sizeof(str), -1, ""}
    };

    const int num_tests = sizeof(tests) / sizeof(test_matrix_t); // total number of test cases
    int tests_passed=0; // total number of tests passed
    char *test_result; // string to denote PASSED or FAILED
    int act_res; // to store the actual output

    for(int i=0; i<num_tests; i++)
    {
        act_res = uint_to_binstr(str, tests[i].size, tests[i].num, tests[i].nbits);
        if(act_res == tests[i].expected_res && strcmp(str,tests[i].expected_str) == 0)
        {
            test_result = "PASSED";
            printf("Case-%d: %s\n", i+1, test_result);
            tests_passed++;
        }
        else
        {
            test_result = "FAILED XXX";
            printf("Case-%d: %s\n", i+1, test_result);
        }
    }
    printf("\n%s: Total Cases Passed = %d/%d\n",__FUNCTION__, tests_passed, num_tests);
    
    return 0;
}
