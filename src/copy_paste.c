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

void save_file_to_location(char const *file_name)
{
	int file = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	write(file, file_buffer, sizeof(char) * file_buffer_size);
	free(file_buffer);
	close(file);
}

void save_folder_to_location()
{
}

void save_file_to_buffer()
{
	int file = open(file_name, O_RDONLY);
	int size = 30;
	file_buffer = (char *)calloc(30, sizeof(char));
	file_buffer_size = 30;
	char c;
	while (read(file, &c, sizeof(c)) > 0)
	{
		file_buffer[(file_buffer_size++)] = c;
		if (file_buffer_size >= size)
		{
			size *= 2;
			file_buffer = (char *)realloc(file_buffer, size * sizeof(char));
		}
	}
	close(file);
}

void recur()
{
	out_dir[0] = '\0';
	int i = 0;
	char c = 0;
	while (strcmp(out_dir, "-1") != 0 && !is_folder_fn(out_dir))
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
				out_dir[i++] = c;
			}
		}
		out_dir[i] = '\0';
	}
	if (strcmp(out_dir, "-1") == 0)
	{
		if (is_folder)
		{
			getcwd(save_folder_location_buffer, sizeof(save_folder_location_buffer));
		}
		else
		{
			printf("Enter the file name or press ENTER to skip:");
			char temp_name[100];
			i = 0;
			c = 0;
			while (c != '\n')
			{
				scanf("%c", &c);
				if (c == '\n' || i == 100)
				{
					break;
				}
				else
				{
					file_name[i++] = c;
				}
			}
			if (strlen(temp_name) == 0)
			{
				save_file_to_location(temp_name);
			}
			else
			{
				save_file_to_location(file_name);
			}
		}
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
	save_files();
	display();
	out_dir[0] = '\0';
	recur();
	if (st)
	{
		chdir(delete_stack());
	}
	save_files();
}

int copy_paste()
{
	char choice;
	int cnt = 0;

	getcwd(going_back_dir, sizeof(going_back_dir));
	save_files();
	do
	{
		printf("Do you want to copy or move? (C - copy, M - move) : ");
		scanf("%c", &choice);
		getchar();
	} while (choice != 'M' && choice != 'm' && choice != 'C' && choice != 'c');

	if (choice == 'M' || choice == 'm')
	{
		flag = 1;
	}
	else
	{
		flag = 0;
	}
	int i = 0;
	char c = 0;
	file_name[0] = '\0';
	while (strcmp(file_name, "..") == 0 || strcmp(file_name, ".") == 0 || !is_present(file_name))
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
				file_name[i++] = c;
			}
		}
		file_name[i] = '\0';
	}
	struct stat check_folder;
	stat(file_name, &check_folder);
	is_folder = S_ISDIR(check_folder.st_mode) ? 1 : 0;
	if (!is_folder)
		save_file_to_buffer();
	out_dir[0] = '\0';
	strcpy(current_dir, going_back_dir);
	recur();
	if (is_folder)
	{
		char command[1000];
		command[0] = '\0';
		if (flag)
		{
			strcat(command, "mv ");
		}
		else
		{
			strcat(command, "cp -r ");
		}
		strcat(command, file_name);
		strcat(command, " \"");
		strcat(command, save_folder_location_buffer);
		strcat(command, "\"");
		printf("%s\n", command);
		getchar();
		system(command);
		printf("done\n");
		getchar();
	}
	else
	{
		if (flag)
		{
			delete_fn(file_name);
		}
	}
	return 0;
}