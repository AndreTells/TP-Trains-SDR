#include "libserver.h"
#include "comms.h"

int main(void){
  //Message_data_t data;
  //data.cmd_code = 0;
  //Message_t* msg = package_message_data(NULL,NULL,&data);

  Server_t* serv = init_server();

  print_server_state(serv);
  route_messages(serv,NULL);
  //printf("%p",(void*)resp);
  //print_server_state(serv);

  return 0;
}
