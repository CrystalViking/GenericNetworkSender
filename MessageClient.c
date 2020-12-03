#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
	char abcd[512];
	char message[256];

	struct sockaddr_in client_address;
	unsigned int port;
	int client_socket;
	int n = 0;

	printf("Please, provide the server IP: ");
	scanf("%s", abcd);
	printf("Please, provide the port address: ");
	scanf("%u", &port);
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(port);
	client_address.sin_addr.s_addr = inet_addr(abcd);

	int connect_status = (client_socket, (struct sockaddr*) &client_address, sizeof(client_address));

	if(connect_status < 0)
	{
		printf("Connect failed\n");
		return 1;
	}
	else
	{
		printf("Connected to the server...\n");
	}

	while(1)
	{
		bzero(message, sizeof(message));
		printf("Enter the message: ");
		n = 0;
		fflush(stdout); fgetc(stdin);
		//while((message[n++] = getchar()) != '\n');
		send(client_socket, message, strlen(message),0);

		if ((strncmp(message, "exit", 4)) == 0) {
			printf("Client exit...\n");
			break;
		}
	}

	close(client_socket);
	return 0;
}

