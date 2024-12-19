#include "libtrain.h"

#include <stdio.h>
#include <unistd.h>

#include <string.h>

#include "comms.h"
#include "constants.h"
#include "verbose_mode.h"

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
  train_addr = create_socket_UDP(PORT, IP_TRAIN);

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
  Message_t* msg_to_send;
  Message_t* msg_received;

// ===================================================== Package message to create the train

  msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,TRAIN_CONNECT_CMD,-1,-1,-1);


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

  train->id = msg_received->train_id;
  train->pos = msg_received->pos;
  train->eoa = msg_received->eoa;
  
  IF_VERBOSE(verbose,printf("cmd_code msg_received_data %d \n", msg_received->cmd_code));
  IF_VERBOSE(verbose,printf("id msg_received_data %d \n", msg_received->train_id));
  IF_VERBOSE(verbose,printf("pos msg_received_data %d \n", msg_received->pos));
  IF_VERBOSE(verbose,printf("eoa msg_received_data %d \n", msg_received->eoa));

  char command [10];
  int cmd_to_send = 0;

  show_train(train);

  printf("TYPE A FOR ADVANCE THE TRAIN\n U FOR UPDATE SERVER \n E FOR ASK FOR A EXTENSION\n L FOR ASK FOR A EXIT\n");

  while (1) {
    fgets(command,10,stdin);

    switch (command[0]){

      case 'A':
        if(train->pos < train->eoa){
          char adv_step [4];
          printf("HOW MUCH DO U WANT AVANCE ?\n");
          fgets(adv_step,4,stdin);
          IF_VERBOSE(verbose,printf("ok ! \n"));
          if(atoi(adv_step) < 0 || train->pos+atoi(adv_step) > 100){
            printf("U CAN'T MOVE THERE \n");
            break;
          } 
          train->pos += atoi(adv_step);
          cmd_to_send = 0; // Don't send msg to server 

          }
        else{
          IF_VERBOSE(verbose,printf("TRAIN CAN'T ADVANCE, SO ASK FOR AN EXTENSION\n"));
          }
        break;

      case 'U':
        IF_VERBOSE(verbose,printf("Updating server....\n"));
        cmd_to_send = TRAIN_UPDATE_POS_CMD;
        break;

      case 'E':
        IF_VERBOSE(verbose,printf("Requesting a extension to server\n"));
        cmd_to_send = TRAIN_REQ_LIM_EXTENSION_CMD;
        break;

      case 'L':
      IF_VERBOSE(verbose,printf("Requesting a exit to server\n"));
      cmd_to_send = TRAIN_DISCONECT_CMD;
      break;

      default:
        break;

      }

  
  // ===================================================== Send message to server

  if(cmd_to_send != 0){

    // ===================================================== Package message

    msg_to_send = package_message_data((Host_address_t*)ip_train,(Remote_address_t*)ip_server,cmd_to_send,train->id,train->pos,train->eoa);


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

    if(msg_received->cmd_code != SERVER_ACK_ERROR){
      train->id = msg_received->train_id;
      train->pos = msg_received->pos;
      train->eoa = msg_received->eoa;
    }

    if(msg_received->cmd_code != SERVER_ACK_ERROR && command[0] == 'L'){
      break;
    }


    show_train(train);

  }else{
    printf("UPDATE TO SEE YOUR NEW CONFIGURATION [TYPE U]\n");
    
  }

  }


  return 0;
}
