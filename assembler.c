#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "globalHeader.h"
#include "firstRun.h"
#include "errorHandler.h"
#include "structs.h"

#define LINE_MAX_LEN 81 /* Extra one for \0 */
#define MAX_ARG_COUNT ((LINE_MAX_LEN - 3)/2 + 1)
#define COMMENT_SIGN ';'
#define NEWLINE '\n'
#define SPACE ' '
#define LABEL_DELIM ':'
#define OPCODES_AMOUNT 16
#define REG_FLAG 'r'
#define ARG_SEPERATOR ','
#define STR_DELIM '"'

typedef enum {
	DOT_DATA = OPCODES_AMOUNT, DOT_STRING, DOT_EXTERN, DOT_ENTRY
} inst_type;

/* Gets a line of code */
input_line *getLine(FILE *input) {
	const char *ops[] = { "mov", "cmp", "add", "sub", "not", "clr", "lea",
			"inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", /* Ops until here */
			".data", ".string", ".extern", ".entry" }; /* Instructions *//* The order of these command stay identical to the order of the enum constants in constants.h so the index will match the enum value */
	char cmdStr[LINE_MAX_LEN];
	char tmpStr[LINE_MAX_LEN];
	char *p1, *p2;
	input_line *line;
	int length; /* Temporary length */
	int strIndex = 0; /* Index for next read in the current line */
	int i, status;

	if (!(line = malloc(sizeof(input_line)))) { /* Mem initialisation */
	    /*TODO: FIX ME*/
/**		error(sprintf(errMsg, OUT_OF_RAM));**/
		freeLine(line);
		return NULL;
	}
	line->cmd = -1;
	line->label = NULL;
	line->isEffectless = 0;
	line->isEOF = 0;
	line->args = malloc(sizeof(char *) * MAX_ARG_COUNT);

	for (i = 0; i < MAX_ARG_COUNT; i++) /* Set all cells to NULL */
		line->args[i] = NULL;

	if (!fgets(cmdStr, LINE_MAX_LEN, input)) { /* EOF encountered */
		line->isEOF = 1;
		return line;
	}

	if ((length = strlen(cmdStr))
			== 0|| sscanf(cmdStr, "%s", tmpStr) == 0 || tmpStr[0] == COMMENT_SIGN) { /* Check for effect-less line */
		line->isEffectless = 1;
		free(line->args);
		line->args = NULL;
		return line;
	} else if (cmdStr[length - 1] != NEWLINE) { /* Line exceeds max length */
	    /*TODO: FIXME*/
/**		error(sprintf(errMsg, LINE_EXCEEDS_LEN));**/
		freeLine(line);
		return NULL;
	}

	/* Removes multi whitespace */
	p1 = p2 = cmdStr;
	while (isspace(*p2))
		p2++;
	if (*p2 == '\0') {
		free(line->args);
		line->args = NULL;
		line->isEffectless = 1;
		return line;
	}
	for (; p2 - cmdStr < length - 1; p2++) {
		if (isspace(*p2) && isspace(*(p2 + 1)))
			continue;
		*p1++ = isspace(*p2) ? SPACE : *p2;

	}
	*p1 = '\0';
	/* End whitespace section */
	sscanf(cmdStr, "%s", tmpStr);
	/* Recognise label section */
	if (tmpStr[(length = strlen(tmpStr)) - 1] == LABEL_DELIM) {
		tmpStr[length - 1] = '\0';
		if (validReg(tmpStr)) {/* Error. a label cannot be a register name */
/**			error(sprintf(errMsg, ILLEGAL_LABEL, tmpStr));**/
			freeLine(line);
			return NULL;
		}

		if (validLabel(tmpStr)) {
			if (copyStr(&(line->label), tmpStr))
				strIndex += strlen(line->label) + 2;
			else {
				freeLine(line);
				return NULL; /* Error msg is placed in copyStr */
			}
		} else {
/**			error(sprintf(errMsg, ILLEGAL_LABEL, tmpStr));**/
			freeLine(line);
			return NULL;
		}

		if (!sscanf((cmdStr + strIndex), "%s", tmpStr)) { /* Read the next word for the operator recognition */
/**			error(sprintf(errMsg, SYNTAX_ERROR MISSING_OP)); **/
			freeLine(line);
			return NULL;
		}

	} else {
		line->label = NULL;
	}/* End label section */

	/* Recognises the operator */
	if ((line->cmd = getOp(ops, tmpStr, sizeof(ops) / sizeof(ops[0]))) == -1) {
		freeLine(line);
		return NULL;
	} else
		strIndex += (strlen(tmpStr)
				+ (strcmp(tmpStr, cmdStr + strIndex) == 0 ? 0 : 1));
	if(line->cmd >= DOT_EXTERN){
		free(line->label);
		line->label = NULL;
	}
	/* End operator section */

	/* Seperates arguments */
	i = 0;
	if (!(status = getNextArg(cmdStr + strIndex, tmpStr))) {
		free(line->args);
		line->args = NULL;
	} else if (status == -1)
		return NULL;
	else {
		i++;
		if (!(copyStr(&(line->args[0]), tmpStr))) {
			freeLine(line);
			return NULL;
		}
		for (; (status = getNextArg(NULL, tmpStr)); i++) {
			if (status == -1)
				return NULL;
			if (!(copyStr(&(line->args[i]), tmpStr))) {
				freeLine(line);
				return NULL;
			}
		}
	}

	if ((length = i) > 0)
		line->args = realloc(line->args, sizeof(char *) * length + 1); /* Can't fail because it's shrinking */

	/* End arguments section */
	return line;
}/* End getLine */

