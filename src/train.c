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
  // ===================================================== 
  int verbose = check_for_verbose_flag(argc, argv);

  int pos_ip_server = check_for_ip_server_flag(argc, argv);
  int pos_ip_train = check_for_ip_client_flag(argc, argv);

  char ip_server [20];
  strcpy (ip_server,IP_SERVER);
  char ip_train [20];
  strcpy (ip_train,IP_TRAIN);

  if(pos_ip_server > 0) strcpy(ip_server, argv[pos_ip_server]);
  IF_VERBOSE(verbose,printf("IP SERVER: %s ... \n",ip_server));

  if(pos_ip_train > 0) strcpy(ip_train, argv[pos_ip_train]);
  IF_VERBOSE(verbose,printf("IP TRAIN: %s ... \n",ip_train));

  // ===================================================== Open socket UDP

  int socket_fd = 0;
  struct sockaddr_in train_addr;
  socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  train_addr = create_socket_UDP(SOCKET_PORT, IP_TRAIN);

  // ===================================================== Bind to the set port and IP:
  
  if (bind(socket_fd, (struct sockaddr*)&train_addr, sizeof(train_addr)) <
      0) {
    printf("Couldn't bind to the port\n");
    return -1;
  }

  // ===================================================== Initialize train

  IF_VERBOSE(verbose,printf("initialising Train ... \n"));
  Train_t* train = create_train(NULL,NULL);

  if (train == NULL){
    IF_VERBOSE(verbose,printf("Error creating train\n"));
    return -1;
  }

  IF_VERBOSE(verbose,printf("initialising Train ... finished\n"));

  IF_VERBOSE(verbose,printf("click enter to continue\n"));
  IF_VERBOSE(verbose,read(0, NULL, 10));

  // ===================================================== Create 2 msg buffer to send and receive a message to server

  Message_data_t msg_buffer;
  Message_t* msg_to_send;
  Message_t* msg_received;

// ===================================================== Package message to create the train

  msg_buffer.cmd_code = TRAIN_CONNECT_CMD; // test
  msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,&msg_buffer);


  IF_VERBOSE(verbose,printf("Sending message to server ...\n"));
  int check_send = send_message(socket_fd, msg_to_send);

  if (check_send == 0){
    IF_VERBOSE(verbose,printf("Sending message to server ... finished\n"));
  }

  // ===================================================== Receive the server's response

  IF_VERBOSE(verbose,printf("Receiving message from server ...\n"));
  msg_received = listen_message(socket_fd);

  IF_VERBOSE(verbose,printf("Receiving message from server ... finished\n"));
  IF_VERBOSE(verbose,printf("received message from %s \n", msg_received->target_addr));

  char command [10];


  while (1) {
    printf("TYPE A FOR ADVANCE THE TRAIN\n U FOR UPDATE SERVER \n E FOR ASK FOR A EXTENSION\n");
    fgets(command,10,stdin);

    switch (command[0]){

      case 'A':
        if(train->pos < train->eoa){
          IF_VERBOSE(verbose,printf("Advancing one position\n"));
          train->pos++;
          msg_buffer.cmd_code = 0; // Don't send msg to server 

          }
        else{
          IF_VERBOSE(verbose,printf("TRAIN CAN'T ADVANCE, SO ASK FOR AN EXTENSION\n"));
          }
        break;

      case 'U':
        IF_VERBOSE(verbose,printf("Updating server....\n"));
        msg_buffer.cmd_code = TRAIN_UPDATE_POS_CMD;
        break;

      case 'E':
        IF_VERBOSE(verbose,printf("Requesting a extension to server\n"));
        msg_buffer.cmd_code = TRAIN_REQ_LIM_EXTENSION_CMD;
        break;

      default:
        break;

      }

  // ===================================================== Package message

  msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,&msg_buffer);

  // ===================================================== Send message to server

  if(msg_buffer.cmd_code != 0){

    IF_VERBOSE(verbose,printf("Sending message to server ...\n"));
    check_send = send_message(socket_fd, msg_to_send);

    if (check_send == 0){
      IF_VERBOSE(verbose,printf("Sending message to server ... finished\n"));
    }

    // ===================================================== Receive the server's response

    IF_VERBOSE(verbose,printf("Receiving message from server ...\n"));
    msg_received = listen_message(socket_fd);

    IF_VERBOSE(verbose,printf("Receiving message from server ... finished\n"));
    IF_VERBOSE(verbose,printf("received message from %s \n", msg_received->target_addr));

  }

  show_train(train);
     // sleep(2);
  }


  return 0;
}
