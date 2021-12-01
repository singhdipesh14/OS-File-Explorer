#include "includes.h"

void insert_stack(char *buffer)
{
	Stack n = (Stack)malloc(sizeof(struct stack));
	n->val = (char *)calloc(strlen(buffer) + 1, sizeof(char));
	strcpy(n->val, buffer);
	n->next = NULL;
	if (st == NULL)
	{
		st = n;
		return;
	}
	n->next = st;
	st = n;
}

char *delete_stack()
{
	Stack n = st;
	st = st->next;
	char *retur = (char *)calloc(strlen(n->val) + 1, sizeof(char));
	strcpy(retur, n->val);
	free(n);
	return retur;
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

void save_files(char const *dir_name)
{
	DIR *cur_dir = opendir(dir_name);
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

int is_file_fn(char const *file_name)
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

void save_file_to_location()
{
	int file = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	write(file, file_buffer, sizeof(char) * file_buffer_size);
	close(file);
}

void recur()
{
	out_dir[0] = '\0';
	while (strcmp(out_dir, "-1") != 0 && !is_file_fn(out_dir))
	{
		printf(" - Where do you want to");
		if (flag)
		{
			printf(" move?");
		}
		else
		{
			printf(" copy?");
		}
		printf(" (-1 for current directory or directory name to explore) : ");
		scanf(" %s", out_dir);
	}
	if (strcmp(out_dir, "-1") == 0)
	{
		save_file_to_location();
		return;
	}
	else if (strcmp(out_dir, "..") == 0)
	{
		getcwd(going_back_dir, sizeof(going_back_dir));
		insert_stack(going_back_dir);
	}
	else
	{
		insert_stack("..");
	}
	chdir(out_dir);
	getcwd(going_back_dir, sizeof(going_back_dir));
	strcpy(current_dir, going_back_dir);
	save_files(current_dir);
	display();
	out_dir[0] = '\0';
	recur();
	if (st)
	{
		chdir(delete_stack());
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	save_files(".");
}

void save_file_to_buffer(char const *file_name)
{
	int file = open(file_name, O_RDONLY);
	file_buffer = (char *)calloc(30, sizeof(char));
	int size = 30;
	char c;
	while (read(file, &c, sizeof(c)) > 0)
	{
		file_buffer[file_buffer_size++] = c;
		if (file_buffer_size >= size)
		{
			size *= 2;
			file_buffer = (char *)realloc(file_buffer, size * sizeof(char));
		}
	}
	close(file);
}

int copy_paste()
{
	char choice;
	files = (char **)calloc(30, sizeof(char *));
	files_count = 30;
	int cnt = 0;
	getcwd(going_back_dir, sizeof(going_back_dir));
	save_files(going_back_dir);
	display();
	do
	{
		printf("Do you want to copy or move? (C - copy, M - move) : ");
		scanf(" %c", &choice);
	} while (choice != 'M' && choice != 'm' && choice != 'C' && choice != 'c');

	if (choice == 'M' || choice == 'm')
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}

	file_name[0] = '\0';
	while (!is_present(file_name))
	{
		printf("Enter the name of the file or folder you want to");
		if (flag)
		{
			printf(" move : ");
		}
		else
		{
			printf(" copy : ");
		}
		scanf(" %s", file_name);
	}
	save_file_to_buffer(file_name);

	out_dir[0] = '\0';
	strcpy(current_dir, going_back_dir);
	recur();
	if (flag)
	{
		hello_world(file_name);
	}
	free(file_buffer);
	for (int i = 0; i < files_count; i++)
	{
		free(files[i]);
	}
	free(files);
	return 0;
}