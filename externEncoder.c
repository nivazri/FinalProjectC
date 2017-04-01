/*
 ====================================================================================
 Name		: 	externEncoder.c
 Description: 	This file holds methods relevant to .extern line processing
 ====================================================================================
 */

#include "structs.h"
#include "symbolTable.h"
#include "functions.h"
/*
 * Description: Process the extern definition in first transition.
 * 				Adds it into the symbol table */
void first_transition_process_extern(transition_data* transition) {
	symbol_node_ptr p_symbol = NULL;

	char* extern_name = get_next_word(transition);

	/* If we have an extern*/
	if (extern_name) {
		symbol_node_ptr p_searched_symbol = search_symbol(extern_name);

		/* Extern does not exists in symbol table */
		if (!p_searched_symbol) {
			/* Create new symbol in table or die */
			p_symbol = create_symbol(extern_name, NO_ADDRESS, true, true);
			if (p_symbol) {
				add_symbol_to_list(p_symbol);

				/* Make sure that the line does not contain left overs */
				if (!is_end_of_data_in_line(transition->current_line_information)) {
					print_compiler_error("Invalid tokens after extern definition", transition->current_line_information);
					transition->is_compiler_error = true;
					return;
				}
			}
			/* Could not allocat memory, die*/
			else {
				transition->is_runtimer_error = true;
				free(extern_name);
				return;
			}
		}
		/* Extern is already in table */
		else {
			print_compiler_error("Each extern can be defined only once", transition->current_line_information);
			transition->is_compiler_error = true;
			return;
		}
	}
}

/*
 * Second Run method
 * Description: Creates the entry file if it doesn't exists*/
void create_extern_output_file_if_needed(compiler_output_files* output_files, char* file_name_without_extension) {
	if (output_files->extern_file == NULL) {
		output_files->extern_file = create_output_file(file_name_without_extension, EXTERN_FILE_EXT);
	}
}
