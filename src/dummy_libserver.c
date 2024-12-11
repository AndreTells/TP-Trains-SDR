#include <stdlib.h>
#include "libserver.h"
#define MAX_TRAINS 10

Message_t* create_server_ACK_msg(Train_t train, enum Server_result_e res){
  Message_t* msg = (Message_t*) malloc(sizeof(Message_t));

  if(res == SERVER_SUCCESS){
    msg->cmd_code = SERVER_ACK_SUCCESS;
  }
  else{
    msg->cmd_code = SERVER_ACK_ERROR;
  }

  msg->train_id = train.id;
  msg->train_pos = train.pos;
  msg->train_eoa = train.eoa;
  return msg;
}
