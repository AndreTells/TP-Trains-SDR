#include <stdio.h>
#include <stdlib.h>
#include "libserver.h"
#include "constants.h"
#define MAX_TRAINS 10

Train_t NULL_TRAIN ={0,-1,-1,-1,-1};

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

Message_t* route_messages(Server_t server, Message_t* msg){
  Message_t* response = create_server_ACK_msg(NULL_TRAIN, SERVER_ERR);

  switch(msg->cmd_code){
    case TRAIN_CONNECT_CMD:
      response = server_add_train(server, msg);
      break;
    case TRAIN_DISCONECT_CMD:
      printf("not implemented");
      break;
    case TRAIN_UPDATE_POS_CMD:
      printf("not implemented");
      break;
    case TRAIN_REQ_LIM_EXTENSION_CMD:
      printf("not implemented");
      break;
    case INFO_REQ_CMD:
      printf("not implemented");
      break;
  }

  return response;
}

Message_t* server_add_train(Server_t server, Message_t* msg){
  // TODO create pop for the buffer
  int i = server.next;
  server.next++;

  server.trains[i].id = i;

  server.trains[i].pos = TRAIN_START_POS;

  if(i == server.start){
    server.trains[i].eoa = TRAIN_END_POS;
  }
  else{
    // get previous train and set this train's eoa to that train's position
    //train.eoa = ;
  }

  return create_server_ACK_msg(server.trains[i],SERVER_SUCCESS);
}
