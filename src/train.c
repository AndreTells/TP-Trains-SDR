#include "libtrain.h"

#include <stdio.h>
#include <unistd.h>

#include "comms.h"
#include "constants.h"
#include "verbose_mode.h"

int main(int argc, char* argv[]) {
  // TODO(André) get addr by command line
  int verbose = check_for_verbose_flag(argc, argv);

  int port = 0;
  // open socket

  // initialize train
  IF_VERBOSE(verbose,printf("initialising Train ... \n"));
  Train_t* train = create_train(NULL,NULL);

  if (train == NULL){
    return -1;
  }

  IF_VERBOSE(verbose,printf("initialising Train ... finished\n"));

  IF_VERBOSE(verbose,printf("click enter to continue\n"));
  IF_VERBOSE(verbose,read(0, NULL, 10));

  while (train->pos < TRAIN_END_POS) {
    sleep(2);
  }
  return 0;
}
