all: main procedure monitor_sc
	gcc -w -o main main.o procedure.o monitor_sc.o
main:
	gcc  -c main.c
procedure:
	gcc  -c procedure.c
monitor_sc:
	gcc  -c monitor_sc.c
clean:
	rm -f main
	rm -f *.o