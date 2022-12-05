#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORTNR 12345
#define MYMSG "MESSAGE 123"

int main()
{
    int sock;
    int conn;
    int clilen;
    
    // czy ponizsza definicja struktury jest poprawna ?
    struct sockaddr_in server_addr, client_addr;

    // Utowrzenie strumienia STREAM [TCP] z uzyciem gniazda dla protokolu (IP)
    sock = socket(PF_INET,SOCK_STREAM,0);   // 0 to protokul IP ?
    
    if(sock < 0){
        perror("creating socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNR);

    if(bind(sock,(struct sockaddr *) &server_addr,
        sizeof(server_addr)) < 0){
            perror("bind failed");
            exit(2);
        }

    if(listen(sock,5) < 0){
        perror("listen failed");    // tutaj wywala blad ; zle podalem argument po znaku mniejszosci, mialo byc 0 a nie 5
        exit(3);
    }

    while(1){
        printf("waiting for a connection ... \n");
        clilen = sizeof(client_addr);
        conn = accept(sock,(struct sockaddr *) &client_addr, (socklen_t *) &clilen);

        if(conn < 0){
            perror("accept failed");
            exit(4);
        }
        printf("connection from %s\n",inet_ntoa(client_addr.sin_addr));
        printf("sending message ...\n");
        write(conn, MYMSG, sizeof(MYMSG));

        close(conn);
    }
    return 0;
}