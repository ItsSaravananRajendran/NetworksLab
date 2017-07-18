/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

pthread_t tid [2];
int newsockfd;

void *readMessage(void *arg){
	char buffer[256];
	int n;
        while(1){
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0){
			 error("ERROR reading from socket");
			 exit(1);
		}
		printf("Receicer:%s",buffer);
	    if(buffer[0] == 'e' && buffer[1] =='n' && buffer[2]=='d') exit(0);
	}	
	return NULL;
}




int main(int argc, char *argv[])
{
     int sockfd, portno, clilen,thread;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     printf("Connection estalbished\n");
     thread = pthread_create(&(tid[0]),NULL,&readMessage,NULL);
     while(1){
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(newsockfd,buffer,strlen(buffer));
	if (n < 0) 
	error("ERROR writing to socket");	
	    if(buffer[0] == 'e' && buffer[1] =='n' && buffer[2]=='d') exit(0);
     }   
     return 0; 
}
