#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <unistd.h>

int main()
{
	char message[256];


	// prompt user to input the port number
	unsigned int port;
	printf("Which port should I listen to? : ");
	scanf("%u", &port);

	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = INADDR_ANY;

	//bind the socket
	int bind_status = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

	//bind check
	if(bind_status < 0)
	{
		printf("Bind failed");
		return 1;
	}

	// start to listen
	int listen_status = listen(server_socket, 10);

	if(listen_status < 0)
	{
		printf("Listen failed");
		return 1;
	}

	printf("Waiting for connection...\n");

	//accepting connection
	struct sockaddr_in client_address;
	socklen_t client_address_length = sizeof(struct sockaddr_in);
	int client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_length);



	while(1)
	{
		bzero(message, 256);

		//read the message from client and copy to buffer
		recv(server_socket, message, sizeof(message), 0);
		printf("From client: %s", message);
		if (strncmp("exit", message, 4) == 0)
		{
			printf("Server exit...\n");
			break;
		}
	}


	close(server_socket);

	return 0;
}
