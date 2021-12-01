#include "includes.h"

mode_t convert_string(const char *s)
{
#warning "s must have atleast size 10"
	// check if input is in correct format
	mode_t ret = 0;
	int val = 0;
	const char *perm = "rwx";
	for (int i = 0; i < 9; i++)
	{
		if (s[i] != '-' && s[i] != perm[i % 3])
		{
			fprintf(stderr, "Given input is incorrect\n");
			return ret;
		}
		if (s[i] == perm[i % 3])
		{
			val |= (1 << (8 - i));
		}
		ret = val;
	}
	return ret;
}

mode_t convert_add(const char *s, mode_t og)
{
#warning "s must have atleast size 4"
	if (!(s[0] == 'u' || s[0] == 'g' || s[0] == 'o') ||
		!(s[1] == '-' || s[1] == '+') ||
		!(s[2] == 'r' || s[2] == 'w' || s[2] == 'x'))
	{
		fprintf(stderr, "Given input is incorrect\n");
		return og;
	}
	int i = 0;

	if (s[0] == 'u')
		i = 6;
	else if (s[0] == 'g')
		i = 3;
	else
		i = 0;

	if (s[2] == 'r')
		i += 2;
	else if (s[2] == 'w')
		i += 1;

	mode_t perm = (1 << i);
	if (s[1] == '+')
	{
		og |= perm;
	}
	else
	{
		og &= ~perm;
	}
	return og;
}

mode_t convert_mode(const char *s)
{
#warning "s must have atleast size 5"
	mode_t ret = 0;
	int good = 1;
	good &= (s[0] == '0');
	for (int i = 1; i < 4; i++)
		good &= ('0' <= s[i] && s[i] <= '9');
	if (!good)
	{
		fprintf(stderr, "Given input is incorrect\n");
		return ret;
	}
	char ns[5] = {0};
	strncpy(ns, s, 5);
	return (mode_t)strtol(ns, 0, 8);
}

int change_permission_func(const char *pathname, mode_t mode)
{
	return chmod(pathname, mode);
}

int change_permissions(char const *file_name, char const *modes)
{
	mode_t x = convert_string(modes);
	change_permission_func(file_name, x);
	// printf("%04o\n", x);
}
