all: main procedure monitor_sc
	gcc -w -o main main.o procedure.o monitor_sc.o

main:
	gcc -w -c main.c
procedure:
	gcc -w -c procedure.c
monitor_sc:
	gcc -w -c monitor_sc.c
clean:
	rm -f *.o
	rm -f main