#include "libtrain.h"

#include <stdio.h>
#include <unistd.h>

#include "comms.h"
#include "constants.h"
#include "verbose_mode.h"

int main(int argc, char* argv[]) {
  // TODO get addr by command line
  check_for_verbose_flag(argc, argv);

  // open socket

  // initialize train
  IF_VERBOSE(printf("initialising Train ... \n"));
  Train_t* train = create_train(NULL,NULL);

  if (train == NULL) return -1;

  IF_VERBOSE(printf("initialising Train ... finished\n"));

  IF_VERBOSE(printf("click enter to continue\n"));
  IF_VERBOSE(read(0, NULL, 10));

  while (train->pos < TRAIN_END_POS) {
    sleep(2);
  }
  return 0;
}
