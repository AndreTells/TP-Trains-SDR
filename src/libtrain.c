#include <unistd.h>
#include <string.h>

#include "libtrain.h"
#include "comms.h"



Train_t* create_train(Host_address_t* host_addr,
                      Remote_address_t* server_addr) {
  host_addr = NULL;
  server_addr = NULL;

  Train_t* train = (Train_t*)malloc(sizeof(Train_t));

  strcpy(train->addr,"");
  train->id = -1;
  train->pos = -1;
  train->eoa = 0;

  return train;
}

void show_train(Train_t *train){

  printf("ID train : %d\n", train->id);
  printf("Pos train %d : %d\n", train->id, train->pos);
  printf("Eoa train %d : %d\n", train->id, train->eoa);

}

int send_position_update(Train_t* train, struct sockaddr* server_addr) {
  train = NULL;
  server_addr = NULL;

  // add send_message

  return 0;
}

int request_limit_extension(Train_t* train, struct sockaddr* server_addr) {
  server_addr = NULL;
  sleep(2);
  return train->eoa + 1;
}
