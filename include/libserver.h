#ifndef LIBSERVER_H_
#define LIBSERVER_H_
#include "comms.h"
#include "train.h"

#define MAX_TRAINS 10

typedef struct {
  Train_t trains[MAX_TRAINS];
} Server_t;

enum Server_result_e {
  SERVER_SUCCESS,
  SERVER_ERR
};

Message_t* create_server_ACK_msg(Train_t train, enum Server_result_e res);

#endif // LIBSERVER_H_
