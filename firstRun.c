/*
 ====================================================================================
 Name		: 	firstRun.c
 Description: 	This file holds methods relevant to the first run
 ====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "structs.h"
#include "functions.h"
#include "firstRun.h"
#include "operationEncoder.h"

/* Global variables */
ADDRESS_METHOD last_operand_method;
bool can_use_copy_previous = false;

/* Description: Executes the first run of the assembly compiler */
bool first_transition_execute(FILE* assembler_input_file, char* file_name_without_extension, unsigned int* IC, unsigned int* DC) {
	/* Creates the first run data */
	transition_data* transition = create_transition_data();
	int line_number = 0;
	bool success = true;

	if (transition == NULL) {
		return false;
	}

	/* Initialization of IC and DC*/
	transition->IC = 0;
	transition->DC = 0;

	/* Runs until end of file */
	while (!feof(assembler_input_file) && !transition->is_runtimer_error) {
		char line[MAX_LINE_LENGTH];

		line_number++;

		/* Reads each line in file  */
		if (fgets(line, MAX_LINE_LENGTH + 1, assembler_input_file)) {

			/* This isn't an empty line or a comment */
			if (!is_empty_or_comment(line)) {
				line_info* info = create_line_info(file_name_without_extension, line_number, line);

				/* Process the line */
				if (info != NULL) {
					transition->current_line_information = info;

					first_transition_process_line(transition);
					success &= !(transition->is_compiler_error);

					free(info);
				} else {
					transition->is_runtimer_error = true;
				}
			}
		}
	}

	/* No error has occurred during transition */
	if (!transition->is_compiler_error && !transition->is_runtimer_error) {
		/* Changes the data address according to the code length */
		update_data_address(transition->IC);
		update_symbol_address(transition->IC);

		*IC = transition->IC;
		*DC = transition->DC;
	}

	/* Release memory */
	if (transition->prev_operation_operand != NULL) {
		free(transition->prev_operation_operand);
	}

	free(transition);

	return success & !transition->is_runtimer_error;
}

/* Description: Processes a line according to its' type */
void first_transition_process_line(transition_data* transition) {
	char* label = NULL;
	char* line_type = NULL;
	bool is_symbol = false;
	char* partial_line;

	skip_all_spaces(transition->current_line_information);

	/*Find label */
	if ((partial_line = strchr(transition->current_line_information->line_str, LABEL_END_TOKEN)) != NULL) {

		/* Find label position */
		int start_label = transition->current_line_information->current_index;
		int label_length = partial_line - transition->current_line_information->line_str - start_label;
		label = allocate_string(label_length);
		strncpy(label, transition->current_line_information->line_str + start_label, label_length);
		label[label_length] = END_OF_STRING;

		/* The label is valid */
		if (is_valid_label(label)) {
			/* Turn symbol flag on */
			is_symbol = true;
			transition->current_line_information->current_index += label_length + 1;
		} else {
			print_compiler_error("Invalid label definition", transition->current_line_information);
			transition->is_compiler_error = true;
			return;
		}
	}

	/* Read line type */
	line_type = get_next_word(transition);

	/* Handle line type */
	if (line_type == NULL) {
		print_compiler_error("Invalid line", transition->current_line_information);
		transition->is_compiler_error = true;
	}
	/* Line is data: .string or .data */
	else if ((strcmp(line_type, DATA_OPERATION) == 0) || (strcmp(line_type, STRING_OPERATION) == 0)) {
		first_transition_process_data(transition, label, line_type, is_symbol);
	}
	/* Line is .extern */
	else if (strcmp(line_type, EXTERN_OPERATION) == 0) {
        first_transition_process_extern(transition);
	}
	/* Line is .entry */
	else if (strcmp(line_type, ENTRY_OPERATION) == 0) {
        first_transition_process_entry(transition);
	}
	/* Line is suspected as operation */
	else  {
		transition->current_line_information->current_index -= strlen(line_type);
		first_transition_process_operation(transition, label, is_symbol);
	}

	if (line_type != NULL) {
		free(line_type);
	}
}
