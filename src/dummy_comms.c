#include<stdlib.h>
#include<stdio.h>
#include "comms.h"

int send_message(Message_t* msg){
  printf("Message Sent: %d\n",msg->cmd_code);
  return 1;
}


Message_t* listen_message(){
  Message_t* msg = (Message_t *) malloc(sizeof(Message_t));
  msg->cmd_code = 110;
  // also requires info about the ip address that connected
  return msg;
}
