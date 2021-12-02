#include "includes.h"

int main()
{
	while (1)
	{
		display();
		int choice = -1;
		// // printf choices
		printf("\n\nPress 0 for find, 1 for create, 2 for copy_paste, 3 for delete, 4 for exploring, 5 for change permissions, 6 for preview, 7 for exit : \n\n");
		scanf("%d", &choice);
		getchar();
		int cnt = 0;
		char c = 0;
		int i = 0;
		save_files();
		switch (choice)
		{
		case 0:

			printf("Enter the file name: ");
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
			printf("enter any key");
			getchar();
			break;
		case 1:
			create();
			break;
		case 2:
			copy_paste();
			break;
		case 3:
			printf("Enter the file to delete: ");
			input_buffer[0] = '\0';
			while (!is_present(input_buffer))
			{
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
			printf("Enter explore dir: ");
			input_buffer[0] = '\0';
			while (!is_folder_fn(input_buffer))
			{
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
			printf("Enter file name: ");
			input_buffer[0] = '\0';
			while (!is_present(input_buffer))
			{
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
			printf("enter file name to preview");
			input_buffer[0] = '\0';
			while (!is_file_fn(input_buffer))
			{
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
