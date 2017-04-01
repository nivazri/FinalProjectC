#ifndef SECONDRUN_H_
#define SECONDRUN_H_

 /*
  * Description: Processes an entry line in the second transition 
  */
 void second_transition_process_entry(transition_data* transition, compiler_output_files* output_files);
 /*
  * Description: Processes a line in input file
  * Input:       1. Current transition data
  *              2. Output files
  */
 void second_transition_process_line(transition_data* transition, compiler_output_files* output_files);
  /*
   * Description: Writes all data definitions into an output file 
   */
 void write_data_to_output_file(FILE* output_file); 
  /*
   *   Description: Executes the second transition
   *   Input:       1. Input file handle
   *                2. Name of input file
   *                3. Code length in memory word
   *                4. Data length in memory word
   */
  void second_transition_execute(FILE* pFile, char* file_name_without_extension,
                                          unsigned int previous_transition_ic, unsigned int previous_transition_dc);
#endif /* SECONDRUN_H_ */
