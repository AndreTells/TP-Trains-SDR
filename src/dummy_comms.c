#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comms.h"

#define LEN_IPV4 32



int send_message(int socket_fd, Message_t* msg){
  // we also can test use the flag MSG_CONFIRM to have a confirmation
  if(sendto(socket_fd, msg, sizeof(*msg), 0,msg->target_addr, LEN_IPV4)<0){
    perror("Its impossible to send the message\n");
    return -1;
  }

  return 0;
}

Message_t* listen_message(int socket_fd) {

    Message_t* msg = (Message_t*)malloc(sizeof(Message_t));
    socklen_t addr_len;

    if (!msg) {
        perror("Erro ao alocar memória para mensagem");
        exit(-1);
    }

    // Receber mensagem do servidor
   if(recvfrom(socket_fd, msg, sizeof(*msg), 0, NULL, &addr_len) < 0){
        perror("Erro ao receber mensagem");
        free(msg);
        exit(-1);
    }

    return msg;
}

Message_t* package_message_data(struct sockaddr* host_addr,
                                struct sockaddr* target_addr,
                                Message_data_t* data){
  //TODO make a check on the Message_data
  Message_t* msg = (Message_t*) malloc(sizeof(Message_t));
  msg->host_addr = host_addr;
  msg->target_addr = target_addr;

  memcpy(&(msg->data), data, sizeof(Message_data_t));

  return msg;
}


