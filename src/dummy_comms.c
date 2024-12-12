#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "comms.h"

#define LEN_IPV4 32

int send_message(int socket_fd, Message_t* msg) {
  printf("[Message Sent] Message code: %d socket fd: %d", msg->data.cmd_code, socket_fd);
  free(msg);

  return 0;
}

Message_t* listen_message(int socket_fd) {
  printf("[Message Received] socket fd: %d",socket_fd);
  Message_t* msg = (Message_t*)malloc(sizeof(Message_t));
  msg->data.cmd_code = TRAIN_CONNECT_CMD;

  return msg;
}

Message_t* package_message_data(Host_address_t* host_addr,
                                Remote_address_t* target_addr,
                                Message_data_t* data) {

  Message_t* msg = (Message_t*)malloc(sizeof(Message_t));
  msg->host_addr = (struct sockaddr*) host_addr;
  msg->target_addr = (struct sockaddr*) target_addr;

  memcpy(&(msg->data), data, sizeof(Message_data_t));

  return msg;
}
