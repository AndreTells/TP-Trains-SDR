#include<stdio.h>
#include "comms.h"

int send_message(Message_t* msg){
  printf("%d %d %d %d\n",msg->cmd_code,msg->train_id,msg->train_pos,msg->train_eoa);
  return 1;
}
