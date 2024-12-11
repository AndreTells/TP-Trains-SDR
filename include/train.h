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

//Train_t NULL_TRAIN ={0,0,0,0,0};

/*
Message_t* create_train_connect_msg( Train_t train, int train_position);

Message_t* create_train_disconnect_msg( Train_t train);

Message_t* create_train_update_pos_msg(Train_t train);

Message_t* create_train_mov_req_msg(Train_t train);
*/
#endif // TRAIN_H_
