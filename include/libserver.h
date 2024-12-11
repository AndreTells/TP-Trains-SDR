#ifndef LIBSERVER_H_
#define LIBSERVER_H_
#include "comms.h"
#include "train.h"

#define MAX_TRAINS 10

typedef struct {
  Train_t trains[MAX_TRAINS];
  int start;
  int next;
} Server_t;

enum Server_result_e {
  SERVER_SUCCESS,
  SERVER_ERR
};

Message_t* create_server_ACK_msg(Train_t train, enum Server_result_e res);

Message_t* server_add_train(Server_t server, Message_t* msg);
Message_t* route_messages(Server_t server, Message_t* msg);

#endif // LIBSERVER_H_
