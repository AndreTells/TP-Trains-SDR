#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libserver.h"

typedef struct{
  int cmd_code;
  int value;
}Message_test_t;

int main(void){
  // Initialize server
  printf("server initialization\n");
  Server_t* serv = init_server();

  // loop

  Message_t* msg = listen_message(0);

  Message_t* response = route_messages(serv, msg);

  send_message(0,response);
  return 0;
}
