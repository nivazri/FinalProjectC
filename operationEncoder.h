#ifndef OPERATIONENCODER_H_
#define OPERATIONENCODER_H_

#include <stdbool.h>

/*
 * Description: Initializes the operation list used for encoding
 * Output:		Did the initialization end
 */
bool init_operation_list();

/*
 * Description: Adds an operation into the list
 * Input:		1. Operation name
 * 				2. Op code
 * 				3. Number of operands
 * Output:		Did add successfully
 */
bool add_operation_to_list(char* name, unsigned int code, int operands);

/*
 * Description: Free memory list
 */
void free_operation_list();

#endif /* OPERATIONENCODER_H_ */
