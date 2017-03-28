#include "globalHeader.h"
#include "errorHandler.h"

/*function declration*/
void openFile(char *fileName);

int main(int argc, char *argv[])
{
	int i;

	if (argc < MIN_ARGS)
	{
		print_runtime_error("Expected an argument");
		exit(0);
	}

	/*Parse the provided files one by one*/
	for (i=1; i < argc; i++)
	{
		/*Check fileName length*/
		if (strlen(argv[i]) > MAX_FILENAME_LEN)
		{
			printf("ERROR: Maximum allowed file name length is %d.\n", (MAX_FILENAME_LEN));
			return 1;
		}

		printf("------------ Parsing File: \"%s\" ------------\n\n", argv[i]);
		openFile(argv[i]);
	}

	return 0;
}
