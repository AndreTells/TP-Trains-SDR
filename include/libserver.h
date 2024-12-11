#ifndef LIBSERVER_H_
#define LIBSERVER_H_
#include "comms.h"
#include "train.h"

#define MAX_TRAINS 10

typedef struct Server_t Server_t;

Message_data_t* create_server_ERR_msg();

Message_t* server_add_train(Server_t* server, Message_t* msg);
Message_t* route_messages(Server_t* server, Message_t* msg);

Server_t* init_server();

#endif // LIBSERVER_H_
