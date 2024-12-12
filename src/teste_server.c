#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MESSAGE_SIZE 2000
#define SOCKET_PORT 9002

int main(void) {
  int socket_desc = 0;
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  char server_message[MESSAGE_SIZE];
  char client_message[MESSAGE_SIZE];
  int client_struct_length = sizeof(client_addr);

  // Clean buffers:
  memset(server_message, '\0', sizeof(server_message));
  memset(client_message, '\0', sizeof(client_message));

  // Create UDP socket:
  socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (socket_desc < 0) {
    printf("Error while creating socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SOCKET_PORT);
  //  server_addr.sin_addr.s_addr =  INADDR_ANY;
  server_addr.sin_addr.s_addr = inet_addr("192.168.1.106");

  // Bind to the set port and IP:
  if (bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) <
      0) {
    printf("Couldn't bind to the port\n");
    return -1;
  }
  printf("Done with binding\n");

  printf("Listening for incoming messages...\n\n");

  // Receive client's message:
  if (recvfrom(socket_desc, client_message, sizeof(client_message), 0,
               (struct sockaddr*)&client_addr,
               (socklen_t*)&client_struct_length) < 0) {
    printf("Couldn't receive\n");
    return -1;
  }
  printf("Received message from IP: %s and port: %i\n",
         inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

  printf("Msg from client: %s\n", client_message);

  // Respond to client:
  strcpy(server_message, client_message);

  if (sendto(socket_desc, server_message, strlen(server_message), 0,
             (struct sockaddr*)&client_addr, client_struct_length) < 0) {
    printf("Can't send\n");
    return -1;
  }

  // Close the socket:
  close(socket_desc);

  return 0;
}
