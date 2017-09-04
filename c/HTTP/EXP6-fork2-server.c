// Program Status : Working as on 18-07-2016
// Handling Multiple Clients with fork() method
// TCP Echo Application
// Server Code
// This Server can receive message (for infinite number of times) from many clients and echo it back.

#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"

#define PORT 4441
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void main() 
{
 struct sockaddr_in addr, cl_addr;
 int sockfd, len, ret, newsockfd;
 char buffer[BUF_SIZE];
 pid_t childpid;
 char clientAddr[CLADDR_LEN];
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) 
 {
 printf("Error creating socket!\n");
 exit(1);
 }
 printf("Socket created...\n");
 
 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;

/* INADDR_ANY is used when you don't need to bind a socket to a specific IP. 
When you use this value as the address when calling bind(), the socket accepts 
connections to all the IPs of the machine. */

addr.sin_port = PORT;
 
 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) 
 {
  printf("Error binding!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 listen(sockfd, 5);

 for (;;) { //infinite loop
 len = sizeof(cl_addr);
 newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);

 if (newsockfd < 0) 
 {
 printf("Error accepting connection!\n");
 exit(1);
 }
 printf("Connection accepted...\n");

inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
/* This function converts the network address structure src in the af
   address family into a character string.  The resulting string is
   copied to the buffer pointed to by dst, which must be a non-null
   pointer.  The caller specifies the number of bytes available in this
   buffer in the argument size.
*/
  
if ((childpid = fork()) == 0) //creating a child process
{ 

close(sockfd);  //stop listening for new connections by the main process. 
//the parent process will continue to listen. 
//the chiled process now handles the connected client.

   for (;;) 
   {
    memset(buffer, 0, BUF_SIZE);
    ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);

/*  The sendto() and recvfrom() calls take additional parameters to allow 
the caller to specify the recipient of the data, or to be notified of 
the sender of the data. 

Functions sendto() and recvfrom() are MUST while using UDP. 
However we can use it in TCP also. 
What distinguishes TCP from UDP is the following line of statement-
sockfd = socket(AF_INET, SOCK_STREAM, 0); //for TCP
sockfd = socket(AF_INET, SOCK_DGRAM, 0); //for UDP

*/
 
  if(ret < 0) 
    {
     printf("Error receiving data!\n");  
     exit(1);
    }

    printf("Data received from Client %s : %s\n", clientAddr, buffer); 

    ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);   

   if (ret < 0) 
   {  
     printf("Error sending data!\n");  
     exit(1);  
   }
  
    printf("Data Sent to Client %s       : %s\n", clientAddr, buffer);
    printf("------------------------------------------------------------\n");
   }
  }
  close(newsockfd);
 }
}
