#include<stdio.h>
#include<string.h>
#include"libserver.h"
#include"constants.h"

Train_t NULL_TRAIN ={0,-1,-1,-1,-1};

Server_result_e server_add_train(Server_t server, Message_t msg);
Server_result_e route_messages(Server_t server, Message_t msg);

int main(void){
  // Initialize server
  printf("server initialization");
  Server_t serv;
  serv.start=0;
  serv.next=0;

  for(int i=0; i<MAX_TRAINS; i++){
    memcpy(&(serv.trains[i]),&NULL_TRAIN, sizeof(Train_t));
    printf("train t_%d of the server created id: %d\n", i, serv.trains[i].id);
  }

  // simulate a train connecting

  // loop
  // getting train from message ...
  Message_t msg = listen_message();

  Train_t* train;
  memcpy(&train,&NULL_TRAIN, sizeof(Train_t));
  // getting train from message ...


  Message_t* msg_train_created = create_server_ACK_msg(train, SERVER_SUCCESS);
  send_message(msg_train_created);

  return 0;
}

Message_t* route_messages(Server_t server, Message_t msg){
  Message_t* response_status = create_server_ACK_msg(NULL_TRAIN, SERVER_ERR);

  switch(msg->cmd_code){
    case TRAIN_CONNECT_CMD:
      response_status = connect_train(server, msg);
      printf("not implemented");
      break;
    case TRAIN_DISCONNECT_CMD:
      printf("not implemented");
      break;
    case TRAIN_UPDATE_POS_CMD:
      printf("not implemented");
      break;
    case TRAIN_REQ_LIM_EXTENSION_CMD:
      printf("not implemented");
      break;
    case INFO_REQ_CMD:
      printf("not implemented");
      break;
  }

  return SERVER_ERR;
}

Server_result_e connect_train(Server_t server, Message_t msg){
  // TODO create pop for the buffer
  int i = serv.next;
  serv.next++;

  server.trains[i].id = i;

  server.trains[i].pos = TRAIN_START_POS;

  if(i == serv.start){
    server.trains[i].eoa = TRAIN_END_POS;
  }
  else{
    // get previous train and set this train's eoa to that train's position
    //train.eoa = ;
  }

  return ;
}
