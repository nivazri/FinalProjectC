#include "structs.h"

/*
 * Description: Processes an entry line in the first transition
 * Input:		1. Line information
 */
void first_transition_process_entry(transition_data* transition) {
	char* entry_name = get_next_word(transition);

	/* If entry was found*/
	if (entry_name != NULL) {
		/* Is entry valid? */
		if (is_valid_label(entry_name)) {
			/* Are we at line end?, if so, its an error, and if not, we are done */
			if (!is_end_of_data_in_line(transition->current_line_information)) {
				print_compiler_error("Invalid tokens in end of entry definition", transition->current_line_information);
				transition->is_compiler_error = true;
			}
		}
		/* Throw compiler error */
		else {
			print_compiler_error("Entry name must be a valid label", transition->current_line_information);
			transition->is_compiler_error = true;
		}
	}
	/* Throw runtime error */
	else if (!transition->is_runtimer_error) {
		print_compiler_error("Missing entry name", transition->current_line_information);
		transition->is_compiler_error = true;
	}
}

/*
 * Second Run method
 * Description: Processes an entry line in the second transition
 * Input:		1. Line information
 * 				2. Output files
 */
void second_transition_process_entry(transition_data* transition, compiler_output_files* output_files) {
	char* entry_name = get_next_word(transition);

	/* Search for the entry inside the symbol table */
	symbol_node_ptr p_symbol = search_symbol(entry_name);

	/* Entry doesn't exists in symbol table*/
	if (p_symbol == NULL) {
		print_compiler_error("Invalid entry definition. Label doesn't exists.", transition->current_line_information);
		transition->is_compiler_error = true;
	} else {
		create_entry_output_file_if_needed(output_files, transition->current_line_information->file_name);

		if (output_files->entry_file == NULL) {
			transition->is_runtimer_error = true;
			return;
		}

		fprintf(output_files->entry_file,"%s %x",entry_name,p_symbol->current_symbol.address);
	}
}

/*
 * Second Run method
 * Description: Creates the entry file if it doesn't exists
 * Input:		1. Output files
 * 				2. File name without extension
 */
void create_entry_output_file_if_needed(compiler_output_files* output_files, char* file_name_without_extension) {
	if (output_files->entry_file == NULL) {
		output_files->entry_file = create_output_file(file_name_without_extension, ENTRY_FILE_EXT);
	}
}
