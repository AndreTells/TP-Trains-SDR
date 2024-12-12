#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libserver.h"
#include "verbose_mode.h"

int main(int argc, char* argv[]) {
  int verbose = check_for_verbose_flag(argc, argv);

  // Initialize server
  IF_VERBOSE(verbose,printf("server initialization ... \n"));
  Server_t* serv = init_server();

  IF_VERBOSE(verbose,printf("server initialization ... finished\n"));
  // open socket
  IF_VERBOSE(verbose,printf("opening socket ... \n"));

  IF_VERBOSE(verbose,printf("opening socket ... finished\n"));

  // TODO(André) open socket

  IF_VERBOSE(verbose,printf("click enter to continue\n"));
  IF_VERBOSE(verbose,read(0, NULL, 10));

  // loop
  while (1) {
    IF_VERBOSE(verbose,printf("waiting for a message ... \n"));
    Message_t* msg = listen_message(0);  // TODO(André) change to actual socket fd

    IF_VERBOSE(verbose,printf("waiting for a message ... finished\n"));

    IF_VERBOSE(verbose,printf("treating message ... \n"));
    Message_t* response = route_messages(serv, msg);

    IF_VERBOSE(verbose,printf("treating message ... finished\n"));

    IF_VERBOSE(verbose,printf("sending response ... \n"));
    send_message(0, response);  // TODO(André) change to actual socket fd
    IF_VERBOSE(verbose,printf("sending response ... finished\n"));

    IF_VERBOSE(verbose,printf("continue ? (y/n)\n"); char res[2]; read(0, res, 2);
               if (res[0] == 'n') { break; });
  }
  return 0;
}
