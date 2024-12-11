#include <stdio.h>
#include <stdlib.h>
#include "libserver.h"
#include "constants.h"
#include "comms.h"
#include "train.h"

#define MAX_TRAINS 10

struct Server_t {
  Train_t trains[MAX_TRAINS];
  int start;
  int next;
};

Message_t* server_add_train(Server_t* server, Message_t* msg);

Message_data_t* create_server_ERR_msg(){
  Message_data_t* data = (Message_data_t*) malloc(sizeof(Message_data_t));
  data->cmd_code = SERVER_ACK_ERROR;

  return data;
}

Message_t* route_messages(Server_t* server, Message_t* msg){
  Message_t* response = package_message_data(
                         msg->target_addr,
                         msg->host_addr,
                         create_server_ERR_msg());

  switch(msg->data.cmd_code){
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

Message_t* server_add_train(Server_t* server, Message_t* msg){
  // TODO create pop for the buffer
  Data_full_train_t response;
  response.cmd_code = SERVER_ACK_SUCCESS;
  int i = server->next;
  server->next++;

  server->trains[i].addr = msg->host_addr;

  server->trains[i].id = i;
  response.id = i;

  server->trains[i].pos = TRAIN_START_POS;
  response.pos = TRAIN_START_POS;

  if(i == server->start){
    server->trains[i].eoa = TRAIN_END_POS;
    response.eoa = TRAIN_END_POS;
  }
  else{
    // get previous train and set this train's eoa to that train's position
    //train.eoa = ;
  }
  return package_message_data(
                         msg->target_addr,
                         msg->host_addr,
                         (Message_data_t*)&response);
}

Server_t* init_server(){
  Server_t* serv = (Server_t*) malloc(sizeof(Server_t));
  serv->start=0;
  serv->next=0;

  Train_t NULL_TRAIN ={0,-1,-1,-1};
  for(int i=0; i<MAX_TRAINS; i++){
    serv->trains[i] = NULL_TRAIN;
    printf("train t_%d of the server created id: %d\n", i, serv->trains[i].id);
  }

  return serv;
}
