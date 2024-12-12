#include <unistd.h>

#include "libtrain.h"

Train_t* create_train(Host_address_t* host_addr,
                      Remote_address_t* server_addr) {
  host_addr = NULL;
  server_addr = NULL;

  Train_t* train = (Train_t*)malloc(sizeof(Train_t));
  train->addr = NULL;
  train->id = 0;
  train->pos = 1;
  train->eoa = 2;

  return train;
}

int send_position_update(Train_t* train, struct sockaddr* server_addr) {
  train = NULL;
  server_addr = NULL;
  return 0;
}

int request_limit_extension(Train_t* train, struct sockaddr* server_addr) {
  server_addr = NULL;
  sleep(2);
  return train->eoa + 1;
}
