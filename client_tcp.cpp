#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 12345
#define SERVERADDR "127.0.0.1"

int main()
{
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //creating TCP stream, for Internet Protocol (IP)
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("creating socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));       //cleaning server address
    server_addr.sin_family = AF_INET;                   //inet address
    inet_aton(SERVERADDR, &server_addr.sin_addr);       //IP address of server
    server_addr.sin_port = htons(PORT);                 //port, where data will be sent

    if(
        connect(sock, 
               (struct sockaddr *)&server_addr,
               sizeof(server_addr)) < 0)
    {
        perror("connection failed");
        exit(4);
    }

    printf("reading message\n");
    read(sock, buffer, 1024);
    std::cout<<"got: "<<buffer<<std::endl;
    close(sock);

    return 0;
}
