#include "includes.h"

void save_files()
{
	if (!files)
	{
		files = (char **)calloc(30, sizeof(char *));
		files_count = 30;
	}
	DIR *cur_dir = opendir(".");
	struct dirent *myfile;
	int cnt = 0;
	while ((myfile = readdir(cur_dir)) != NULL)
	{
		files[cnt] = (char *)calloc(strlen(myfile->d_name) + 1, sizeof(char));
		strcpy(files[cnt], myfile->d_name);
		cnt++;
		if (cnt >= files_count)
		{
			files_count *= 2;
			files = (char **)realloc(files, files_count * sizeof(char *));
		}
	}
	files_count = cnt;
	closedir(cur_dir);
}

int is_present(char const *file_name)
{
	for (int i = 0; i < files_count; i++)
	{
		if (strcmp(files[i], file_name) == 0)
		{
			return 1;
		}
	}
	return 0;
}

int is_folder_fn(char const *file_name)
{
	for (int i = 0; i < files_count; i++)
	{
		if (strcmp(files[i], file_name) == 0)
		{
			struct stat stat_var;
			stat(file_name, &stat_var);
			if (S_ISDIR(stat_var.st_mode))
			{
				return 1;
			}
		}
	}
	return 0;
}

int is_file_fn(char const *file_name)
{
	for (int i = 0; i < files_count; i++)
	{
		if (strcmp(files[i], file_name) == 0)
		{
			struct stat stat_var;
			stat(file_name, &stat_var);
			if (!S_ISDIR(stat_var.st_mode))
			{
				return 1;
			}
		}
	}
	return 0;
}

void create_folder_at_location(char const *file_name)
{
	int file = mkdir(file_name, 0777);
}

void create_file_at_location(char const *file_name)
{
	FILE *file = fopen(file_name, "w+");
	char str[100];
	printf("Enter file data: \n");
	int i = 0, j = 0;
	char c;
	c = 0;
	i = 0;
	while (c != '\n')
	{
		scanf("%c", &c);
		if (c == '\n' || i == 100)
		{
			break;
		}
		else
		{
			str[i++] = c;
		}
	}
	str[i] = '\0';
	do
	{
		fputc(str[j++], file);
	} while (str[j] != '\0');
	fclose(file);
}