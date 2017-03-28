#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "structs.h"

/*
 * Description: Allocates a string
 * Input:		Number of tokens in string
 * Output:		Allocated string
 */
char* allocate_string(int string_length);

/*
 * Description: Allocates memory
 * Input:		Number of bytes to allocate
 * Output:		Pointer to number
 */
void* allocate_memory(int bytes);

/*
 * Description: Skips all the spaces until next word
 * Input:		Line information
 */
void skip_all_spaces(line_info* info);

/*
 * Description: Prints runtime error
 * Input:		Message
 */
void print_runtime_error(char* message);

/*
 * Description: Prints a compiler error to the user
 * Input:		1. Message
 * 				2. Current line
 */
void print_compiler_error(char* message, line_info* info);

#endif /* FUNCTIONS_H_ */
