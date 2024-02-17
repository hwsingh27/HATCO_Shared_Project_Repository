/**
 * @file: main.c
 * @brief: the file contains a main function that calls a test_uint_binstr() function for unit testing
 *
 * @author: Harshwardhan Singh
 * @tool: Linux (Ubuntu OS) compiled using gcc
 */

#include <stdio.h>
#include <stdint.h>
#include "unit_test.h"

int main()
{
	// calling the unit test function
	test_uint_binstr(); 
	
	return 0;
}
