#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libserver.h"
#include"train.h"

typedef struct{
  int cmd_code;
  int value;
}Message_test_t;

int main(void){
  // Initialize server
  printf("server initialization\n");
  Server_t* serv = init_server();

  // simulate a train connecting

  // loop
  Message_test_t test = {30, 2};
  
  send_message(package_message_data(NULL,NULL,(Message_data_t*)&test),0,NULL,0);

  Message_t* msg = listen_message(0,0,0);

  Message_t* response = route_messages(serv, msg);

  send_message(response,0,NULL,0);
  return 0;
}
