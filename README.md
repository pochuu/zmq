 * Compilation for server:  
 * gcc -Wall ./server.c -o ./server -lzmq -lpthread 
 * Compilation for clients: 
 * gcc -Wall ./clientreq.c -o ./clientreq -lzmq
 * gcc -Wall ./clientpush.c -o ./clientreq -lzmq
 * gcc -Wall ./clientsub.c -o ./clientreq -lzmq
 * Usage: 
 * ./server 
 * ./clientreq
 * ./clientpush
 * ./clientsub
