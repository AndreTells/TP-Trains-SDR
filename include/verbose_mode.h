#ifndef VERBOSE_MODE_H_
#define VERBOSE_MODE_H_

extern int verbose;

#define IF_VERBOSE(code) if (verbose) { code; }

void check_for_verbose_flag(int argc, char * argv[]);

#endif // VERBOSE_MODE_H_
