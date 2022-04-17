#include <stdio.h>
#include <zmq.h>
#include <string.h>

#define LENGTH 200
#define SEND_LENGTH 100

int main(void)
{
void *context = zmq_ctx_new();
void *requester = zmq_socket(context, ZMQ_REQ);
char buffer[LENGTH];
char buffer_send[SEND_LENGTH];
memset(buffer, 0, LENGTH);
memset(buffer_send, 0, SEND_LENGTH);

strcpy(buffer_send, "Czesc tu jonasz");
zmq_connect (requester, "tcp://localhost:5555");

zmq_send (requester, buffer_send, SEND_LENGTH, 0);


zmq_recv (requester, buffer, LENGTH, 0);

zmq_close(requester);
zmq_ctx_destroy(context);

return 0;}
