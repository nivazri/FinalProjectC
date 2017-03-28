#include "errorHandler.h"
#include "globalHeader.h"

/*
 * Description: Prints runtime error
 * Input:		Message
 */
void print_runtime_error(char* message) {
	fprintf(stderr, "Error: %s \n", message);
}
