#include "stdbool.h"

/*------------------------
--- Struct declaration ---
--------------------------*/

typedef struct{ 						/* We need a 15 integers for the word, we can use the struct since minimum size for int is 16 */
	union							/* Union struct since the word can be a command or data*/
	{
	    unsigned int eraBits : 2; 				/* First two are reserved for E.R.A bits*/
		int dataBits			: 13;

		struct{
		    unsigned int eraBits : 2; 				/* First two are reserved for E.R.A bits*/
			unsigned int dstMethod	: 2;		/* Destination Operand Address Method ID */
			unsigned int srcMethod	: 2;		/* Source Operand Address Method ID */
			unsigned int opcode	: 4;		/* Command ID */
			unsigned int group	: 2;		/* Number of params passed to command ID*/
			unsigned int unused	: 3;		/* Unused Bit, it is always 101 */
		} commandBits;

		struct{ /* Operation between two registers requires only one word*/
		    unsigned int eraBits : 2; 				/* First two are reserved for E.R.A bits*/
			unsigned int dstReg	: 6; 		/* Destination register Number*/
			unsigned int srcReg	: 6; 		/* Source register Number*/
			unsigned int unused 	: 1;		/* Unused Bit, it is always 0 */
		} registerBits;

	}wordBits;

} WordMemory; /* Holds a 15 bits word*/

/*symbols table*/
typedef struct{
	char name[MAX_LABEL_LEN];	/* Label Name*/
	int memAddress;			/* Label Address in memory*/
	int isExtern;			/* Is the label extern or not*/
	int isAction;		/*Is label action or not*/
} symbol_table;

/*line*/
typedef struct{
	char *label;
	int cmd;
	char **args;
    bool isEffectless;
	bool isEOF;
}input_line;
