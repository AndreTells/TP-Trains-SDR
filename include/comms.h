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

//Communication codes

// server response codes
#define SERVER_ACK_SUCCESS  0
#define SERVER_ACK_ERROR  1

// connection codes
#define TRAIN_CONNECT_CMD 110
#define TRAIN_DISCONECT_CMD 111

//train movement codes
#define TRAIN_UPDATE_POS_CMD 210
#define TRAIN_REQ_LIM_EXTENSION_CMD 211

// info codes
#define INFO_REQ_CMD 310
#define INFO_SEND_CMD 300

// structure of a message
#define MAX_MESSAGE_SIZE 2024

// generic Message data type
typedef union{
  int cmd_code;
  void* data[MAX_MESSAGE_SIZE];
} Message_data_t;

// Message data with all infos on train
typedef struct{
  int cmd_code;
  int id;
  int pos;
  int eoa;
} Data_full_train_t;

// Message data with position and id of train
typedef struct{
  int cmd_code;
  int id;
  int pos;
} Data_pos_t;

// Message data with eoa and id of train
typedef struct{
  int cmd_code;
  int id;
  int eoa;
} Data_eoa_t;

// Struct to package Message_data to make it easier to send it via UDP
typedef struct{
  struct sockaddr* host_addr;
  struct sockaddr* target_addr;
  Message_data_t data;
} Message_t;

Message_t* package_message_data(struct sockaddr* host_addr,
                                struct sockaddr* target_addr,
                                Message_data_t* data);

int send_message(Message_t* msg);

Message_t* listen_message();
#endif // TRAIN_COMMANDS_H_
