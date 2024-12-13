/*
 * @file
 * @section DESCRIPTION
 * function containing all functions for a train to be used by another program
 * with as little influence as possible on the implementation of the train
 */
#ifndef LIBTRAIN_H_
#define LIBTRAIN_H_
#include <sys/socket.h>

#include "comms.h"

typedef struct {
  char addr[LEN_IPV4];
  int id;
  int pos;
  int eoa;
} Train_t;

/* @brief connects host to server and returns the new train
 * @return the created train
 */
Train_t* create_train(Host_address_t* host_addr, Remote_address_t* server_addr);

/* @brief send the server the host train's position
 * @param train the local host's train with the position changed
 * @param server_addr the server that'll be notified of the change
 * @return 0 if no errors have happened and -1 otherwise
 */
int send_position_update(Train_t* train, struct sockaddr* server_addr);

/* @brief request's the server that the host's train eoa be extended
 * @param train the local host's train
 * @param server_addr the server that'll be notified of the request
 * @return new_eoa the extended eoa returned by the server or -1 if an error has
 * happened
 */
int request_eoa_extension(Train_t* train, struct sockaddr* server_addr);

#endif  // TRAIN_H_
