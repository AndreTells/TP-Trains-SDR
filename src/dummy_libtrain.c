#include<unistd.h>
#include "libtrain.h"

Train_t* create_train(struct sockaddr* host_addr, struct sockaddr* server_addr){
  Train_t* train = (Train_t*) malloc(sizeof(Train_t));
  train->addr = NULL;
  train->id = 0;
  train->pos = 1;
  train->eoa = 2;

  return train;
}

int send_position_update(Train_t* train,struct sockaddr* server_addr){
  return 0;
}

int request_limit_extension(Train_t* train, struct sockaddr* server_addr){
  sleep(2);
  return train->eoa+1;
}
