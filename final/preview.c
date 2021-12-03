#include "includes.h"

void preview(char const *file_name)
{
	FILE *finp = fopen(file_name, "r");
	printf("\n\n");
	char c = 0;
	while (c != EOF)
	{
		c = fgetc(finp);
		if (c != EOF)
		{
			printf("%c", c);
		}
	}
	printf("\n\nPress Enter to continue: ");
	getchar();
	printf("\n\n");
	fclose(finp);
}