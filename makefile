cc = clang

all: main

main.o: main.c
	$(cc) main.c -c 

avl.o:
	$(cc) avl.c -c

main: main.o avl.o
	$(cc) main.o avl.o -lm -o main

clean:
	rm *.o main