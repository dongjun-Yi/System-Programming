main: main.o  copy.o
	gcc -g -o main main.o copy.o 
main.o: main.c copy.h
	gcc -g -c main.c
copy.o: copy.c 
	gcc -g -c copy.c
