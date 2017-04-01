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

/*
 * Description: Adds a symbol to the symbol table
 * Input:       1. Filename without extension like "ps"
 *              2. File extension  like "as"
 * Output: Pointer to the file after it has been edited
 */

FILE* create_output_file(char* file_name_without_extension, char* extension);

/*
 * Description: Check if it the end of data in the current line
 * Input: current line info
 * Output: True if there is not more data in the line and false else
 *                
 */
bool is_end_of_data_in_line(line_info* info);

/*
 * Description: Read the next word in line
 * Input:       Current transition data
 * Output:     Extracted word
 *     
 */

char* get_next_word(transition_data* transition);

 /*
  *   Description: Checks if the string is a valid label
  *   Input:       String to check
  *   Output:      True if the string is label, else false
  */

bool is_valid_label(char* str);
 /*
  *   Description: Checks if we've reached end of line
  *   Input:       Line information
  *   Output:      True if we've reached end of lines, otherwise false
  */
bool is_end_of_line(line_info* info);

#endif /* FUNCTIONS_H_ */
