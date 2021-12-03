#include "includes.h"

void delete_fn(char const *file_name)
{
	// unlink(file_name);
	remove(file_name);
}
