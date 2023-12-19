all: main monitor procedure
	gcc -w -o main main.o monitor_signal_continue.o procedure.o
main:
	gcc -w -c main.c

monitor:
	gcc -w -c monitor_signal_continue.c

procedure:
	gcc -w -c procedure.c

clean:
	rm -f *.o
	rm -f main