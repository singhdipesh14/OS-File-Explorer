#include "includes.h"

void hello_world(char const *file_name)
{
	// unlink(file_name);
	remove(file_name);
}
