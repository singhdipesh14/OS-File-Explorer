#include "includes.h"

int convert_string(const char *permission_string, mode_t *new_permission)
{
	// check if input is in correct format
	int val = 0;
	const char *perm = "rwx";
	for (int i = 0; i < 9; i++)
	{
		if (permission_string[i] != '-' && permission_string[i] != perm[i % 3])
		{
			return -1;
		}
		if (permission_string[i] == perm[i % 3])
		{
			val |= (1 << (8 - i));
		}
	}
	*new_permission = val;
	return 0;
}

int convert_add(const char *permission_string, mode_t original_permission, mode_t *new_permission)
{
	if (!(permission_string[0] == 'u' || permission_string[0] == 'g' || permission_string[0] == 'o') ||
		!(permission_string[1] == '-' || permission_string[1] == '+') ||
		!(permission_string[2] == 'r' || permission_string[2] == 'w' || permission_string[2] == 'x'))
	{
		return -1;
	}
	int i = 0;

	if (permission_string[0] == 'u')
		i = 6;
	else if (permission_string[0] == 'g')
		i = 3;
	else
		i = 0;

	if (permission_string[2] == 'r')
		i += 2;
	else if (permission_string[2] == 'w')
		i += 1;

	mode_t perm = (1 << i);
	if (permission_string[1] == '+')
	{
		original_permission |= perm;
	}
	else
	{
		original_permission &= ~perm;
	}
	*new_permission = original_permission;
	return 0;
}

int convert_mode(const char *s, mode_t *new_permission)
{
	int good = 1;
	good &= (s[0] == '0');
	for (int i = 1; i < 4; i++)
		good &= ('0' <= s[i] && s[i] <= '9');
	if (!good)
	{
		return -1;
	}
	char ns[5] = {0};
	strncpy(ns, s, 5);
	*new_permission = (mode_t)strtol(ns, 0, 8);
	return 0;
}

int change_permission_fn(const char *pathname, mode_t mode)
{
	return chmod(pathname, mode);
}

int change_permissions(char const *pathname, char const *permission_string)
{

	int permission_string_length = strlen(permission_string);
	mode_t new_permission = 0;
	int status;

	if (permission_string_length == 9)
	{
		status = convert_string(permission_string, &new_permission);
	}
	else if (permission_string_length == 4)
	{
		status = convert_mode(permission_string, &new_permission);
	}
	else if (permission_string_length == 3)
	{
		// struct stat file_info; Assuming this variable is declared which stores (as the name suggest) the file info of "pathname"
		struct stat file_info;
		assert(lstat(pathname, &file_info) >= 0);
		mode_t original_permission = file_info.st_mode;
		status = convert_add(permission_string, original_permission, &new_permission);
	}
	else
	{
		status = -1;
	}

	if (status == 0)
	{
		change_permission_fn(pathname, new_permission);
		printf("\nChanged file permission successfully\n");
	}
	else
	{
		fprintf(stderr, "Invalid permission input\n");
		return 1;
	}
	printf("Enter any key");
	getchar();
	return 0;
}