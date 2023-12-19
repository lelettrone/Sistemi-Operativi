all: main procedure
	gcc -w -o main main.o procedure.o -pthread

main: main.c header.h
	gcc -w -c main.c -pthread

procedure:	procedure.c header.h
	gcc -w -c procedure.c -pthread

clean:
	rm -f *.o
	rm -f main