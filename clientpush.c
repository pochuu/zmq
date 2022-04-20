#include <stdio.h>
#include <zmq.h>
#include <string.h>

#define LENGTH 200
#define SEND_LENGTH 100

int main(void)
{
void *context = zmq_ctx_new();
void *sender = zmq_socket(context, ZMQ_PUSH);
char buffer[LENGTH];
char buffer_send[SEND_LENGTH];
memset(buffer, 0, LENGTH);
memset(buffer_send, 0, SEND_LENGTH);

strcpy(buffer_send, "PUSH method here");
zmq_connect (sender, "tcp://localhost:5553");

zmq_send (sender, buffer_send, SEND_LENGTH, 0);



zmq_close(sender);
zmq_ctx_destroy(context);

return 0;}
