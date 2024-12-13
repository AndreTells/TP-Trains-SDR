#include "comms.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define LEN_IPV4 32

int send_message(int socket_fd, Message_t* msg) {
  // we also can test use the flag MSG_CONFIRM to have a confirmation

  if (sendto(socket_fd, msg, sizeof(*msg), 0, &(msg->target_addr), LEN_IPV4) < 0) {
    perror("Its impossible to send the message\n");
    return -1;
  }

  return 0;
}

Message_t* listen_message(int socket_fd) {
  Message_t* msg = (Message_t*)malloc(sizeof(Message_t));
  socklen_t addr_len=0;

  if (!msg) {
    perror("Erro ao alocar memória para mensagem");
    exit(-1);
  }

  // Receber mensagem do servidor
  if (recvfrom(socket_fd, msg, sizeof(*msg), 0, NULL, &addr_len) < 0) {
    perror("Erro ao receber mensagem");
    free(msg);
    exit(-1);
  }

  return msg;
}

Message_t* package_message_data(Host_address_t* host_addr,
                                Remote_address_t* target_addr,
                                Message_data_t* data) {
  // TODO(André) make a check on the Message_data
  Message_t* msg = (Message_t*)malloc(sizeof(Message_t));

  memcpy(&(msg->host_addr), host_addr, sizeof(struct sockaddr));
  memcpy(&(msg->target_addr), target_addr, sizeof(struct sockaddr));

  memcpy(&(msg->data), data, sizeof(Message_data_t));

  return msg;
}
