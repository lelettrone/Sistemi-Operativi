all: main header
	gcc -o main main.o header.o
main:
	gcc -w -c main.c
header:
	gcc -w -c header.c

clean:
	rm -f *.o
	rm -f main
