#include "verbose_mode.h"

#include <string.h>


int check_for_verbose_flag(int argc, char* argv[]) {
  int verbose = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
      verbose = 1;
    }
  }
  return verbose;
}
