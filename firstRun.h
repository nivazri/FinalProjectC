#ifndef FIRSTRUN_H_
#define FIRSTRUN_H_

/*
 * Description: Executes the first transition of the assembly compiler
 * Input:		1. Input file
 * 			2. File name
 * Output:		Was transition successful
 */
bool first_transition_execute(FILE* pFile, char* file_name, unsigned int* IC, unsigned int* DC);

/*
 * Description: Processes a line according to its' type
 * Input:		1. Line information
 * 			2. Current IC address
 * 			3. Current DC value
 */
void first_transition_process_line(transition_data* transition);

/* Description: Processes an entry line in the first transition */

void first_transition_process_entry(transition_data* transition);

/* Description: Processes a data initialization line */

void first_transition_process_data(transition_data* transition, char* label, char* data_type, bool is_symbol);

/*
 * Description: Process the extern definition in first transition.
 * Adds it into the symbol table 
 */
 
 void first_transition_process_extern(transition_data* transition);

 /* Description: Updates symbol's address after first transition ends */
  void update_symbol_address(int ic_length);
 
 /*
  * Description: Updates data addresses according to code block size
  * Input:       Code block size
  */
   void update_data_address(int ic_length);

#endif /* FIRSTRUN_ */
