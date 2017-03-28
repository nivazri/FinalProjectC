/*------------------------
--- Includes of C libs ---
--------------------------*/

#include <stdio.h>

/* String constants */
#define NEWLINE '\n'
#define COMMENT_SIGN ';'
#define LABEL_DELIM ':'
#define STR_DELIM '"'
#define REG_FLAG 'r'
#define IMD_FLAG '#'
#define RND_FLAG '*'
#define ARG_SEPERATOR ','
#define SPACE ' '

/* Flag status */
typedef enum {
	ASM_SUCCESS, ASM_FAILURE
} FLAG;

/* Opcodes enum table */
typedef enum {
	MOV,
	CMP,
	ADD,
	SUB,
	NOT,
	CLR,
	LEA,
	INC,
	DEC,
	JMP,
	BNE,
	RED,
	PRN,
	JSR,
	RTS,
	STOP
} OPCODE;

/*--------------------------------------
--- Declaration of Global Constants  ---
----------------------------------------*/

/*Minimum number of arguments that should be passed to the compiler*/
#define MIN_ARGS 2

/*Maximum file name length allowed*/
#define MAX_FILENAME_LEN 100

/*Maximum length of the label allowed*/
#define MAX_LABEL_LEN 30

/* Size constants */
#define MAX_MEMORY_SIZE 1000
#define MAX_FILE_ZISE 1000
#define FIRST_MEM_ADDR 100
#define LINE_MAX_LEN 81 /* Extra one for \0 */
#define MAX_ARG_COUNT ((LINE_MAX_LEN - 3)/2 + 1) /* Max arg count assuming shortest command is 3 letters and shortest args are at least 1 character */
#define DECODE_SIZE 2
#define OPERAND_SIZE 2
#define RED_OPERAND_SIZE 6
#define OPCODE_SIZE 4
#define GROUP_SIZE 2
#define RND_SIZE 2
#define UNUSED_SIZE 1
#define VALUE_SIZE 13
#define OPCODES_AMOUNT 16
#define WORD_SIZE 15
#define REG_AMOUNT 8
#define EXT_LEN 4 /* Length of the extension file name. */
#define INPUT_EXT ".as"
#define OBJ_EXT ".ob"
#define EXT_EXT ".ext"
#define ENT_EXT ".ent"

#define DOT_STRING ".string"
#define DOT_EXTERN ".extern"
#define DOT_ENTRY ".entry"
#define DOT_DATA ".data"
