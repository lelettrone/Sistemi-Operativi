all: main header
	gcc -w -o main main.o header.o -pthread

main:
	gcc -w -c main.c -pthread

header:
	gcc -w -c header.c -pthread

clean:
	rm -f *.o
	rm -f main