cc = clang

all: main

main.o: main.c
	$(cc) main.c -c -g -gdwarf-4

avl.o:
	$(cc) avl.c -c -g -gdwarf-4 

main: main.o avl.o
	$(cc) -g -gdwarf-4 main.o avl.o -lm -o main

clean:
	rm *.o