#include "includes.h"

void find_file(char *dir, const char *file_name, int *cnt, int depth)
{
	// Initialize *cnt to 0
	static char path[1 << 10];
	DIR *dp;
	struct dirent *entry;
	struct stat file_info;
	if ((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "Cannot open directory %s\n", dir);
		return;
	}
	chdir(dir);
	while ((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &file_info);
		if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
			continue;
		if (S_ISDIR(file_info.st_mode))
		{
			find_file(entry->d_name, file_name, cnt, depth + 1);
		}
		else if (strcmp(file_name, entry->d_name) == 0)
		{
			char *ret = getcwd(path, sizeof(path));
			assert(ret != NULL);
			printf("%d) %s/%s\n", ++(*cnt), ret, entry->d_name);
		}
	}
	if (depth != 0)
		chdir("..");
	closedir(dp);
}