#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LENGTH 200
#define SEND_LENGTH 100

int main(int argc, char argv[]){

char buffer[LENGTH];
char buffer_send[SEND_LENGTH];
int bytes, counter_req = 0;
void *context = zmq_ctx_new();
void *responder = zmq_socket (context, ZMQ_REP);
int rc = zmq_bind (responder, "tcp://*:5555");
assert (rc == 0);



while (1){
bytes = zmq_recv (responder, buffer, LENGTH, 0);
counter_req++;

printf("%d. [%dB]  Message: %s\n",counter , bytes, buffer);

zmq_send(responder, buffer_send, SEND_LENGTH, 0);

memset(buffer, 0 , LENGTH);
}


return 0;
}

