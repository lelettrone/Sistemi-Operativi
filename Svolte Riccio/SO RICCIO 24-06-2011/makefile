all: main.o	procedure.o monitor_hoare.o
	gcc -w -o main main.o procedure.o monitor_hoare.o

main.o:
	gcc -w -c main.c

procedure.o:
	gcc -w -c procedure.c

monitor_hoare.o:
	gcc -w -c monitor_hoare.c

clean:
	rm -f main
	rm -f *.o