#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libserver.h"
#include"train.h"

int main(void){
  // Initialize server
  printf("server initialization\n");
  Server_t* serv = init_server();

  // loop
  while(1){
    Message_t* msg = listen_message();

    Message_t* response = route_messages(serv, msg);

    send_message(response);
  }
  return 0;
}
