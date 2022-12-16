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
//#define SERVERADDR "192.168.1.34"

int main()
{
    std::cout<<"Give IP of a server: ";
    std::string ip_address_string;
    std::cin>>ip_address_string;
    const char * ip_address_char = ip_address_string.c_str();
    
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    //utworzenie strumienia STREAM(TCP) dla protokołu IP
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("creating socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));       //wyczyszczenie adresu serwera
    server_addr.sin_family = AF_INET;                   //adres inet
    inet_aton(ip_address_char, &server_addr.sin_addr);       //adres ip servera
    server_addr.sin_port = htons(PORT);                 //port na ktory beda wysylane dane

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
