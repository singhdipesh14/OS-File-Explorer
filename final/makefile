run: main.o
	gcc -o run main.o display.o create.o find_file.o change_permissions.o copy_paste.o delete.o preview.o

main.o: delete.o display.o create.o copy_paste.o find_file.o change_permissions.o preview.o includes.h
	gcc -c main.c

display.o : display.c includes.h
	gcc -c display.c

create.o: display.o create.c includes.h
	gcc -c create.c

find_file.o: display.o find_file.c includes.h
	gcc -c find_file.c

change_permissions.o : display.o change_permissions.c includes.h
	gcc -c change_permissions.c

copy_paste.o : display.o copy_paste.c includes.h
	gcc -c copy_paste.c

delete.o : delete.c includes.h display.o
	gcc -c delete.c

preview.o : preview.c includes.h
	gcc -c preview.c