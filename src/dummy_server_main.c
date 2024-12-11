#include<stdio.h>
#include<string.h>
#include"libserver.h"
#include"constants.h"

int main(void){
  // Initialize server
  printf("server initialization");
  Server_t serv;
  Train_t NULL_TRAIN ={0,-1,-1,-1,-1};

  for(int i=0; i<MAX_TRAINS; i++){
    memcpy(&(serv.trains[i]),&NULL_TRAIN, sizeof(Train_t));
    printf("train t_%d of the server created id: %d\n", i, serv.trains[i].id);
  }

  // simulate a train connecting
  Train_t train;
  memcpy(&train,&NULL_TRAIN, sizeof(Train_t));
  return 0;
}
