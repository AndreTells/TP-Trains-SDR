#include<stdio.h>
#include "comms.h"

int send_message(Message_t* msg){
  printf("Message Sent: %d %d %d %d\n",msg->cmd_code,msg->train_id,msg->train_pos,msg->train_eoa);
  return 1;
}

Message_t* listen_message(){
  Message_t* msg = (Message_t *) malloc(sizeof(Message_t));
  msg->cmd_code = 110;
  msg->train_id = -1;
  msg->train_pos = -1;
  msg->train_eoa = -1;
  // also requires info about the ip address that connected
  return msg;
}
