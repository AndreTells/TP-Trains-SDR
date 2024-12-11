
/*
====================================================================

          SIMPLE CODE ABOUT UDP CLIENT USING SOCKET         

====================================================================
*/


#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>

#include <string.h>

int main(int argv, char *argc[]){

    // create buffer
    char server_message[2000], client_message[2000] = "Olá";

    // create a socket
    int server_socket;
    server_socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

     if(server_socket < 0){
        printf("Error while creating socket\n");
        return -1;
    }

    // specify an address for the server socket

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);                         // mudar porta ? Acho que n
    server_addr.sin_addr.s_addr = INADDR_ANY;                   // mudar isso
    //server_addr.sin_addr.s_addr = inet_addr("192.168.1.0");   //       pra isso na rede da sala ?
    
    
    int server_struct_length = sizeof(server_addr);
    

    // Get input from the user:

    // Send the message to server:
    if(sendto(server_socket, client_message, strlen(client_message), 0,(struct sockaddr*)&server_addr, server_struct_length) < 0){
        printf("Unable to send message\n");
        return -1;
    }
    
    // Receive the server's response:
    if(recvfrom(server_socket, server_message, sizeof(server_message), 0,(struct sockaddr*)&server_addr, (socklen_t*)&server_struct_length) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }

    // print off the server's response

    printf("The server sent the data: %s \n", server_message);
    close(server_socket);

    return 0;
}
