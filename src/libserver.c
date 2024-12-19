#include "libserver.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comms.h"
#include "constants.h"
#include "libtrain.h"

#define MAX_TRAINS 10

struct Server_t {
  int start;
  int top;
  Train_t trains[MAX_TRAINS];
};

// declaring functions
Message_t* server_add_train(Server_t* server, Message_t* msg);

Message_t* server_remove_train(Server_t* server, Message_t* msg);

Message_t* server_update_pos(Server_t* server, Message_t* msg);

Message_t* server_req_lim_extension_pos(Server_t* server, Message_t* msg);

// implementations
Train_t get_top(Server_t* server) { return server->trains[server->top]; }

int get_next(int train_id) {
  int next_train_id = train_id + 1 % MAX_TRAINS;
  return next_train_id;
}

int get_prev(int train_id) {
  int prev_train_id = (train_id - 1);
  if (prev_train_id < 0){
    prev_train_id = MAX_TRAINS - 1;
  }

  return prev_train_id;
}

int calculate_train_eoa(Server_t* server, int train_id) {
  int eoa = TRAIN_END_POS;
  if (train_id != server->start) {
    int id_prev_train = get_prev(train_id);
    eoa = server->trains[id_prev_train].eoa;
  }
  return eoa;
}

Message_data_t* create_server_ERR_msg() {
  Message_data_t* data = (Message_data_t*)malloc(sizeof(Message_data_t));
  data->cmd_code = SERVER_ACK_ERROR;

  return data;
}

Message_data_t* create_server_SUC_msg() {
  Message_data_t* data = (Message_data_t*)malloc(sizeof(Message_data_t));
  data->cmd_code = SERVER_ACK_SUCCESS;

  return data;
}

Message_t* route_messages(Server_t* server, Message_t* msg) {
  Message_t* response = package_message_data(
                           (Host_address_t*)&(msg->target_addr),
                           (Remote_address_t*)&(msg->host_addr),
                           create_server_ERR_msg());

  switch (msg->data.cmd_code) {
    case TRAIN_CONNECT_CMD:
      response = server_add_train(server, msg);
      break;

    case TRAIN_DISCONECT_CMD:
      response = server_remove_train(server, msg);
      break;

    case TRAIN_UPDATE_POS_CMD:
      response = server_update_pos(server, msg);
      break;

    case TRAIN_REQ_LIM_EXTENSION_CMD:
      response = server_req_lim_extension_pos(server, msg);
      break;

    case INFO_REQ_CMD:
      break;
  }

  return response;
}

Message_t* server_add_train(Server_t* server, Message_t* msg) {
  // check if buffer is full
  if (server->start == get_next(server->top)) {
    Message_t* response = package_message_data(
                              (Host_address_t*)&(msg->target_addr),
                              (Remote_address_t*)&(msg->host_addr),
                              create_server_ERR_msg());
    return response;
  }

  // effectively adding train to buffer
  Train_t train;

  memcpy(train.addr,msg->host_addr,LEN_IPV4);
  server->top = get_next(server->top);

  train.pos = TRAIN_START_POS;
  train.eoa = calculate_train_eoa(server, train.id);

  // creating response
  Data_full_train_t response;
  response.id = train.id;
  response.pos = train.pos;
  response.eoa = train.eoa;
  response.cmd_code = SERVER_ACK_SUCCESS;

  Message_t* response_msg = package_message_data(
      (Host_address_t*)&(msg->target_addr),
      (Remote_address_t*)&(msg->host_addr),
      (Message_data_t*)&response);
  return response_msg;
}

Message_t* server_remove_train(Server_t* server, Message_t* msg) {
  // check if buffer is emtpy
  if (server->start == server->top) {
    Message_t* response = package_message_data(
                            (Host_address_t*)&(msg->target_addr),
                            (Remote_address_t*)&(msg->host_addr),
                            create_server_ERR_msg());
    return response;
  }
  Message_t* response_msg =
      package_message_data(
         (Host_address_t*)&(server->trains[server->start].addr),
         (Remote_address_t*)&(msg->host_addr),
         create_server_SUC_msg());
  server->start = get_next(server->start);

  return response_msg;
}

Message_t* server_update_pos(Server_t* server, Message_t* msg) {
  Data_pos_t* data = (Data_pos_t*)&(msg->data);

  server->trains[data->id].pos = data->pos;

  Message_t* response_msg = package_message_data(
      (Host_address_t*)&(server->trains[data->id].addr),
      (Remote_address_t*)&(msg->host_addr),
      create_server_SUC_msg());
  return response_msg;
}

Message_t* server_req_lim_extension_pos(Server_t* server, Message_t* msg) {
  Data_eoa_t* data = (Data_eoa_t*)&(msg->data);

  server->trains[data->id].eoa = calculate_train_eoa(server, data->id);
  data->eoa = server->trains[data->id].eoa;

  Message_t* response_msg = package_message_data(
      (Host_address_t*)&(server->trains[data->id].addr),
      (Remote_address_t*)&(msg->host_addr),
      (Message_data_t*)data);
  return response_msg;
}

Server_t* init_server() {
  Server_t* serv = (Server_t*)malloc(sizeof(Server_t));
  serv->start = 0;
  serv->top = -1;

  Train_t NULL_TRAIN = {{0}, -1, -1, -1};
  for (int i = 0; i < MAX_TRAINS; i++) {
    serv->trains[i] = NULL_TRAIN;
  }

  return serv;
}

void print_server_state(Server_t* server){
  printf("+-----+-----+\n");
  for(int i=server->start; i<=server->top; i = get_next(i)){
    printf("| %03d | %03d | %03d |\n",server->trains[i].id ,server->trains[i].pos, server->trains[i].eoa);
  }
  printf("+-----+-----+\n");
}
