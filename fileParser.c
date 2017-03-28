#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "globalHeader.h"
#include "structs.h"

bool isDirect(input_line *line,char* tmpString);

const char *ops[] = { "mov", "cmp", "add", "sub", "not", "clr", "lea",
			"inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};

input_line *getLine(FILE *file) {
    /*struct of line refer: structs.h*/
	input_line *line;

	/*temp variables*/
    char tmpStr[LINE_MAX_LEN];
    char *restLine;

    /*label parameters*/
    char *label;
    const char LABEL_STRTOK[2]=":";

	/* Mem initialisation */
	if(!(line = malloc(sizeof(input_line)))) {
	    /*TODO: send error*/
		freeLine(line);
		return NULL;
	}

    /*initialization values struct*/
    line->label=NULL;
    line->isEffectless = false;
    line->isEOF = false;

    /*check if EOF encountered*/
    if (!fgets(tmpStr, LINE_MAX_LEN, file)) {
        line->isEOF = true;
		return line;
	}

    /*check if the line is comment*/
    if(tmpStr[0] == COMMENT_SIGN) {
        line->isEffectless = true;
        return line;
    }

    /*check if label in line*/
    if(strchr(tmpStr,LABEL_DELIM)){
        /*get the name of the label*/
        label=strtok(tmpStr,LABEL_STRTOK);
        line->label=label;

        /*put rest of the line in tmpString*/
        restLine=strtok(NULL,LABEL_STRTOK);
        strcpy(tmpStr,restLine);
    }

    /*check if .extern or .data or .entry or .string*/
    if(isDirect(line,tmpStr)){
        printf("unhandled direction sentence\n");
    }
    else {
    /*operation sentence*/
        line->cmd=getOp(line,tmpStr);
    }

    return line;
} /*End of method getLine*/

/* Release all allocated mem from struct */
void freeLine(input_line *line) {
	int i;
	if (!line)
		return;
	free(line->label);
	if (line->args != NULL)/* Release args */
		for (i = 0; line->args[i] != NULL; i++)
			free(line->args[i]);
/**	free(line->args);**/
	free(line);
}/* End freeLine */

bool isDirect(input_line *line,char* tmpString){
    const char EXTERN_STRTOK[2]=".extern";
    const char ENTRY_STRTOK[2]=":";
    const char DATA_STRTOK[2]=":";
    const char STRING_STRTOK[2]=":";

    if(strstr(tmpString,DOT_EXTERN)){
        return true;
    }
    if(strstr(tmpString,DOT_ENTRY)){
        return true;
    }
    if(strstr(tmpString,DOT_STRING)){
        return true;
    }
    if(strstr(tmpString,DOT_DATA)){
        return true;
    }
    return false;
}

int getOp(input_line *line,char* tmpString) {
	int i;
	char *tmp;
    const char s[2]= " ";

	for (i = 0; i < OPCODES_AMOUNT; i++)
		if (strstr(tmpString, ops[i])) /* Found the op */
                tmp=strtok(tmpString,s);
                line->args=tmp;
                return i;
	return -1;
}/* End  */
