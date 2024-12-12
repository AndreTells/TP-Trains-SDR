#include<stdio.h>
#include <unistd.h>
#include "comms.h"
#include "constants.h"
#include "train.h"


int main(int argc, char * argv[]){
  //TODO get addr by command line
  check_for_verbose_flag(argc,argv);

  // open socket
  // connect to server
  IF_VERBOSE(printf("sending connection message ... \n"));
  Message_t* out_bound_connect_msg = package_message_data(
                                                          create_connection_msg());

  send_message(out_bound_connect_msg);
  IF_VERBOSE(printf("sending connection message ... finished\n"));

  IF_VERBOSE(printf("waiting for a server response... \n"));
  Message_t* msg = listen_message();

  IF_VERBOSE(printf("waiting for a server response... finished\n"));

  // initialize train
  IF_VERBOSE(printf("initialising Train ... \n"));
  Train_t* train = init_train(msg);

  if(train == NULL) return -1;

  IF_VERBOSE(printf("initialising Train ... finished\n"));

  IF_VERBOSE(printf("click enter to continue\n"));
  IF_VERBOSE(read(0,NULL,10));

  while(train->pos < TRAIN_END_POS){
    sleep(2);
  }
  return 0;
}
