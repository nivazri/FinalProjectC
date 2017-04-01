Assembler: Assembler.o secondRun.o firstRun.o operationEncoder.o dataEncoder.o entryEncoder.o externEncoder.o symbolTable.o functions.o
	gcc -g -ansi -Wall -pedantic Assembler.o secondRun.o firstRun.o operationEncoder.o dataEncoder.o entryEncoder.o externEncoder.o symbolTable.o functions.o -o assembler
	rm -f *.o
Assembler.o: main.c functions.h consts.h
	gcc -c -ansi -Wall -pedantic main.c -o Assembler.o

secondRun.o: secondRun.c structs.h consts.h
	gcc -c -ansi -Wall -pedantic secondRun.c -o secondRun.o

firstRun.o: firstRun.c firstRun.h  functions.h structs.h
	gcc -c -ansi -Wall -pedantic firstRun.c -o firstRun.o

operationEncoder.o: operationEncoder.c operationEncoder.h consts.h enums.h structs.h
	gcc -c -ansi -Wall -pedantic operationEncoder.c -o operationEncoder.o

dataEncoder.o: dataEncoder.c dataEncoder.h consts.h structs.h functions.h
	gcc -c -ansi -Wall -pedantic dataEncoder.c -o dataEncoder.o

entryEncoder.o: entryEncoder.c structs.h
	gcc -c -ansi -Wall -pedantic entryEncoder.c -o entryEncoder.o

externEncoder.o: externEncoder.c structs.h
	gcc -c -ansi -Wall -pedantic externEncoder.c -o externEncoder.o

symbolTable.o: symbolTable.c structs.h
	gcc -c -ansi -Wall -pedantic symbolTable.c -o symbolTable.o

functions.o: functions.c structs.h
	gcc -c -ansi -Wall -pedantic functions.c -o functions.o

clean:
	rm *.o
