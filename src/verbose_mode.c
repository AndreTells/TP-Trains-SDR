#include <string.h>
#include "verbose_mode.h"

int verbose = 0;

void check_for_verbose_flag(int argc, char * argv[]){
  for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
    }
}
