
all: main prodcons
	gcc -o main main.o prodcons.o -pthread
main:
	gcc -c main.c -pthread
prodcons:
	gcc -c prodcons.c -pthread
clean:
	rm -f *.o
	rm -f main