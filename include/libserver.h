/*
* @file
* @section DESCRIPTION
* Contains all functions required for an external program to use the server with
* as little influence / knowledge as possible regarding the server's implementation
*/
#ifndef LIBSERVER_H_
#define LIBSERVER_H_
#include "comms.h"
#include "train.h"

#define MAX_TRAINS 10

typedef struct Server_t Server_t;

Message_t* route_messages(Server_t* server, Message_t* msg);

Server_t* init_server();

#endif // LIBSERVER_H_
