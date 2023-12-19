all: main procedure
	gcc -w -o main main.o procedure.o -pthread

main:
	gcc -c main.c -pthread
procedure:
	gcc -c procedure.c -pthread
clean:
	rm -f *.o
	rm -f main