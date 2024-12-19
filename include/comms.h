/*
 * @file
 * @section DESCRIPTION
 *
 * header file for the comms.c file. Aggregates all functions and defines that
 * regard the socket communication required in the application. The Message_t is
 * what is used to send information between cooperating process
 */
#ifndef COMMS_H_
#define COMMS_H_

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

// Communication codes

// server response codes
#define SERVER_ACK_SUCCESS 0
#define SERVER_ACK_ERROR 1

// connection codes
#define TRAIN_CONNECT_CMD 110
#define TRAIN_DISCONECT_CMD 111

// train movement codes
#define TRAIN_UPDATE_POS_CMD 210
#define TRAIN_REQ_LIM_EXTENSION_CMD 211

// info codes
#define INFO_REQ_CMD 310
#define INFO_SEND_CMD 300

// internet related defines
#define MAX_MESSAGE_SIZE 2024
#define LEN_IPV4 32
#define PORT 7000

// structure of a message

/*
 * @struct  Host_address_t
 * @brief wrapper aronud 'struct sockaddrr' to better function legibility
 */
typedef struct {
  char address[LEN_IPV4];
}Host_address_t;

/*
 * @struct Remote_address_t
 * @brief wrapper around 'struct sockdaddr' to better function legibility
 */
typedef struct {
  char address[LEN_IPV4];
}Remote_address_t;

/*
 * @struct Message_t
 * @brief Package's the Message_data to make it easier to send it. Sholud only
 * be generated through the package_message_data function
 * @var Message_t::host_addr
 * address of the entity sending this message
 * @var Message_t::target_addr
 * address of the entity that'll receive this message
 * @var Message_t::data
 * the data of the message
 */
typedef struct {
  char host_addr[LEN_IPV4];
  char target_addr[LEN_IPV4];
  int cmd_code;
  int train_id;
  int pos;
  int eoa;
} Message_t;

/* @brief creates an instance of Message_t
 * @param host_addr address of the entity sending this message
 * @param target_addr address of the entity that'll receive this message
 * @param data contents of teh message
 * @return msg the data given packaged as a message
 */
Message_t* package_message_data(Host_address_t* host_addr,
                                Remote_address_t* target_addr,
                                int cmd_code,
                                int train_id,
                                int pos,
                                int eoa);

/* @brief sends a message through the given file descriptor
 * @param socket_client file descriptor of the socket
 * @param msg the message to be sent
 * @return res 0 if no errors happened and -1 otherwise
 */
int send_message(int socket_fd, Message_t* msg);

/* @brief receives a message through the given file descriptor
 * @param socket_client file descriptor of the socket
 * @return msg the received message
 */
Message_t* listen_message(int socket_fd);

/* @brief create a socket UDP
 * @param socket_port number of socket port
 * @param socket_address IP socket 
 * @return socket created
 */
struct sockaddr_in create_socket_UDP(int socket_port, char* socket_address);


#endif  // TRAIN_COMMANDS_H_
