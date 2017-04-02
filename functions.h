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
 * 			2. Current line
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
  * Description: Checks if the string is a valid label
  * Input:       String to check
  * Output:      True if the string is label, else false
  */

bool is_valid_label(char* str);
 /*
  * Description: Checks if we've reached end of line
  * Input:       Line information
  * Output:      True if we've reached end of lines, otherwise false
  */
bool is_end_of_line(line_info* info);

 /*
  * Description: Checks if operand is a register
  * Input:       Operand
  * Output:      True if register, otherwise false
  */
 bool is_register(char* operand);
 /*
  * Description: Checks if this is a valid operation line
  * Input:       Line information
  */
 bool is_valid_is_operation_line (line_info* info);

 /*
  * Description: Creates a line information structure
  * Input:       1. File name
  *              2. Line number
  *              3. Line content
  * Output:      Pointer to line information
  */
  line_info* create_line_info(char* file_name, int line_number, char* line_str);
 /*
  *  Description: Checks if this is an empty line or a comment
  *  Input:       The line to check
  *  Output:      Is this an empty line or a comment
  */
   bool is_empty_or_comment(char* line);
 /*
  *  Description: Creates a transition data structure
  *  Output:      Basic transition data
  */
    transition_data* create_transition_data();
 /*
  *  Description: Skips the label
  *  Input:       Line information
  */
    void skip_label(line_info* info);
#endif /* FUNCTIONS_H_ */
