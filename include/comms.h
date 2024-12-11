#ifndef COMMS_H_
#define COMMS_H_

#define MAX_MESSAGE_SIZE 128

// Communication codes

#define SERVER_ACK_SUCCESS  0
#define SERVER_ACK_ERROR  1

// connection command
#define TRAIN_CONNECT_CMD 110
#define TRAIN_DISCONECT_CMD 111

//train movement
#define TRAIN_UPDATE_POS_CMD 210
#define TRAIN_REQ_LIM_EXTENSION_CMD 211

// info
#define INFO_REQ_CMD 310
#define INFO_SEND_CMD 300

// structure of a message
typedef union{
  int cmd_code;
  void* data[MAX_MESSAGE_SIZE];
} Message_data_t;

typedef struct{
  int cmd_code;
  int id;
  int pos;
  int eoa;
} Data_full_train_t;

typedef struct{
  int cmd_code;
  int pos;
} Data_pos_t;

typedef struct{
  int cmd_code;
  int eoa;
} Data_eoa_t;

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