/* Release all allocated mem from struct */
void freeLine(input_line *line) {
	int i;
	if (!line)
		return;
	free(line->label);
	if (line->args != NULL)/* Release args */
		for (i = 0; line->args[i] != NULL; i++)
			free(line->args[i]);
	free(line->args);
	free(line);
}/* End freeLine */

/* Validate whether the given str of a label is valid*/
int validLabel(const char *labelStr) {
	int i;
	if (validReg(labelStr))
		return 0; /* Not a register */

	if (!isalpha(labelStr[0])) {/* Starts with alphabetic */
		return 0;
	} else {
		for (i = 1; labelStr[i]; i++) {/* Rest is alphanumeric */
			if (!isalnum(labelStr[i]))
				return 0;
		}
		return 1;
	}
}/* End validLabel */

/* Validates whether the given str of register name is legal. */
int validReg(const char* regStr) {
	return ((regStr[0] == REG_FLAG && '0' <= regStr[1] && regStr[1] <= '7'
			&& regStr[2] == '\0') ? 1 : 0);
} /* End validReg */

int copyStr(char **dest, const char *src) {
	int strIndex = 0;
	if (!(*dest = malloc(strIndex = (strlen(src) + 1)))) {
		/**error(sprintf(errMsg, OUT_OF_RAM));**/
		return 0;
	}
	strcpy(*dest, src);
	return 1;
}/* End copyStr */

/* Find the operator in the given op list*/
int getOp(const char **ops, const char *str, const int opsAmount) {
	int i;
	for (i = 0; i < opsAmount; i++)
		if (strcmp(str, ops[i]) == 0) /* Found the op */
			return i;
	/**error(sprintf(errMsg, SYNTAX_ERROR UNKNOWN_OP));**/
	return -1;
}/* End getOp */

/* Gets the next argument from the current line */
int getNextArg(char *src, char *dest) {
	static char *cmdStr;
	int inStr = 0, i;
	if (src != NULL) {
		cmdStr = src;
	}
	while (isspace(*cmdStr))
		cmdStr++;
	if (*cmdStr == '\0')
		return 0;
	for (i = 0; *cmdStr != ARG_SEPERATOR && *cmdStr != '\0'; cmdStr++) {
		if (inStr) {
			if (*cmdStr == STR_DELIM)
				inStr = 0;
		} else if (isspace(*cmdStr))
			break;
		else if (*cmdStr == STR_DELIM) {
			inStr = 1;
		}
		dest[i] = *cmdStr;
		i++;
	}
	if (i == 0) {
/**		error(sprintf(errMsg, SYNTAX_ERROR EMPTY_ARG));**/
		return -1;
	}
	while (isspace(*cmdStr))
		cmdStr++;
	if (*cmdStr != '\0' && *cmdStr != ARG_SEPERATOR) {
/**		error(sprintf(errMsg, SYNTAX_ERROR UNKNOWN_ARG_TYPE));**/
		return -1;
	}
	dest[i] = '\0';
	if (*cmdStr == ARG_SEPERATOR) {
		cmdStr++;
		if (*cmdStr == '\0') {
/**			error(sprintf(errMsg, SYNTAX_ERROR EMPTY_ARG));**/
			return -1;
		}
	}
	return 1;
}/* End getNextArg */
