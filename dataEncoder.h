#ifndef DATA_H_
#define DATA_H_

/*
 * Description: Updates data addresses according to code block size
 * Input:		Code block size
 */
void update_data_address(int ic_length);

/*
 * Description: Adds a string to the data list
 * Input:		A character of the string
 * Output:		Was the add successful
 */
bool add_string_data_to_list(char data, unsigned int address);

/*
 * Description: Gets the next number from the .data line
 * Input:		1. Current transition data
 * 				2. Pointer to the resulted number
 * Output:		Is number valid
 */
bool get_next_number(transition_data* transition, int* number);

/* Description: Free memory list */
 void free_data_node_list();
#endif /* DATA_H_ */
