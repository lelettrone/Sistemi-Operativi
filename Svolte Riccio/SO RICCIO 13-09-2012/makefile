all: main.o procedure.o monitor_sc.o
	gcc -w -o main main.o procedure.o monitor_sc.o

main.o:
	gcc -c main.c 
procedure.o:
	gcc -c procedure.c
monitor_sc.o:
	gcc -c monitor_sc.c

clean:
	rm -f *.o
	rm -f main