/*
 * @file
 * @section DESCRIPTION
 * function containing all functions for a train to be used by another program
 * with as little influence as possible on the implementation of the train
*/
#ifndef TRAIN_H_
#define TRAIN_H_
#include <sys/socket.h>
#include "comms.h"


typedef struct {
  struct sockaddr* addr;
  int id;
  int pos;
  int eoa;
}Train_t;

Train_t* init_train(Message_t connection_msg);

#endif // TRAIN_H_
