#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "comms.h"

int send_message(Message_t* msg, int socket_client,const struct sockaddr *server_address,socklen_t server_addrlen){
// we also can test use the flag MSG_CONFIRM to have a confirmation
  if(sendto(socket_client, msg, sizeof(*msg), 0,server_address, server_addrlen)<0){
    perror("Its impossible to send the message\n");
    return -1;
  }

  return 0;
}

Message_t* listen_message(int client_socket, struct sockaddr_in* server_addr, socklen_t* addr_len) {

    Message_t* msg = (Message_t*)malloc(sizeof(Message_t));

    if (!msg) {
        perror("Erro ao alocar memória para mensagem");
        exit(-1);
    }

    // Receber mensagem do servidor
   if(recvfrom(client_socket, msg, sizeof(*msg), 0,(struct sockaddr*)server_addr, addr_len) < 0){
        perror("Erro ao receber mensagem");
        free(msg);
        exit(-1);
    }

    return msg;
}

