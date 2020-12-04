#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  unsigned int port;
  char message[1024];
  int server_socket, client_socket;
  struct sockaddr_in server_address, sender;
  socklen_t length = sizeof(struct sockaddr_in);

  printf("Which port should I listen to : ");
  scanf("%u", &port);
  server_socket = socket(PF_INET, SOCK_STREAM, 0);
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_socket, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0)
  {
    printf("Bind failed.\n");
    return 1;
  }
  if (listen(server_socket, 10) < 0)
  {
    printf("Listen failed.\n");
    return 1;
  }
  printf("Waiting for connection...\n");

  if ((client_socket = accept(server_socket,
                         (struct sockaddr *)&sender,
                         &length)) < 0)
  {
    printf("Connection error\n");
  }
  int exit_status = 0;
  while (exit_status == 0)
  {

    memset(message, 0, 1024);
    recv(client_socket, message, 1024, 0);
    if (strncmp("exit", message, 4) == 0)
    {
      printf("Server exit...\n");
      exit_status = 1;
    }
    else
    {
      printf("Message from %s: %s\n",
             inet_ntoa(sender.sin_addr),
             message);
    }
  }
  close(client_socket);
  close(server_socket);
  return 0;
}
