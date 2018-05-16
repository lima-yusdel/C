all: my_malloc.h memgrind.c my_malloc.o
	gcc memgrind.c my_malloc.o

my_malloc.o: my_malloc.c my_malloc.h
	gcc -c my_malloc.c

clean:
	rm a.out my_malloc.o