#include <stdio.h>
#include <stdlib.h>

#include "comms.h"
#include "libserver.h"

#define MAX_TRAINS 10

struct Server_t {
  Train_t trains[MAX_TRAINS];
  int start;
  int next;
};

Message_data_t* create_server_ERR_msg() {
  Message_data_t* data = (Message_data_t*)malloc(sizeof(Message_data_t));
  data->cmd_code = SERVER_ACK_ERROR;

  return data;
}

Message_t* route_messages(Server_t* server, Message_t* msg) {
  Message_t* response = package_message_data(msg->target_addr, msg->host_addr,
                                             create_server_ERR_msg());

  return response;
}

Server_t* init_server() {
  Server_t* serv = (Server_t*)malloc(sizeof(Server_t));
  serv->start = 0;
  serv->next = 0;

  Train_t NULL_TRAIN = {0, -1, -1, -1};
  for (int i = 0; i < MAX_TRAINS; i++) {
    serv->trains[i] = NULL_TRAIN;
    printf("train t_%d of the server created id: %d\n", i, serv->trains[i].id);
  }

  return serv;
}
