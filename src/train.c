#include "libtrain.h"

#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include "comms.h"
#include "constants.h"
#include "verbose_mode.h"

#define SOCKET_PORT 7000
#define IP_TRAIN "192.168.91.18"
#define IP_SERVER "192.168.91.187"


int main(int argc, char* argv[]) {
  // TODO(André) get addr by command line
  int verbose = check_for_verbose_flag(argc, argv);

  //  int port = 0;
  // open socket UDP

  struct sockaddr_in train_addr, server_addr;
  train_addr = create_socket_UDP(SOCKET_PORT, IP_TRAIN);
  server_addr = create_socket_UDP(SOCKET_PORT, IP_SERVER);

/*
  struct sockaddr_in server_addr, client_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SOCKET_PORT);
  server_addr.sin_addr.s_addr = inet_addr("192.168.91.187");

  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(SOCKET_PORT);
  client_addr.sin_addr.s_addr = inet_addr("192.168.91.18");
*/


  int socket_fd = 0;
  socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  // initialize train
  IF_VERBOSE(verbose,printf("initialising Train ... \n"));
  Train_t* train = create_train(NULL,NULL);

  if (train == NULL){
    IF_VERBOSE(verbose,printf("Error creating train\n"));
    return -1;
  }

  IF_VERBOSE(verbose,printf("initialising Train ... finished\n"));

  IF_VERBOSE(verbose,printf("click enter to continue\n"));
  IF_VERBOSE(verbose,read(0, NULL, 10));

  // create 2 msg buffer to send and receive a message to server

  Message_data_t msg_buffer;
  char string [10]= "Olá";
  memcpy(&(msg_buffer.data),string , sizeof(string) );  

  Message_t* msg_to_send;
  //Message_t* msg_received;

  msg_to_send = package_message_data((Host_address_t *)&train_addr,(Remote_address_t*)&server_addr,&msg_buffer);

  // send message to server

  IF_VERBOSE(verbose,printf("Sending message to server ...\n"));
  int check_send = send_message(socket_fd, msg_to_send);

  if (check_send == 0){
    IF_VERBOSE(verbose,printf("Sending message to server ... finished\n"));
  }

  // Receive the server's response

  IF_VERBOSE(verbose,printf("Receiving message from server ...\n"));
  //msg_received = listen_message(socket_fd);
  IF_VERBOSE(verbose,printf("Receiving message from server ... finished\n"));

  /*

    while (train->pos < TRAIN_END_POS) {
      sleep(2);
    }

  */

  return 0;
}
