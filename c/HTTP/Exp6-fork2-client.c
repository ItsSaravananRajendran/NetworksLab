// Program Status : Working as on 18-07-2016
// Handling Multiple Clients with fork() method
// TCP Echo Application
// Client Code
// This client can send message (for infinite number of times) to server, which will be echoed back. 


#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
  
#define PORT 4441 
#define BUF_SIZE 2000 
  
int main(int argc, char**argv) 
 {  
 struct sockaddr_in addr, cl_addr;  
 int sockfd, ret;  
 char buffer[BUF_SIZE];  
 struct hostent * server;
 char * serverAddr;

 if (argc < 2) 
 {
  printf("usage: client < ip address >\n");
  exit(1);  
 }

 serverAddr = argv[1]; // Read as argument
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);  
 if (sockfd < 0) 
 {  
  printf("Error creating socket!\n");  
  exit(1);  
 }  
 printf("Socket created...\n");   

 memset(&addr, 0, sizeof(addr));  
 addr.sin_family = AF_INET;  // AF means Address Family; INET means Internet
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 /*  The inet_addr function converts a string containing an IPv4 dotted-decimal address 
into a proper address for the IN_ADDR structure. */

 addr.sin_port = PORT;     

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
 if (ret < 0) 
 {  
  printf("Error connecting to the server!\n");  
  exit(1);  
 }  
 printf("Connected to the server...\n");  

 memset(buffer, 0, BUF_SIZE);

 printf("Enter your message to Server : ");
 
 while (fgets(buffer, BUF_SIZE, stdin) != NULL) 
 {
 ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));  

/*  The sendto() and recvfrom() calls take additional parameters to allow 
the caller to specify the recipient of the data, or to be notified of 
the sender of the data. 

Functions sendto() and recvfrom() are MUST while using UDP. 
However we can use it in TCP also. 
What distinguishes TCP from UDP is the following line of statement-
sockfd = socket(AF_INET, SOCK_STREAM, 0); //for TCP
sockfd = socket(AF_INET, SOCK_DGRAM, 0); //for UDP

*/


  if (ret < 0) 
  {  
   printf("Error sending data!\n\t-%s", buffer);  
  }
  
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);  
  if (ret < 0) 
  {  
   printf("Error receiving data!\n");    
  } 

else 
 {
  printf("Data Received from Server   : ");
  fputs(buffer, stdout);
  printf("------------------------------------------------------------\n");
  printf("\n");
 }  
 
printf("Enter your message to Server : ");

}
 
return 0;    
}  
