#include "includes.h"

void yellow()
{
	printf("\033[0;33m");
}
void red()
{
	printf("\033[0;31m");
}

void resetColor()
{
	printf("\033[0m");
}

void green()
{
	printf("\033[0;32m");
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

int display()
{
	system("clear");
	printf("\n\n ***************************************** FILE EXPLORER *****************************************\n\n");
	char cwd[256];
	getcwd(cwd, sizeof(cwd));
	red();
	printf("\n%s\n\n", cwd);
	resetColor();
	DIR *cur_dir = opendir(".");
	struct dirent *myfile;
	struct stat mystat;
	int cnt = 0;
	char *dirFlag;
	printf("\n\n          Name        Size          Permissions           Last Modified Time \n\n");
	printf("\n\n  -------------------------------------FOLDERS---------------------------------------------------\n\n");
	yellow();
	while ((myfile = readdir(cur_dir)) != NULL)
	{
		dirFlag = (char *)calloc(1, sizeof(char));
		bzero(&mystat, sizeof(mystat));
		stat(myfile->d_name, &mystat);
		if (S_ISDIR(mystat.st_mode))
		{

			printf("\t\n%15s\t%10ld\t%15s\t\t%15s", myfile->d_name, mystat.st_size, sperm(mystat.st_mode), ctime(&mystat.st_mtime));
		}
	}
	resetColor();
	printf("\n\n  --------------------------------------FILES--------------------------------------------------\n\n");
	cur_dir = opendir(".");
	green();
	while ((myfile = readdir(cur_dir)) != NULL)
	{
		dirFlag = (char *)calloc(1, sizeof(char));
		bzero(&mystat, sizeof(mystat));
		stat(myfile->d_name, &mystat);
		if (S_ISDIR(mystat.st_mode))
		{
			continue;
		}
		else
		{

			printf("\n%15s\t%10ld\t%15s\t\t%15s", myfile->d_name, mystat.st_size, sperm(mystat.st_mode), ctime(&mystat.st_mtime));
		}
	}
	resetColor();
	printf("\n\n  ---------------------------------------------------------------------------------------------\n\n");
}