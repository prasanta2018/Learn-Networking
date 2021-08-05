#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char* argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char* message;
    char server_reply[10000];
    
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    printf("AF_INET=%d\n",AF_INET);

    if(socket_desc == -1)
        printf("Couldn't create socket\n");
    else
        printf("Successfully created a socket with sockid=%d\n", socket_desc);
    
    server.sin_addr.s_addr = inet_addr("142.251.32.238");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );

    // connect to remote server
    if(connect(socket_desc, (struct sockaddr *)&server , sizeof(server)) < 0 )
    {
        puts("connect error");
        return 1;
    }

    puts("connected");

    // send some data
    message = "GET / HTTP/1.1\r\n\r\n";
    if(send(socket_desc, message, strlen(message), 0) < 0)
    {
        puts("Send Failed");
        return 1;
    }
    puts("Data Send\n");

    // receive a reply from the server
    if(recv(socket_desc, server_reply, 10000, 0) < 0)
    {
        puts("recv failed");
    }
    puts("Reply received");
    puts(server_reply);

    close(socket_desc);
    
    return 0;

}