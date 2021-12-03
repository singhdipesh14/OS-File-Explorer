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

/* Global Static Files */

// buffers
static char **files, out_dir[256], current_dir[256], file_name[256], going_back_dir[256], input_buffer[256], *file_buffer, save_folder_location_buffer[256];

// sizes
static int files_count = 0, stackSz = 0, file_buffer_size = 30;

// flags
static int flag = 0, is_folder = 0;

// structure for stack
typedef struct stack
{
	char *val;
	struct stack *next;
} * Stack;

// global stack instance
static Stack st = NULL;

/* Function Definitions */

// display
int display();

// file checking functions
int is_file_fn(char const *);
int is_folder_fn(char const *);
int is_present(char const *);

// files saving functions
void save_files();

// delete
void delete_fn(char const *);

// create
void create_folder_at_location(char const *);
void create_file_at_location(char const *);
int create();

// permissions
int change_permissions(char const *, char const *);

// find file
void find_file(char *, const char *, int *, int);

// copy/move and paste
int copy_paste();

// preview
void preview(char const *);
#endif