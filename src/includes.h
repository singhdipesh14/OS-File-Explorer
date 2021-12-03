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
static char **files // for file names in a dir
	,
	goto_dir[256] // input for change directory
	,
	current_dir[256] // buffer for current directory
	,
	file_name[256] // input for file names
	,
	input_buffer[256] // input for file names in main fn
	,
	*file_buffer // buffer for saving file content
	,
	save_folder_location_buffer[256]; // buffer for saving location

// sizes
static int files_count = 0 // number of files in a directory
	,
		   stackSz = 0 // number of items in stack
	,
		   file_buffer_size = 30; // number of bytes in file_buffer

// flags
static int options_flag = 0, is_folder = 0;

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