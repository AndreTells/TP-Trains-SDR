#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"libserver.h"
#include"train.h"
#include"verbose_mode.h"

int main(int argc, char * argv[]){
  check_for_verbose_flag(argc,argv);

  // Initialize server
  IF_VERBOSE(printf("server initialization ... \n"));
  Server_t* serv = init_server();

  IF_VERBOSE(printf("server initialization ... finished\n"));
  // open socket
  IF_VERBOSE(printf("opening socket ... \n"));

  IF_VERBOSE(printf("opening socket ... finished\n"));

  IF_VERBOSE(printf("click enter to continue\n"));
  IF_VERBOSE(read(0,NULL,10));

  // loop
  while(1){
    Message_t* msg = listen_message();

    Message_t* response = route_messages(serv, msg);

    send_message(response);
  }
  return 0;
}
