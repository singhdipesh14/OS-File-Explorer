#include "includes.h"

/* insert into stack, at head */
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

/*  pop from the stack and return popped value.
	checking for empty is done at function call
	*/
char *delete_stack()
{
	Stack n = st;
	st = st->next;
	char *retur = (char *)calloc(strlen(n->val) + 1, sizeof(char));
	strcpy(retur, n->val);
	free(n);
	return retur;
}

/* saving the file in the file buffer to the desired location */
void save_file_to_location(char const *file_name)
{
	int file = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	write(file, file_buffer, sizeof(char) * file_buffer_size);
	free(file_buffer);
	close(file);
}

/* save the contents of a file to the file buffer */
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

/* recursive function for traversing folders to choose destination */
void recur()
{
	goto_dir[0] = '\0';
	int i = 0;
	char c = 0;
	while (strcmp(goto_dir, "-1") != 0 && !is_folder_fn(goto_dir))
	{
		printf(" - Where do you want to");
		if (options_flag)
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
				goto_dir[i++] = c;
			}
		}
		goto_dir[i] = '\0';
	}
	if (strcmp(goto_dir, "-1") == 0)
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
	else if (strcmp(goto_dir, "..") == 0)
	{
		getcwd(current_dir, sizeof(current_dir));
		insert_stack(current_dir);
	}
	else
	{
		insert_stack("..");
	}
	chdir(goto_dir);
	getcwd(current_dir, sizeof(current_dir));
	save_files();
	display();
	goto_dir[0] = '\0';
	recur();
	if (st)
	{
		chdir(delete_stack());
	}
	save_files();
}

/* function menu */
int copy_paste()
{
	char choice;
	int cnt = 0;

	getcwd(current_dir, sizeof(current_dir)); // saving current dir
	save_files();							  // saving file names in buffer
	do
	{ // choosing operations
		printf("Do you want to copy or move? (C - copy, M - move) : ");
		scanf("%c", &choice);
		getchar();
	} while (choice != 'M' && choice != 'm' && choice != 'C' && choice != 'c');

	if (choice == 'M' || choice == 'm')
	{
		options_flag = 1;
	}
	else
	{
		options_flag = 0;
	}
	int i = 0;
	char c = 0;
	file_name[0] = '\0';
	while (strcmp(file_name, "..") == 0 || strcmp(file_name, ".") == 0 || !is_present(file_name))
	{ // input name of file or folder to be operated on
		printf("Enter the name of the file or folder you want to");
		if (options_flag)
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
	is_folder = S_ISDIR(check_folder.st_mode) ? 1 : 0; // checking for folder
	if (!is_folder)
		save_file_to_buffer(); // save file to buffer
	goto_dir[0] = '\0';
	recur(); // traverse through the folder to select destination
	if (is_folder)
	{
		char command[1000];
		command[0] = '\0';
		if (options_flag)
		{
			strcat(command, "mv "); // move command
		}
		else
		{
			strcat(command, "cp -r "); // copy command
		}
		strcat(command, file_name);
		strcat(command, " \"");
		strcat(command, save_folder_location_buffer);
		strcat(command, "\"");
		system(command); // running command
	}
	else
	{
		if (options_flag)
		{
			delete_fn(file_name); // if move command, delete particular instance
		}
	}
	return 0;
}