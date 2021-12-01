#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>

char **files, out_dir[30], current_dir[30], *file_buffer, file_name[30];
int files_count, flag, file_buffer_size;

void create_folder_at_location()
{
	int file = mkdir(file_name, 0777);
}

void writing_to_file()
{
	char str[100];
	FILE *file = fopen(file_name, "w");
	getchar();
	gets(str);
	fputs(str, file);
	fclose(file);
}

void create_file_at_location()
{
	int file = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	write(file, file_buffer, sizeof(char) * file_buffer_size);
	printf("Enter file data: \n");
	writing_to_file();
	close(file);
}

void recur()
{
	out_dir[0] = '\0';
	while (strcmp(out_dir, "-1") != 0 && !is_file_fn(out_dir))
	{
		printf("(%s)", current_dir);
		printf(" - Where do you want to create ");
		if (flag)
		{
			printf("directory?");
		}
		else
		{
			printf("file?");
		}
		printf(" (-1 for current directory or directory name to explore) : ");
		scanf(" %s", out_dir);
	}
	if (strcmp(out_dir, "-1") == 0)
	{

		return;
	}
	strcpy(current_dir, out_dir);
	save_files(current_dir);
	chdir(out_dir);
	out_dir[0] = '\0';
	recur();
	chdir("..");
	save_files(".");
}

int main()
{
	char choice;
	files = (char **)calloc(30, sizeof(char *));
	files_count = 30;
	int cnt = 0;
	save_files(".");

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
	save_file_to_buffer(file_name);
	out_dir[0] = '\0';
	strcpy(current_dir, ".");
	if (flag)
		create_folder_at_location();
	else
		create_file_at_location();
	recur();
	free(file_buffer);
	for (int i = 0; i < files_count; i++)
	{
		free(files[i]);
	}
	free(files);
	return 0;
}