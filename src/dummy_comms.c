#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "comms.h"

#define LEN_IPV4 32



int send_message(int socket_fd, Message_t* msg){

  printf("Message sent: %d", msg->data.cmd_code);
  free(msg);

  return 0;
}

Message_t* listen_message(int socket_fd) {

    Message_t* msg = (Message_t*)malloc(sizeof(Message_t));
    msg->data.cmd_code = TRAIN_CONNECT_CMD;

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


