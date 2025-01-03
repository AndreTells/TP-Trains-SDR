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

teste_server_print:
	clang $(CFLAGS) src/comms_flags.c src/verbose_mode.c src/libserver.c src/comms.c src/teste_server_print.c -o ./bin/teste_server_print

server:
	clang $(CFLAGS) src/comms_flags.c src/verbose_mode.c src/libserver.c src/comms.c src/server.c -o ./bin/server

dummy_version_server:
	clang $(CFLAGS) src/dummy_libserver.c src/dummy_comms.c src/dummy_server.c -o ./bin/dummy_version_server

dummy_version_train:
	clang $(CFLAGS) src/dummy_train.c src/dummy_libtrain.c -o ./bin/dummy_version_train

teste_version_server:
	clang $(CFLAGS) src/teste_server.c  -o ./bin/teste_version_server

teste_version_client:
	clang $(CFLAGS) src/teste_client.c -o ./bin/teste_version_client

train:
	clang $(CFLAGS) src/verbose_mode.c src/libtrain.c src/comms.c src/train.c -o ./bin/train

format_code:
	clang-format --verbose -i --style=file src/*
	clang-format --verbose -i --style=file include/*

static_analyser:
	clang-tidy src/* -- -I include
