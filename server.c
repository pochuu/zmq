#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <zmq.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LENGTH 200
#define SEND_LENGTH 100

void *pull_service()
{

 int bytes,counter_pull=0;
 char buffer_pull[LENGTH];
 void *context3 = zmq_ctx_new();
 void *receiver = zmq_socket (context3, ZMQ_PULL);
 zmq_bind (receiver, "tcp://*:5553");
 while (1)
{
bytes = zmq_recv (receiver, buffer_pull, LENGTH, 0);
printf("%d. Odebrano [%d]B. %s\n",counter_pull,bytes,buffer_pull);
memset(buffer_pull, 0 , LENGTH);
counter_pull++;
}
zmq_close(receiver);
zmq_ctx_destroy (context3);

}

void *rep_service(){
void *context1 = zmq_ctx_new();
void *responder = zmq_socket (context1, ZMQ_REP);
char buffer[LENGTH];
char buffer_send[SEND_LENGTH];
int bytes, counter_req = 0;
int rc = zmq_bind (responder, "tcp://*:5554");
assert (rc == 0);
while (1){

bytes = zmq_recv (responder, buffer, LENGTH, 0);
counter_req++;

printf("%d. [%dB]  Message: %s\n",counter_req , bytes, buffer);

zmq_send(responder, buffer_send, SEND_LENGTH, 0);

memset(buffer, 0 , LENGTH);
}
zmq_close(responder);
zmq_ctx_destroy(context1);
}

void *pub_service()
{
void *context2 = zmq_ctx_new();
void *publisher = zmq_socket (context2, ZMQ_PUB);
char buffer_send_pub[SEND_LENGTH];
int counter_pub = 0;
int rc = zmq_bind(publisher, "tcp://*:5550");
assert (rc == 0);
while(1){
	strcpy(buffer_send_pub,"This is pub service");
	zmq_send (publisher, buffer_send_pub, SEND_LENGTH, 0);
	printf("%d. - published. \n",counter_pub);
	sleep(1);
	counter_pub++;
}
zmq_close(publisher);
zmq_ctx_destroy(context2);

}

int main(int argc, char argv[]){
pthread_t t1, t2 ,t3;
pthread_create( &t1, NULL, rep_service, NULL);
pthread_create( &t2, NULL, pull_service, NULL);
pthread_create( &t3, NULL, pub_service, NULL);
pthread_join(t3, NULL);
pthread_join(t2, NULL);
pthread_join(t1, NULL);
return 0;
}
