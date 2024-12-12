/*
* @file
* @section DESCRIPTION
* Contains all functions required for an external program to use the server with
* as little influence / knowledge as possible regarding the server's implementation
*/
#ifndef LIBSERVER_H_
#define LIBSERVER_H_
#include "comms.h"
#include "libtrain.h"

#define MAX_TRAINS 10

/*
 * @struct Server_t
 * @brief contains all information about a server, but cannot be accessed
 * directly by any external code
*/
typedef struct Server_t Server_t;

/*
 * @brief given a message and a server, returns the message this server should
 * send as a response
 * @param server the server that should interpret the message
 * @param msg the message that should be interpreted
 * @return response the server's response
*/
Message_t* route_messages(Server_t* server, Message_t* msg);

/*
 * @brief create a server object
 * @return a new server
*/
Server_t* init_server();

#endif // LIBSERVER_H_
