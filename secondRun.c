/*
 ====================================================================================
 Name		: 	secondRun.c
 Description: 	This file holds methods relevant to the second transition run
 ====================================================================================
 */

#include <stdio.h>
#include "operationEncoder.h"
#include "consts.h"
#include "structs.h"
#include "functions.h"
#include "secondRun.h"
/*
 * Description: Executes the second transition
 * Input:		1. Input file handle
 * 				2. Name of input file
 * 				3. Code length in memory word
 * 				4. Data length in memory word
 */
void second_transition_execute(FILE* pFile, char* file_name_without_extension,
                               unsigned int previous_transition_ic, unsigned int previous_transition_dc) {
    compiler_output_files output_files;
	int line_number = 0;

    /* Creates transition first data */
	transition_data* transition = create_transition_data();

    if (transition == NULL) {
        return;
	}

    /* Create ob file */
	output_files.ob_file = create_output_file(file_name_without_extension, CODE_FILE_EXT);

	if (output_files.ob_file == NULL) {
		return;
	}

	output_files.entry_file = NULL;
	output_files.extern_file = NULL;

    /* Write first line to ob file */
    fprintf(output_files.ob_file,"%x %x\n",previous_transition_ic,previous_transition_dc);

    /* Initializes IC to zero*/
	transition->IC = 0;

	/* Reads all code lines */
	while (!feof(pFile) && !transition->is_runtimer_error) {
		char line[MAX_LINE_LENGTH];

		line_number++;

		if (fgets(line, MAX_LINE_LENGTH + 1, pFile)) {
			/* This isn't an empty line or a comment */
			if (!is_empty_or_comment(line)) {
				transition->current_line_information =
						create_line_info(file_name_without_extension, line_number, line);

				/* Process line */
				if (transition->current_line_information != NULL) {
					second_transition_process_line(transition, &output_files);

					free(transition->current_line_information);
				} else {
					transition->is_runtimer_error = true;
				}
			}
		}
	}/*end of while*/

	/* No error has occurred */
	if (!transition->is_runtimer_error && !transition->is_compiler_error) {
		/* Write data initialization section into ob file */
		write_data_to_output_file(output_files.ob_file);

		/* Close files */
		if (output_files.ob_file != NULL) {
			fclose(output_files.ob_file);
		}

		if (output_files.extern_file != NULL) {
			fclose(output_files.extern_file);
		}

		if (output_files.entry_file != NULL) {
			fclose(output_files.entry_file);
		}
	} else {
		/* Close and delete file */
		if (output_files.ob_file != NULL) {
			char* full_name = allocate_string(strlen(file_name_without_extension) + strlen(CODE_FILE_EXT));

			fclose(output_files.ob_file);
			if (full_name != NULL) {
				strcpy(full_name, file_name_without_extension);
				strcat(full_name, CODE_FILE_EXT);

				remove(full_name);

				free(full_name);
			} else {
				print_runtime_error("Couldn't delete compilation files");
			}

		}
    }

}
/*
 * Description: Processes a line in input file
 * Input:		1. Current transition data
 * 				2. Output files
 */
void second_transition_process_line(transition_data* transition, compiler_output_files* output_files) {
    char* type = NULL;
	int index;

	/* Skips label if exists */
    skip_label(transition->current_line_information);

    index = transition->current_line_information->current_index;

	/* Read line type */
	type = get_next_word(transition);

	/*if there is no type*/
    if (type == NULL) {
		print_compiler_error("Invalid line", transition->current_line_information);
		transition->is_compiler_error = true;
	}/*end of compiler error*/

	/* Line is data initialization - Ignores it */
	else if ((strcmp(type, DATA_OPERATION) == 0) || (strcmp(type, STRING_OPERATION) == 0)) {
		/* Ignore */
	}/*end of else if data*/

    /*Line is extern */
	else if (strcmp(type, EXTERN_OPERATION) == 0) {
        output_files->extern_file = create_output_file(transition->current_line_information->file_name, EXTERN_FILE_EXT);

		if (output_files->extern_file == NULL) {
			transition->is_runtimer_error  = true;
        }
    }/*end of else if extern*/

    /*Line is entry*/
    else if (strcmp(type, ENTRY_OPERATION) == 0) {
		/* Process entry */
		second_transition_process_entry(transition, output_files);
	}/*end of else if entry*/

	else  {
		/* Process operation */
		transition->current_line_information->current_index = index;
		second_transition_process_operation(transition, output_files);
	}/*end of else*/

    if (type != NULL) {
		free(type);
	}
}
