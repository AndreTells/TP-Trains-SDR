#ifndef TRAIN_COMMS_H_
#define TRAIN_COMMS_H_

// Communication codes
// server ACK
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
typedef struct{
  int cmd_code;
  int train_id;
  int train_pos;
  int train_eoa;
} Message_t;

int send_message(Message_t* msg);

Message_t* listen_message();
#endif // TRAIN_COMMANDS_H_
