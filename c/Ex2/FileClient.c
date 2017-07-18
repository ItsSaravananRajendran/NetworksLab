#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 



int sockfd;



int newsockfd;
int main(int argc, char *argv[])
{
    int  portno, n ,thread,c;

    struct sockaddr_in serv_addr;
    struct hostent *server;
    FILE *ptr;
    char buffer[100];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    ptr=fopen("client.txt","r");
    while(1){
      c = fgetc(ptr);
      if( feof(ptr) )
      {
         buffer[0] = 'e';
	 buffer[1] = 'n';
	 buffer[2] = 'd';
	 n = write(newsockfd,buffer,3); 
         break ;
      }
      buffer[0] = (char) c;
      n = write(newsockfd,buffer,1); 	
    }
     fclose(ptr);	
    printf("Connection established and file is sent\n\n");
    return 0;
}
