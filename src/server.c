#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "comms.h"
#include "libserver.h"
#include "verbose_mode.h"
#include "comms_flags.h"

int main(int argc, char* argv[]) {
  int verbose = check_for_verbose_flag(argc, argv);
  char* ip_address = check_for_ip_flag(argc, argv);
  if (ip_address == NULL) {
    IF_VERBOSE(verbose,printf("no ip provided, using 127.0.0.1 \n"));
    ip_address = "127.0.0.1";
  }

  // Initialize server
  IF_VERBOSE(verbose,printf("server initialization ... \n"));
  Server_t* serv = init_server();

  IF_VERBOSE(verbose,printf("server initialization ... finished\n"));
  // open socket
  IF_VERBOSE(verbose,printf("opening socket ... \n"));

  // Create UDP socket:
  int socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (socket_fd< 0) {
    printf("Error while creating socket\n");
    return -1;
  }

  struct sockaddr_in server_addr;
  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  //  server_addr.sin_addr.s_addr =  INADDR_ANY;
  server_addr.sin_addr.s_addr = inet_addr(ip_address);

  // Bind to the set port and IP:
  if (bind(socket_fd, (struct sockaddr*)&server_addr,
           sizeof(server_addr)) < 0) {
    printf("Couldn't bind to the port\n");
    return -1;
  }

  IF_VERBOSE(verbose,printf("opening socket ... finished\n"));


  IF_VERBOSE(verbose,printf("click enter to continue\n"));
  IF_VERBOSE(verbose,read(0, NULL, 10));



  // loop
  while (1) {
    IF_VERBOSE(verbose,printf("waiting for a message ... \n"));
    Message_t* msg = listen_message(socket_fd);

    IF_VERBOSE(verbose,printf("received message from %s \n", msg->host_addr));
    IF_VERBOSE(verbose,printf("received message with code %d \n", msg->data.cmd_code));
    IF_VERBOSE(verbose,printf("waiting for a message ... finished\n"));

    IF_VERBOSE(verbose,printf("treating message ... \n"));
    Message_t* response = route_messages(serv, msg);

    print_server_state(serv);

    IF_VERBOSE(verbose,printf("sending message %s \n", response->target_addr));
    IF_VERBOSE(verbose,printf("treating message ... finished\n"));

    IF_VERBOSE(verbose,printf("sending response ... \n"));
    send_message(socket_fd, response);
    IF_VERBOSE(verbose,printf("sending response ... finished\n"));

    IF_VERBOSE(verbose,printf("continue ? (y/n)\n"); char res[2]; read(0, res, 2);
               if (res[0] == 'n') { break; });
  }
  return 0;
}
