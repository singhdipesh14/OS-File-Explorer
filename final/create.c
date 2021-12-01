#include "includes.h"

void create_folder_at_location()
{
	int file = mkdir(file_name, 0777);
}

void create_file_at_location()
{
	FILE *file = fopen(file_name, "w+");
	// write(file, file_buffer, sizeof(char) * file_buffer_size);
	char str[100];
	printf("Enter file data: \n");
	int i = 0, j = 0;
	char c;
	scanf(" %s", str);
	do
	{
		fputc(str[i++], file);
	} while (str[i] != '\0');
	fclose(file);
}

int create()
{
	char choice;
	do
	{
		printf("Do you want to create a file or a directory? (F - file, D - directory) : ");
		scanf(" %c", &choice);
	} while (choice != 'F' && choice != 'f' && choice != 'D' && choice != 'd');

	if (choice == 'D' || choice == 'd')
	{
		flag = 1;
		printf("Enter the name of the directory you want to create: ");
	}
	else
	{
		flag = 0;
		printf("Enter the name of the file you want to create: ");
	}
	file_name[0] = '\0';
	scanf(" %s", file_name);
	if (flag)
		create_folder_at_location();
	else
		create_file_at_location();
	return 0;
}