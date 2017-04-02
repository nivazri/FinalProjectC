#ifndef CONSTS_H_
#define CONSTS_H_

/* Length of line in code */
#define MAX_LINE_LENGTH 80
#define TWO_REGISTER_FIXED_LEN 6

/* Address definitions */
#define ADDRESS_START 100
#define NO_ADDRESS 0

/* A comment line */
#define COMMENT ';'

/* Label definitions */
#define LABEL_END_TOKEN ':'
#define LABEL_MAX_LENGTH 30

/* String definitions*/
#define END_OF_STRING '\0'
#define END_OF_LINE '\n'

/* Signs*/
#define MINUS_SIGN '-'
#define PLUS_SIGN '+'
#define STRING_DATA_END 0
#define QUOTATION '\"'
#define NUMBER_TOKEN_SEPERATOR ','
#define OPERATION_LINE_MAX_LENGTH 80
#define OPERAND_SEPERATOR ','
#define IMMEDIATE_TOKEN '#'
#define REGISTER_FIRST_TOKEN 'r'
#define REGISTERS_COUNT 8
#define REGISTER_SEPRATOR '['
#define UNUSED_BITS  7 /*111 in base 2*/

/* Operation bits */
#define MEMORY_WORD 15
#define OPERATION_GROUP_BITS_LENGTH 2
#define OPERATION_OP_CODE_BITS_LENGTH 4
#define OPERATION_ADDRESS_METHOD_BITS_LENGTH 2
#define OPERATION_ERA_BITS_LENGTH 2
#define OPERATION_REST_BITS 3

/* Register bits*/
#define REGISTER_ADDRESS_METHOD_BITS_LENGTH 6
#define REGISTERS_REST_BITS 1

/*Memory vars bits*/
#define OPERAND_BITS 13

/* Operation definitions */
#define OPERAION_MIN_WORD_SIZE 1
#define MOV_OPERATION "mov"
#define CMP_OPERATION "cmp"
#define ADD_OPERATION "add"
#define SUB_OPERATION "sub"
#define NOT_OPERATION "not"
#define CLR_OPERATION "clr"
#define LEA_OPERATION "lea"
#define INC_OPERATION "inc"
#define DEC_OPERATION "dec"
#define JMP_OPERATION "jmp"
#define BNE_OPERATION "bne"
#define RED_OPERATION "red"
#define PRN_OPERATION "prn"
#define JSR_OPERATION "jsr"
#define RTS_OPERATION "rts"
#define STOP_OPERATION "stop"

/* Instruction */
#define ENTRY_OPERATION ".entry"
#define STRING_OPERATION ".string"
#define DATA_OPERATION ".data"
#define EXTERN_OPERATION ".extern"

/* File usage */
#define READ_ONLY_MODE "r"
#define WRITE_MODE "w"

/* Input code file extension */
#define FILE_EXT ".as"

/* Output file extensions */
#define EXTERN_FILE_EXT ".ext"
#define CODE_FILE_EXT ".ob"
#define ENTRY_FILE_EXT ".ent"

#endif /* CONSTS_H_ */
