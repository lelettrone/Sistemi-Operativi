all: procedure main  produttore consumatore

main: 
	gcc -c main.c
	gcc -o main main.o procedure.o
produttore: 
	gcc -c produttore.c
	gcc -o produttore produttore.o procedure.o
consumatore: 
	gcc -c consumatore.c
	gcc -o consumatore consumatore.o procedure.o
procedure:
	gcc -c procedure.c
clean:
	rm -f main
	rm -f produttore
	rm -f consumatore
	rm -f *.o