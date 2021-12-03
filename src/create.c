#include "includes.h"

int create()
{
	char choice;
	do
	{
		printf("Do you want to create a file or a directory? (F - file, D - directory) : ");
		scanf("%c", &choice);
		getchar();
	} while (choice != 'F' && choice != 'f' && choice != 'D' && choice != 'd');

	if (choice == 'D' || choice == 'd')
	{
		options_flag = 1;
		printf("Enter the name of the directory you want to create: ");
	}
	else
	{
		options_flag = 0;
		printf("Enter the name of the file you want to create: ");
	}
	file_name[0] = '\0';
	char c = 0;
	int i = 0;
	while (c != '\n')
	{
		scanf("%c", &c);
		if (c == '\n' || i == 256)
		{
			break;
		}
		else
		{
			file_name[i++] = c;
		}
	}
	file_name[i] = '\0';
	if (options_flag)
		create_folder_at_location(file_name);
	else
		create_file_at_location(file_name);
	return 0;
}