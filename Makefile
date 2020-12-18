mserv: multithread_server.c
	gcc -pthread -o multithread_server.o multithread_server.c

my_client: my_client.c
	gcc -o my_client.o my_client.c


mstuff: mserv my_client

clean:
	rm -rf *.o 