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

// structure of a message
#define MAX_MESSAGE_SIZE 2024

/*
 * @union Message_data_t
 * @brief 'interface' for message data
 * @var Message_data_t::cmd_code
 * a int value identifying which command this data is directed at
 * @var Message_data_t::data
 * enough space to store an arbitrary ammount of data, allowing other structs to
 * 'implement' the Message_data_t interface and still be passed to the comms
 * functions
 */
typedef union {
  int cmd_code;
  void* data[MAX_MESSAGE_SIZE];
} Message_data_t;

/*
 * @struct Data_full_train_t
 * @brief Message data with all infos on train, 'implementing the
 * Message_data_type_t interface'
 * @var Data_full_train_t::cmd_code
 * iden. to the interface
 * @var Data_full_train_t::id
 * id of the train described
 * @var Data_full_train_t::pos
 * position of the train
 * @var Data_full_train_t::eoa
 * until when the train can advance without conflicts
 */
typedef struct {
  int cmd_code;
  int id;
  int pos;
  int eoa;
} Data_full_train_t;

/*
 * @struct Data_pos_t
 * @brief Message data with position and id of train, 'implementing the
 * Message_data_type_t interface'
 * @var Data_pos_t::cmd_code
 * iden. to the interface
 * @var Data_pos_t::id
 * id of the train described
 * @var Data_pos_t::pos
 * position of the train
 */
typedef struct {
  int cmd_code;
  int id;
  int pos;
} Data_pos_t;

/*
 * @struct Data_eoa_t
 * @brief Message data with eoa and id of train, 'implementing the
 * Message_data_type_t interface'
 * @var Data_pos_t::cmd_code
 * iden. to the interface
 * @var Data_pos_t::id
 * id of the train described
 * @var Data_eoa__t::eoa
 * until when the train can advance without conflicts
 */
typedef struct {
  int cmd_code;
  int id;
  int eoa;
} Data_eoa_t;

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
  struct sockaddr* host_addr;
  struct sockaddr* target_addr;
  Message_data_t data;
} Message_t;

/* @brief creates an instance of Message_t
 * @param host_addr address of the entity sending this message
 * @param target_addr address of the entity that'll receive this message
 * @param data contents of teh message
 * @return msg the data given packaged as a message
 */
Message_t* package_message_data(struct sockaddr* host_addr,
                                struct sockaddr* target_addr,
                                Message_data_t* data);

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
#endif  // TRAIN_COMMANDS_H_
