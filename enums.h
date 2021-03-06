#ifndef ENUMS_H_
#define ENUMS_H_

/* Addressing methods */
typedef enum {
	INVALID_ADDRESS_METHOD = -1,
	IMMEDIATE = 0,
	DIRECT = 1,
	REGISTER_INDEX = 2,
	DIRECT_REGISTER = 3
} ADDRESS_METHOD;

/* ERA options */
typedef enum {
	ABSOLUTE = 0,
	EXTERNAL = 1,
	RELOCATABLE = 2
} ERA;

/* Number of operands */
typedef enum {
	NO_OPERANDS = 0,
	ONE_OPERAND = 1,
	TWO_OPERANDS = 2
} OPERANDS_COUNT;

#endif /* ENUMS_H_ */
