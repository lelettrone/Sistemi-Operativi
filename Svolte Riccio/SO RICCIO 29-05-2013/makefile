all: main server client
	
main:
	gcc -w -o main main.c -pthread
server:
	gcc -w -o server server.c -pthread
client:
	gcc -w -o client client.c -pthread

clean:
	rm -f main
	rm -f client
	rm -f server
	rm -f *.o