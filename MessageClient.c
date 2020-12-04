#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char abcd[512];
	char message[1024];
	struct sockaddr_in client_address;
	unsigned int port;
	int client_socket;

	printf("Please provide the server IP: ");
	scanf("%s", abcd);
	printf("Please provide the port number: ");
	scanf("%u", &port);
	client_socket = socket(PF_INET, SOCK_STREAM, 0);
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(port);
	client_address.sin_addr.s_addr = inet_addr(abcd);
	if (connect(client_socket, (struct sockaddr *)&client_address,
				sizeof(client_address)) < 0)
	{
		printf("Connection failed.\n");
		return 1;
	}
	printf("Connected\n");
	fgetc(stdin);

	while (1)
	{
		printf("Enter message: ");
		fflush(stdout);
		fgets(message, 1024, stdin);
		if (strncmp("exit", message, 4) == 0)
		{
			send(client_socket, message, strlen(message), 0);
			printf("Client exit...\n");
			break;
		}
		send(client_socket, message, strlen(message), 0);
		printf("message sent\n");
	}

	close(client_socket);
	return 0;
}
