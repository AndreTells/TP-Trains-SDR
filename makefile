# --------------------------------------------------------------------- #
# Defining directories                                                  #
# --------------------------------------------------------------------- #
SRC_DIR = ./src/
INCLUDE_DIR = ./include/
BIN_DIR = ./bin/
OBJ_DIR = $(BIN_DIR)/obj

# --------------------------------------------------------------------- #
# Defining compilation options                                          #
#       -Wall           : display all warning messages                  #
#       -Werror         : treat warnings as errors                      #
#       -std=c99        : respect the ISO C99 standard                  #
#       -pedantic       : enforces the C standard as much as possible   #
# --------------------------------------------------------------------- #
CFLAGS  = -Wall
CFLAGS += -std=c99
CFLAGS += -Werror
CFLAGS += -pedantic
CFLAGS += -I$(INCLUDE_DIR)

# --------------------------------------------------------------------- #
# Definition of linker options                                          #
# --------------------------------------------------------------------- #
# LDFLAGS = -lrt
SRC_DUMMY = ./src/dummy_main.c ./src/dummy_comms.c ./src/dummy_server.c

dummy_version:
	clang $(CFLAGS) src/dummy_main.c src/dummy_comms.c src/dummy_server.c -o ./bin/dummy_version
