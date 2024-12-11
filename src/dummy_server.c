#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libserver.h"

int main(void){
  // Initialize server
  printf("server initialization");
  Server_t serv;
  serv.start=0;
  serv.next=0;

  Train_t NULL_TRAIN ={0,-1,-1,-1,-1};
  for(int i=0; i<MAX_TRAINS; i++){
    memcpy(&(serv.trains[i]),&NULL_TRAIN, sizeof(Train_t));
    printf("train t_%d of the server created id: %d\n", i, serv.trains[i].id);
  }

  // simulate a train connecting

  // loop
  Message_test_t test = {1, 2};

  Message_t* msg = listen_message();

  Message_t* response = route_messages(serv, msg);

  memcpy(response->data, &test, sizeof(Message_test_t));
  send_message(response);
  printf("%d", ((Message_test_t *) response->data)->value);
  return 0;
}
