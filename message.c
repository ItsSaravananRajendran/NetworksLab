#include <pthread.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <unistd.h>


pthread_t tid [2];
int newsockfd;

void *readMessage(void *arg){
	char buffer[256];
        while(1){
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		printf("Here is the message: %s\n",buffer);
	}	
	return NULL;
}

int main(void ){
    int thread;
    hi=0;
    thread = pthread_create(&(tid[0]),NULL,&readMessage,NULL);
    if (thread != 0)
	printf("\ncan't create thread :[%s]", strerror(thread));
    else
	printf("\n Thread created successfully\n");
    sleep(5);
    return 0;
}
