#include <stdio.h>
#include <zmq.h>
#include <string.h>

#define LENGTH 200
#define SEND_LENGTH 100

int main(void)
{
void *context = zmq_ctx_new();
void *subscriber = zmq_socket(context, ZMQ_SUB);
zmq_connect (subscriber, "tcp://localhost:5550");
zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
char buffer[LENGTH];
memset(buffer, 0, LENGTH);

zmq_recv (subscriber, buffer, LENGTH, 0);
printf("Received [SUB]: %s  \n",buffer);
zmq_close(subscriber);
zmq_ctx_destroy(context);

return 0;}
