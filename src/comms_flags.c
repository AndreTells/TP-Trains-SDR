#include <string.h>

#include "comms_flags.h"

char* check_for_ip_flag(int argc, char* argv[]){
  char* ip = NULL;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--ip") == 0 && i+1 != argc) {
      ip = argv[i+1];
    }
  }
  return ip;
}
