#include "globalHeader.h"
#include "structs.h"
#include "firstRun.h"
#include "errorHandler.h"

void openFile(char *fileName)
{
    /*This method open files*/
	FILE *file = fopen(fileName,FILE_OPEN_MODE);

	if (file == NULL)
	{
		printf("ERROR: Cannot open file: %s\n", fileName);
		return;
	}
    firstRun(file);
	fclose(file);
}

void firstRun(FILE *file)
{
    input_line *line;
    int lineIndex;

    for(lineIndex=1; true;lineIndex++) /* Runs through all the lines. */
    {
        line = getLine(file);
        if (line->isEOF==true) {
            freeLine(line);
            break; /* End when EOF is encountered */
        }

        if (line->isEffectless==true) {
            continue;
        }

        handleLine(line);
    }/*end of for*/
} /*end of firstRun*/

void handleLine(input_line *line){
    switch(line->cmd) {
        /*Two operands group*/
        case MOV:
        case CMP:
        case ADD:
        case SUB:
        case LEA:
            printf("Two operands group\n");

        break;

        /*One operand group*/
        case NOT:
        case CLR:
        case INC:
        case DEC:
        case JMP:
        case BNE:
        case RED:
        case PRN:
        case JSR:
            printf("One operand group\n");

        break;
        /*No operands group*/
        case RTS:
        case STOP:
            printf("No operand group\n");

        break;
    }
}
