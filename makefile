cc = clang++

all: main test

main.o: main.c
	$(cc) main.c -c 

avl.o:
	$(cc) avl.c -c

main: main.o avl.o
	$(cc) main.o avl.o -lm -o main

test.o:
	$(cc) test/test.cc -c

test: test.o avl.o
	$(cc) test.o avl.o -lgtest -lgtest_main -lm -o test_avl

clean:
	rm *.o main test_avl