#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "comms.h"

int send_message(Message_t* msg){
  printf("Message Sent: %d\n",msg->data.cmd_code);
  return 1;
}

Message_t* listen_message(){
  Message_t* msg = (Message_t *) malloc(sizeof(Message_t));
  msg->data.cmd_code = 110;
  // also requires info about the ip address that connected
  return msg;
}


Message_t* package_message_data(struct sockaddr* host_addr,
                                struct sockaddr* target_addr,
                                Message_data_t* data){
  Message_t* msg = (Message_t*) malloc(sizeof(Message_t));
  msg->host_addr = host_addr;
  msg->target_addr = target_addr;

  memcpy(&(msg->data), data, sizeof(Message_data_t));

  return msg;
}
