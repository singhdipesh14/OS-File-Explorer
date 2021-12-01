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

void display(char const *dir_name){
    DIR *cur_dir = opendir(dir_name);
    struct dirent *myfile;
    struct stat mystat;
    int cnt = 0;
    char *dirFlag;
    while((myfile = readdir(cur_dir)) != NULL){
        dirFlag = (char *)calloc(1, sizeof(char));
        bzero(&mystat, sizeof(mystat));
        stat(myfile->d_name, &mystat);
        if(S_ISDIR(mystat.st_mode)){
            dirFlag[cnt] = 'd';
        }
    }
}