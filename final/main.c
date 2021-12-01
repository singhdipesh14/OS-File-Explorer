#include "includes.h"

int main()
{
	while (1)
	{
		display();
		// options
		int choice = -1;
		// // printf choices
		printf("\n\nPress 0 for find, 1 for create, 2 for copy_paste, 3 for delete, 4 for exploring, 5 for change permissions, 6 for preview, 7 for exit : \n\n");
		scanf("%d", &choice);
		char find_file_buffer[100];
		int cnt = 0;
		switch (choice)
		{
		case 0:

			printf("Enter the file name: ");
			scanf(" %s", find_file_buffer);
			find_file(".", find_file_buffer, &cnt, 0);
			printf("enter any key");
			getchar();
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
			scanf(" %s", find_file_buffer);
			hello_world(find_file_buffer);
			break;
		case 4:
			printf("Enter explore dir: ");
			scanf(" %s", find_file_buffer);
			chdir(find_file_buffer);
			break;
		case 5:
			printf("Enter file name: ");
			scanf(" %s", find_file_buffer);
			char modes[30];
			scanf(" %s", modes);
			change_permissions(find_file_buffer, modes);
			break;
		case 6:
			printf("enter file name to preview");
			scanf(" %s", find_file_buffer);
			preview(find_file_buffer);
			break;
		default:
			exit(0);
			break;
		}
	}
	return 0;
}
