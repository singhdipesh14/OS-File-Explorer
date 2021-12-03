#include "includes.h"

int main()
{
	while (1)
	{
		display();
		int choice = -1;
		// // printf choices
		printf("\n\n\t*******MENU*******\n\tPress :\n\t0 -> Find\n\t1 -> Create\n\t2 -> Copy and Paste\n\t3 -> Delete\n\t4 -> Exploring\n\t5 -> Change Permissions\n\t6 -> Preview File\n\t7 -> Exit \n\n\t----> ");
		scanf("%d", &choice);
		while (getchar() != '\n')
			;
		int cnt = 0;
		char c = 0;
		int i = 0;
		save_files();
		switch (choice)
		{
		case 0:

			printf("\nEnter the file name: ");
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
					input_buffer[i++] = c;
				}
			}
			input_buffer[i] = '\0';
			find_file(".", input_buffer, &cnt, 0);
			printf("\nPress ENTER to continue: ");
			while (getchar() != '\n')
				;
			break;
		case 1:
			create();
			break;
		case 2:
			copy_paste();
			break;
		case 3:
			input_buffer[0] = '\0';
			while (!is_present(input_buffer))
			{
				printf("\nEnter the file name to delete: ");
				input_buffer[0] = '\0';
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
						input_buffer[i++] = c;
					}
				}
				input_buffer[i] = '\0';
			}
			delete_fn(input_buffer);
			break;
		case 4:
			input_buffer[0] = '\0';
			while (!is_folder_fn(input_buffer))
			{
				printf("\nEnter the name of directory you want to explore: ");
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
						input_buffer[i++] = c;
					}
				}
				input_buffer[i] = '\0';
			}
			chdir(input_buffer);
			break;
		case 5:
			input_buffer[0] = '\0';
			while (!is_present(input_buffer))
			{
				printf("\nEnter the file name: ");
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
						input_buffer[i++] = c;
					}
				}
				input_buffer[i] = '\0';
			}
			// print ways modes can be entered //
			// Input can be in form of string "rwxrw-r--"
			// Input can be in form of (u/g/o)(+/-)(r/w/x)
			// Input can be in form 0777
			printf("\nFile Permission can be in the form of:\n-> String \"rwxrw-r--\"\n-> \"(u/g/o)(+/-)(r/w/x)\"\n-> \"0777\"\n\nEnter file permission: ");
			char modes[30];
			c = 0;
			i = 0;
			while (c != '\n')
			{
				scanf("%c", &c);
				if (c == '\n' || i == 30)
				{
					break;
				}
				else
				{
					modes[i++] = c;
				}
			}
			modes[i] = '\0';
			change_permissions(input_buffer, modes);
			break;
		case 6:
			input_buffer[0] = '\0';
			while (!is_file_fn(input_buffer))
			{
				printf("\nEnter file name which you want to preview: ");
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
						input_buffer[i++] = c;
					}
				}
				input_buffer[i] = '\0';
			}
			preview(input_buffer);
			break;
		default:
			for (int i = 0; i < files_count; i++)
			{
				free(files[i]);
			}
			free(files);
			exit(0);
			break;
		}
	}
	return 0;
}
