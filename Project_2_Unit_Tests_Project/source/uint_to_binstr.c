/**
 * @file: uint_to_binstr.c
 * @brief: the file contains a function to represent the number in binary format by
 * returning a string with its binary representation
 *
 * @author: Harshwardhan Singh
 * @tool: Linux (Ubuntu OS) compiled using gcc
 */

#include <stdio.h>
#include <stdint.h>

#define ERROR (-1)

/*
* @brief: the function is used represent uint32_t number in binary format by returning a string with binary representation
* 
* @param: pointer to a char array, char array of size size_str (in bytes), num is the value to be converted and nbits is the number of bits in the input
*
* @return: if the operation is successful, the function returns the number of characters written to str, not including the terminal \0.
*	   In case of an error, the function returns a negative value, and str is set to the empty string
*/
int uint_to_binstr(char *str, size_t size_str, uint32_t num, uint8_t nbits)
{
	// return -1 if the string is NULL
	if(str == NULL)
	{
		return ERROR;
	}
	
	/*
	* return -1 (error) if:
	* number if greater than the number of bits needs to be printed
	* number of bits is greater than the size of a string
	* number of bits is zero
	* number of bits is greater than 32
	*/
	if((int)num >= (1 << nbits) || (size_t)(nbits + 2) > size_str || nbits == 0 || nbits > 32)
	{
		str[0] = '\0';
		return ERROR;
	}
	
	char *s = str;
	*s++ = '0';
	*s++ = 'b'; // use 'b' to denote the binary representation of a number
	
	for(uint32_t mask = 1 << (nbits - 1); mask > 0; mask >>= 1)
	{
		if(num & mask)
		{
			*s++ = '1';
		}
		else
		{
			*s++ = '0';
		}
	}
	
	*s = '\0'; // putting a null terminated character to end the string
	
	return (nbits + 2);
}
