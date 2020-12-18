#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <netdb.h>

#define SERVERPORT 8989

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

int main(void)
{
    int client_socket;
    SA_IN client_address;
    //int port;
    struct hostent *h;
    char host_name[512];
    char message[BUFSIZ];
    //char *mes = NULL;
    //size_t len = 512;
    //char buffer[1024];
    long file_length, recieved, recieved_total;
    int file_size;
    ssize_t len;
    int remain_data = 0;

    FILE *recieved_file;

    printf("Provide host address: ");
    scanf("%s", host_name);
    h = gethostbyname(host_name);
    if (h == NULL)
    {
        printf("Unknown host\n");
        return 1;
    }

    //printf("Port number: ");
    //scanf("%d", &port);
    client_socket = socket(PF_INET, SOCK_STREAM, 0);
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(SERVERPORT);
    client_address.sin_addr.s_addr = *((unsigned long *)(h)->h_addr_list[0]);

    if (connect(client_socket, (struct sockaddr *)&client_address,
                sizeof(client_address)) < 0)
    {
        printf("Connection failed.\n");
        return 1;
    }
    printf("Connected\n");
    fgetc(stdin);

    printf(">>");
    //scanf("%s", message);
    //getline(&mes,&len, stdin);
    fgets(message, BUFSIZ, stdin);

    if (send(client_socket, message, strlen(message), 0) != strlen(message))
    {
        printf("Error. Message was not sent\n");
        close(client_socket);
        return 1;
    }

    printf("Message sent.\n");

    /*bzero(message, BUFSIZ);
    recv(client_socket, message, BUFSIZ, 0);

    file_size = atoi(message);
    recieved_file = fopen("DUMMY_RECIEVED.TXT", "w");
    if(recieved_file == NULL)
    {
        printf("Failed to open file\n");
        close(client_socket);
        return 1;
    }

    remain_data = file_size;

    while((remain_data > 0) && ((len = recv(client_socket, message, BUFSIZ, 0)) > 0))
    {
        fwrite(buffer, sizeof(char), len, recieved_file);
        remain_data -= len;
        printf("Receive %ld bytes and we hope :- %d bytes\n", len, remain_data);
    }
    
    fclose(recieved_file);
    close(client_socket);*/

    if (recv(client_socket, &file_length, sizeof(long), 0) != sizeof(long))
    {
        printf("Error. File length was not recieved\n");
        close(client_socket);
        return 1;
    }

    file_length = ntohl(file_length);
    printf("File length: %ld\n", file_length);

    FILE *fptr;
    fptr = fopen("dummy_recieved.txt", "w");
    char buffer[BUFSIZ];
    int n;

    recieved_total = 0;

    //bzero(message, BUFSIZ);
    while (recieved_total < file_length)
    {
        bzero(buffer, BUFSIZ);
        recieved = recv(client_socket, buffer, BUFSIZ, 0);
        if(recieved < 0)
            break;
        recieved_total += recieved;
        fputs(buffer, fptr);
    }

   

    fclose(fptr);
    close(client_socket);

    printf("ay ay captain\n");
}