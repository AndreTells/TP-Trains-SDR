#include "libserver.h"
#include "comms.h"

int main(void){
  Message_t* msg = package_message_data(
                        (Host_address_t*)"192.168.1.113",(Remote_address_t*)"192.168.1.104",
                        TRAIN_CONNECT_CMD,-1,-1,-1);



  Server_t* serv = init_server();

  print_server_state(serv);
  Message_t* resp = route_messages(serv,msg);
  route_messages(serv,msg);

    printf("received message from %s \n", resp->host_addr);
    printf("received message from %s \n", resp->target_addr);
    printf("received message with code %d \n", resp->cmd_code);
    printf("received message with id %d \n", resp->train_id);
    printf("received message with pos %d \n", resp->pos);
    printf("received message with eoa %d \n", resp->eoa);
    printf("received message with size %lu \n", sizeof(msg));

  print_server_state(serv);

  return 0;
}
