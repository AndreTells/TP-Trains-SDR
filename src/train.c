#include "libtrain.h"

#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include "comms.h"
#include "constants.h"
#include "verbose_mode.h"

#define SOCKET_PORT 7000
#define IP_TRAIN "192.168.1.113"
#define IP_SERVER "192.168.1.104"


int main(int argc, char* argv[]) {
  // TODO(André) get addr by command line
  int verbose = check_for_verbose_flag(argc, argv);

  // open socket UDP

  int socket_fd = 0;
  struct sockaddr_in train_addr;
  socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  train_addr = create_socket_UDP(SOCKET_PORT, IP_TRAIN);

   // Bind to the set port and IP:
  if (bind(socket_fd, (struct sockaddr*)&train_addr, sizeof(train_addr)) <
      0) {
    printf("Couldn't bind to the port\n");
    return -1;
  }

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
  msg_buffer.cmd_code = TRAIN_CONNECT_CMD; // test

  Message_t* msg_to_send;
  Message_t* msg_received;

  char* ip_train = IP_TRAIN;
  char* ip_server = IP_SERVER;

  // package message

  msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,&msg_buffer);

  // send message to server

  IF_VERBOSE(verbose,printf("Sending message to server ...\n"));
  int check_send = send_message(socket_fd, msg_to_send);

  if (check_send == 0){
    IF_VERBOSE(verbose,printf("Sending message to server ... finished\n"));
  }

  // Receive the server's response

  IF_VERBOSE(verbose,printf("Receiving message from server ...\n"));
  msg_received = listen_message(socket_fd);

  IF_VERBOSE(verbose,printf("Receiving message from server ... finished\n"));
  IF_VERBOSE(verbose,printf("received message from %s \n", msg_received->target_addr));
  

  while (train->pos < TRAIN_END_POS) {
    
    char command [10];

    printf("CHOOSE A FOR ADVANCE THE TRAIN\n");

    fgets(command,10,stdin);

    switch (command[0]){
      IF_VERBOSE(verbose,printf("switch ok\n"));
      case 'A':
        if(train->pos < train->eoa){
          train->pos++;
          msg_buffer.cmd_code = TRAIN_UPDATE_POS_CMD;

          if (check_send == 0){
            IF_VERBOSE(verbose,printf("Sending message to server ... finished\n"));
          }

          }
        else{
          printf("Impossible to advance, please try to ask a new limit to server\n");
          }
        break;

      case 'U':
        printf("Nothing to do...\n");
        break;

      case 'E':
        printf("Nothing to do...\n");
        break;

      default:
        break;

      }

    msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,&msg_buffer);

    IF_VERBOSE(verbose,printf("Sending message to server ...\n"));
    check_send = send_message(socket_fd, msg_to_send);

    IF_VERBOSE(verbose,printf("Receiving message from server ...\n"));
    msg_received = listen_message(socket_fd);

    IF_VERBOSE(verbose,printf("Receiving message from server ... finished\n"));
    IF_VERBOSE(verbose,printf("received message from %s \n", msg_received->target_addr));

    show_train(train);
     // sleep(2);
    }


  return 0;
}
