/*
 * @file
 * @section DESCRIPTION
 * Contains functions to implement a simple verbose mode, which is to say, a
 * program that has longer (and more readable) outputs to stdout when given the
 * flag -v at EXECUTION TIME
 */
#ifndef VERBOSE_MODE_H_
#define VERBOSE_MODE_H_

#define IF_VERBOSE(verbose,code) \
  if (verbose) {         \
    code;                \
  }

int check_for_verbose_flag(int argc, char* argv[]);

#endif  // VERBOSE_MODE_H_
