/*
 ====================================================================================
 Name		: 	main.c
 Author's	: 	Niv Azriel, Or Friedman
 Description: 	This program will compile an assembler code file.
 	 	 	 	In case of errors in file it will print them out.
 Input		:	Arguments as file name without extension to be compiled
 Output		:	If we've found syntax errors - prints them.
 	 	 	 	Else for each valid file we create
 	 	 	 	 1) ob  - decoded operations in base 4 and memory address
 	 	 	 	 2) ent - memory address of labels
 	 	 	 	 3) ext - memory address of each extern variable used in ob file
 ====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structs.h"
#include "functions.h"
#include "consts.h"
#include "firstRun.h"
#include "secondRun.h"
#include "operationEncoder.h"
#include "dataEncoder.h"
#include "symbolTable.h"
/*
 * Description: Cleaning up memory between files, global call for all cleanups
 */
void file_compilation_memory_clean() {
	free_data_node_list();
	free_symbol_list();
	return;
}

int main(int argc, char* argv[]) {
	int i;
	char* curr_file;
	FILE* p_file;

	/* Check if no arg's provided */
	if (argc == 1) {
		print_runtime_error("Expected an argument");
		exit(0);
	}

	/* Initialize operation list */
	if (!init_operation_list()) {
		free_operation_list();
		print_runtime_error("Could not initializes operation definitions");
		exit(0);
	}

	/* Run the Compiler for each file given as arg */
	for (i=1; i < argc; i++) {
		unsigned int ic;
		unsigned int dc;

		/* Create full file path */
		curr_file = allocate_string(strlen(argv[i])+strlen(FILE_EXT));
		strcpy (curr_file, argv[i]);
		strcat (curr_file, FILE_EXT);

		/* Open the file or die*/
		p_file = fopen(curr_file, READ_ONLY_MODE);

		if (p_file == NULL) {
			print_runtime_error("Could not open a source file");
		}
		else {
            	/* Check if we had errors, if we didn't, move on to the next run */
			bool should_continue = first_transition_execute(p_file, curr_file, &ic, &dc);

			if (should_continue) {
				rewind(p_file);
				second_transition_execute(p_file, argv[i], ic, dc);
			}

			file_compilation_memory_clean();
			fclose(p_file);
		}
		free(curr_file);
    }
    free_operation_list();

    exit(0);
}
