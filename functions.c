/*
 ====================================================================================
 Name		: 	function.c
 Description: 	This file holds function methods used to process assembly line
 ====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "structs.h"

void* allocate_memory(int bytes);

/*
 * Description: Allocates a string
 * Input:		Number of tokens in string
 * Output:		Allocated string
 */
char* allocate_string(int string_length) {
	return (char*)allocate_memory(sizeof(char) * (string_length + 1));
}

/*
 * Description: Allocates memory
 * Input:		Number of bytes to allocate
 * Output:		Pointer to number
 */
void* allocate_memory(int bytes) {
	void* result = (void*)malloc(bytes);

	if (result == NULL) {
		print_runtime_error("Could not allocate memory. Exit program");
	}

	return result;
}

/*
 * Description: Prints runtime error
 * Input:		Message
 */
void print_runtime_error(char* message) {
	fprintf(stderr, "Error: %s \n", message);
}

/*
 * Description: Prints a compiler error to the user
 * Input:		1. Message
 * 				2. Current line
 */
void print_compiler_error(char* message, line_info* info) {
	fprintf(stderr, "Error: %s, File %s Line %d \n", message, info->file_name, info->line_number);
}

/*
 * Description: Creates a transition data structure
 * Output:		Basic transition data
 */
transition_data* create_transition_data() {
	transition_data* transition = (transition_data*)allocate_memory(sizeof(transition_data));

	/* Initialize */
	if (transition != NULL) {
		transition->IC = 0;
		transition->DC = 0;
		transition->prev_operation_operand = NULL;
		transition->is_compiler_error = false;
		transition->is_runtimer_error = false;
		transition->current_line_information = NULL;
	}

	return transition;
}

/*
 * Description: Checks if this is an empty line or a comment
 * Input:		The line to check
 * Output:		Is this an empty line or a comment
 */
bool is_empty_or_comment(char* line) {
	int i;
	int length = strlen(line);

	/* Check's there is a token that isn't a space */
	for (i = 0; i < length; i++) {
		if (!isspace(line[i])) {
			return line[i] == COMMENT;
		}
	}

	return true;
}

/*
 * Description: Creates a line information structure
 * Input:		1. File name
 * 				2. Line number
 * 				3. Line content
 * Output:		Pointer to line information
 */
line_info* create_line_info(char* file_name, int line_number, char* line_str) {
	line_info* info = (line_info*)allocate_memory(sizeof(line_info));

	/* Initialize */
	if (info != NULL) {
		info->current_index = 0;
		info->file_name = file_name;
		info->line_number = line_number;
		info->line_str = line_str;
		info->line_length = strlen(line_str);
	}

	return info;
}

void skip_all_spaces(line_info* info) {
	int index = info->current_index;

	/* Scans all spaces */
	while ((index < info->line_length) && isspace(info->line_str[index])) {
		index++;
	}

	info->current_index = index;
}

/*
 * Description: Checks if the string is a valid label
 * Input:		String to check
 * Output:		True if label, otherwise false
 */
bool is_valid_label(char* str) {
	int i;
	int len = strlen(str);

	/*
	 * Make sure that :
	 * 	1) string start's with a letter
	 * 	2) string is shorter then maximum length (excluding the end of label token)
	 */
	if (!isalpha(str[0]) || len > LABEL_MAX_LENGTH) {
		return false;
	}
}

/*
 * Description: Read next word from line
 * Input:		Current transition data
 * Output:		Extracted word
 */
char* get_next_word(transition_data* transition)
{
	char* word;
	int i, word_end_index, word_start_index, word_length;

	skip_all_spaces(transition->current_line_information);

	word_end_index  = word_start_index = i = transition->current_line_information->current_index;

	/* Find word position */
	for (;i < transition->current_line_information->line_length; i++) {
		if (!isspace(transition->current_line_information->line_str[i])) {
			word_end_index = i;
		} else {
			break;
		}
	}

	word_length = word_end_index - word_start_index + 1;

	word = allocate_string(word_length);

	if (word == NULL) {
		transition->is_runtimer_error = true;
	} else {
		/* Copy word */
		strncpy(word, transition->current_line_information->line_str + word_start_index, word_length);
		(word)[word_length] = END_OF_STRING;

		transition->current_line_information->current_index = word_end_index + 1;
	}

	return word;
}

/*
 * Description: Checks if there are tokens that aren't spaces after current index
 * Input:		Line information
 * Output:		True if found non-space token, otherwise false
 */
bool is_end_of_data_in_line(line_info* info) {
	bool is_end = true;
	int i;

	/* Searches non-space token */
	for (i = info->current_index; i < info->line_length; i++) {
		if (!isspace(info->line_str[i])) {
			is_end = false;
			break;
		}
	}

	return is_end;
}

/*
 * Description: Checks if we've reached end of line
 * Input:		Line information
 * Output:		True if we've reached end of lines, otherwise false
 */
bool is_end_of_line(line_info* info) {
	return info->current_index == info->line_length;
}

/*
 * Description: Checks if this is a valid operation line
 * Input:		1. Line information
 */
bool is_valid_is_operation_line (line_info* info) {

	return info->line_length < OPERATION_LINE_MAX_LENGTH;
}

/*
 * Description: Checks if operand is a register
 * Input:		1. Operand
 * Output:		True if register, otherwise false
 */
bool is_register(char* operand) {
	int digit;
	int length = strlen(operand);

	if ((length != 2) || (operand[0] != REGISTER_FIRST_TOKEN) || (!isdigit(operand[1]))) {
		return false;
	}

	digit = atoi(operand + 1);

	return (digit < REGISTERS_COUNT) && (digit >= 0);
}


/*
 * Description: Creates an output file from given file name
 * Input:		1. File name without extension
 * 				2. File extension
 * Output:		Reference to created file
 */
FILE* create_output_file(char* file_name_without_extension, char* extension) {
	FILE* p_output_file = NULL;
	int file_name_length = strlen(file_name_without_extension) + strlen(extension);

	char* file_name = allocate_string(file_name_length);

	if (file_name != NULL) {
		/* Creates code file output name */
		strcpy(file_name, file_name_without_extension);
		strcat(file_name, extension);
		file_name[file_name_length] = END_OF_STRING;

		p_output_file = fopen(file_name, WRITE_MODE);

		free(file_name);

		if (!p_output_file) {
			print_runtime_error("Cannot create output file");
		}
	}

	return p_output_file;
}

/*
 * Description: Skips the label
 * Input:		Line information
 */
void skip_label(line_info* info) {
	/* Search the label end token */
	char* partial_line = strchr(info->line_str, LABEL_END_TOKEN);

	if (partial_line != NULL) {
		info->current_index = partial_line - info->line_str + 1;
	}
}
