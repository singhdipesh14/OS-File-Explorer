#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>

static char **files, out_dir[256], current_dir[256], *file_buffer, file_name[30], going_back_dir[256];
;
static int files_count = 0, flag = 0, file_buffer_size = 0, going_back = 0, stackSz = 0;
typedef struct stack
{
	char *val;
	struct stack *next;
} * Stack;

static Stack st = NULL;
int display();
void hello_world(char const *file_name);
int create();
int change_permissions(char const *file_name, char const *modes);
void find_file(char *dir, const char *file_name, int *cnt, int depth);
int copy_paste();
void preview(char const *file_name);
#endif