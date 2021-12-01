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

char **files, out_dir[256], current_dir[256], *file_buffer, file_name[30], going_back_dir[256];
;
int files_count, flag, file_buffer_size, going_back = 0;

int stackSz = 0;
typedef struct stack
{
	char *val;
	struct stack *next;
} * Stack;

Stack st = NULL;

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

char const *
sperm(__mode_t mode)
{
	static char local_buff[16] = {0};
	int i = 0;
	// user permissions
	if (S_ISDIR(mode))
	{
		local_buff[i] = 'd';
	}
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IRUSR) == S_IRUSR)
		local_buff[i] = 'r';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IWUSR) == S_IWUSR)
		local_buff[i] = 'w';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IXUSR) == S_IXUSR)
		local_buff[i] = 'x';
	else
		local_buff[i] = '-';
	i++;
	// group permissions
	if ((mode & S_IRGRP) == S_IRGRP)
		local_buff[i] = 'r';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IWGRP) == S_IWGRP)
		local_buff[i] = 'w';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IXGRP) == S_IXGRP)
		local_buff[i] = 'x';
	else
		local_buff[i] = '-';
	i++;
	// other permissions
	if ((mode & S_IROTH) == S_IROTH)
		local_buff[i] = 'r';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IWOTH) == S_IWOTH)
		local_buff[i] = 'w';
	else
		local_buff[i] = '-';
	i++;
	if ((mode & S_IXOTH) == S_IXOTH)
		local_buff[i] = 'x';
	else
		local_buff[i] = '-';
	return local_buff;
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
	struct stat mystat;
	int cnt = 0;
	printf("\n\n");
	while ((myfile = readdir(cur_dir)) != NULL)
	{
		files[cnt] = (char *)calloc(strlen(myfile->d_name) + 1, sizeof(char));
		strcpy(files[cnt], myfile->d_name);
		bzero(&mystat, sizeof(mystat));
		stat(myfile->d_name, &mystat);
		printf("%10.10s", sperm(mystat.st_mode));
		printf("\t%d", mystat.st_uid);
		printf("\t%ld", mystat.st_size);
		printf("\t%s", myfile->d_name);
		printf("\t%s", ctime(&mystat.st_mtime));
		cnt++;
		if (cnt >= files_count)
		{
			files_count *= 2;
			files = (char **)realloc(files, files_count * sizeof(char *));
		}
	}
	printf("\n\n");
	files_count = cnt;
	closedir(cur_dir);
}

void yellow(){
	printf("\033[0;33m");
}

void resetColor(){
	printf("\033[0m");
}

void green(){
	printf("\033[0;32m");
}

void display(char const *dir_name){
	system("clear");
	printf("\n\n ***************************************** FILE EXPLORER *****************************************\n\n");
    DIR *cur_dir = opendir(dir_name);
    struct dirent *myfile;
    struct stat mystat;
    int cnt = 0;
    char *dirFlag;
	printf("\n\n          Name        Size          Permissions           Last Modified Time \n\n");
	printf("\n\n  -------------------------------------FOLDERS---------------------------------------------------\n\n");
	yellow();
    while((myfile = readdir(cur_dir)) != NULL){
        dirFlag = (char *)calloc(1, sizeof(char));
        bzero(&mystat, sizeof(mystat));
        stat(myfile->d_name, &mystat);
        if(S_ISDIR(mystat.st_mode)){

			printf("\t\n%15s\t%10ld\t%15s\t\t%15s", myfile->d_name, mystat.st_size, sperm(mystat.st_mode), ctime(&mystat.st_mtime));

        }
    }
	resetColor();
	printf("\n\n  --------------------------------------FILES--------------------------------------------------\n\n");
	cur_dir = opendir(dir_name);
	green();
	while((myfile = readdir(cur_dir)) != NULL){
        dirFlag = (char *)calloc(1, sizeof(char));
        bzero(&mystat, sizeof(mystat));
        stat(myfile->d_name, &mystat);
        if(S_ISDIR(mystat.st_mode)){
			continue;
		}
		else{

			printf("\n%15s\t%10ld\t%15s\t\t%15s", myfile->d_name, mystat.st_size, sperm(mystat.st_mode), ctime(&mystat.st_mtime));

        }
    }
	resetColor();
	printf("\n\n  ---------------------------------------------------------------------------------------------\n\n");
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
		printf("(%s)\n", current_dir);
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

void delete_file(char const *file_name)
{
	//unlink(file_name);
	remove(file_name);
}

int main()
{
	char choice;
	files = (char **)calloc(30, sizeof(char *));
	files_count = 30;
	int cnt = 0;
	getcwd(going_back_dir, sizeof(going_back_dir));
	save_files(going_back_dir);
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
		delete_file(file_name);
	}
	free(file_buffer);
	for (int i = 0; i < files_count; i++)
	{
		free(files[i]);
	}
	free(files);
	return 0;
}